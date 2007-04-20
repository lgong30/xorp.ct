// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2007 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/rip/xorp_rip_main.cc,v 1.14 2006/03/16 00:05:53 pavlin Exp $"

#include "rip_module.h"
#include "libxorp/xlog.h"

#include "libxorp/eventloop.hh"
#include "libxorp/ipv4.hh"
#include "libxorp/ipv6.hh"

#include "libxipc/finder_constants.hh"
#include "libxipc/xrl_std_router.hh"

#include "libfeaclient/ifmgr_xrl_mirror.hh"

#include "rip/constants.hh"
#include "rip/system.hh"

#include "rip/xrl_config.hh"
#include "rip/xrl_target_rip.hh"
#include "rip/xrl_port_manager.hh"
#include "rip/xrl_process_spy.hh"
#include "rip/xrl_redist_manager.hh"
#include "rip/xrl_rib_notifier.hh"

#include "rip/xrl_target_rip.hh"
#include "rip/xrl_target_ripng.hh"

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

/**
 * @short Class specialized to determine correct type of XrlTarget for
 * addresses of type A.
 */
template <typename A>
struct XrlTarget {};

template <>
struct XrlTarget<IPv4> {
    typedef XrlRipTarget Type;
    static const char* name() { return "rip"; }
};

template <>
struct XrlTarget<IPv6> {
    typedef XrlRipngTarget Type;
    static const char* name() { return "ripng"; }
};


/**
 * Unary function class to build string containing ServiceBase objects
 * in a particular state.
 */
class service_names_in {
public:
    service_names_in(ServiceStatus in_state, string& out)
	: _st(in_state), _o(out)
    {}

    inline void operator() (const ServiceBase* sb)
    {
	if (sb->status() != _st) return;
	if (_o.empty() == false)
	    _o += ", ";
	_o += sb->service_name();
    }

protected:
    ServiceStatus 	_st;
    string& 		_o;
};


/**
 * Class to receive state changes of services used by RIP and update
 * status in the xrl interface accordingly.
 */

template <typename A>
class Service2XrlTargetStatus : public ServiceChangeObserverBase {
protected:
    void status_change(ServiceBase*, ServiceStatus, ServiceStatus)
    {
	update_status();
    }

public:
    Service2XrlTargetStatus(typename XrlTarget<A>::Type& t)
	: _t(t), _st(SERVICE_READY)
    {}

    ~Service2XrlTargetStatus()
    {
	while (_services.empty() == false) {
	    _services.front()->unset_observer(this);
	    _services.pop_front();
	}
    }

    bool add_service(ServiceBase* sb)
    {
	if (sb->set_observer(this)) {
	    _services.push_back(sb);
	    update_status();
	    return true;
	}
	return false;
    }

    void remove_service(ServiceBase* sb)
    {
	list<ServiceBase*>::iterator i;
	i = find(_services.begin(), _services.end(), sb);
	if (i != _services.end()) {
	    _services.erase(i);
	}
	sb->unset_observer(this);
    }

    void update_status()
    {
	// XXX This is particularly inefficient and not very good.

	// Clear existing state mask and then fill with current
	// service states.   This is then propagated to the XrlTarget.

	_st = ServiceStatus(0u);

	list<ServiceBase*>::const_iterator i;
	for (i = _services.begin(); i != _services.end(); ++i) {
	    ServiceBase *sb = *i;
	    _st = ServiceStatus(_st | sb->status());
	}

	if (_st & SERVICE_FAILED) {
	    string svcs;
	    for_each(_services.begin(), _services.end(),
		     service_names_in(SERVICE_FAILED, svcs));
	    _t.set_status(PROC_FAILED, "Failure(s): " + svcs);
	    return;
	}

	if (_st & SERVICE_SHUTTING_DOWN) {
	    string svcs;
	    for_each(_services.begin(), _services.end(),
		     service_names_in(SERVICE_SHUTTING_DOWN, svcs));
	    _t.set_status(PROC_SHUTDOWN, "Awaiting shutdown of: " + svcs);
	    return;
	}

	if (_st & (SERVICE_STARTING | SERVICE_READY)) {
	    string svcs;
	    for_each(_services.begin(), _services.end(),
		     service_names_in(SERVICE_STARTING, svcs));
	    _t.set_status(PROC_STARTUP, "Awaiting start up of: " + svcs);
	    return;
	}

	XLOG_ASSERT(_st == SERVICE_RUNNING);
	_t.set_status(PROC_READY, "");
    }
    inline bool have_status(ServiceStatus st) {
	return _st & st;
    }

protected:
    typename XrlTarget<A>::Type&	_t;
    list<ServiceBase*>			_services;
    ServiceStatus			_st;
};


/**
 * Extract Host and port from either host string or host colon port string, eg
 * "host" or "<host>:<port>".
 *
 * @param host_colon_port string to be scanned [in].
 * @param host host component of scanned string [out].
 * @param port port component of scanned string [out].
 * @return true on success, false if port value is invalid.
 */
static bool
parse_finder_args(const string& host_colon_port, string& host, uint16_t& port)
{
    string::size_type sp = host_colon_port.find(":");
    if (sp == string::npos) {
	host = host_colon_port;
	// Do not set port, by design it has default finder port value.
    } else {
	host = string(host_colon_port, 0, sp);
	string s_port = string(host_colon_port, sp + 1, 14);
	uint32_t t_port = atoi(s_port.c_str());
	if (t_port == 0 || t_port > 65535) {
	    XLOG_ERROR("Finder port %u is not in range 1--65535.\n",
		       XORP_UINT_CAST(t_port));
	    return false;
	}
	port = (uint16_t)t_port;
    }
    return true;
}

static void
usage(const char* name)
{
    fprintf(stderr, "Usage: %s [options]\n", name);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -F <host>[:<port>]  Specify Finder host and port\n");
    fprintf(stderr, "  -h                  Display this information\n");
}


/**
 * Class implementing RIP body.
 */
template <typename A>
class XorpRip
{
public:
    typedef typename XrlTarget<A>::Type XrlTargetType;

public:
    XorpRip();

    int main(int argc, char* const argv[]);

protected:
    void run(const string& finder_host, uint16_t finder_port);

protected:
    bool _stop_flag;
};


template <typename A>
XorpRip<A>::XorpRip()
    : _stop_flag(false)
{
}

template <typename A>
void
XorpRip<A>::run(const string& finder_host, uint16_t finder_port)
{
    XorpUnexpectedHandler catch_all(xorp_unexpected_handler);
    try {
	EventLoop		e;
	System<A>		rip_system(e);
	XrlStdRouter		xsr(e, XrlTarget<A>::name(),
				    finder_host.c_str(), finder_port);
	XrlProcessSpy		xps(xsr);
	IfMgrXrlMirror 		ixm(e, xrl_fea_name(),
				    FinderConstants::FINDER_DEFAULT_HOST(),
				    FinderConstants::FINDER_DEFAULT_PORT());
	XrlPortManager<A>	xpm(rip_system, xsr, ixm);
	XrlRedistManager<A>	xrm(rip_system, xsr);

	XrlTargetType xrlt(e, xsr, xps, xpm, xrm, _stop_flag, rip_system);

	wait_until_xrl_router_is_ready(e, xsr);

	Service2XrlTargetStatus<A> smon(xrlt);

	// Start up process spy
	xps.startup();
	smon.add_service(&xps);

	XrlRibNotifier<A> xn(e, rip_system.route_db().update_queue(), xsr);
	xn.startup();
	smon.add_service(&xn);

	// Start up interface mirror
	ixm.startup();
	smon.add_service(&ixm);

	// Start up xrl port manager
	xpm.startup();
	smon.add_service(&xpm);

	// Start up xrl redist manager
	xrm.startup();
	smon.add_service(&xrm);

	while ((_stop_flag == false)
	       && (smon.have_status(SERVICE_FAILED) == false)
	       && (xsr.failed() == false)) {
	    e.run();
	}

	xps.shutdown();
	xn.shutdown();
	ixm.shutdown();
	xpm.shutdown();
	xrm.shutdown();

	bool flag(false);
	XorpTimer t = e.set_flag_after_ms(5000, &flag);
	while (flag == false &&
	       smon.have_status(
		   ServiceStatus(~(SERVICE_FAILED | SERVICE_SHUTDOWN)))) {
	    e.run();
	}

	smon.remove_service(&xps);
	smon.remove_service(&xn);
	smon.remove_service(&ixm);
	smon.remove_service(&xpm);

	rip_system.route_db().flush_routes();
    } catch (...) {
	xorp_catch_standard_exceptions();
    }
}

template <typename A>
int
XorpRip<A>::main(int argc, char * const argv[])
{
    xlog_init(argv[0], NULL);
    xlog_set_verbose(XLOG_VERBOSE_LOW);
    xlog_level_set_verbose(XLOG_LEVEL_ERROR, XLOG_VERBOSE_HIGH);
    xlog_add_default_output();
    xlog_start();

    string	finder_host = FinderConstants::FINDER_DEFAULT_HOST().str();
    uint16_t	finder_port = FinderConstants::FINDER_DEFAULT_PORT();
    bool	do_run 	    = true;

    int ch;
    while ((ch = getopt(argc, argv, "F:")) != -1) {
	switch (ch) {
	case 'F':
	    do_run = parse_finder_args(optarg, finder_host, finder_port);
	    break;
	default:
	    usage(argv[0]);
	    do_run = false;
	}
    }

    if (do_run)
	run(finder_host, finder_port);

    //
    // Gracefully stop and exit xlog
    //
    xlog_stop();
    xlog_exit();
    return 0;
}


int
main(int argc, char* const argv[])
{
#if defined(INSTANTIATE_IPV4)
    XorpRip<IPv4> xorp_rip;
#elif defined(INSTANTIATE_IPV6)
    XorpRip<IPv6> xorp_rip;
#endif
    return xorp_rip.main(argc, argv);
}
