/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/test_socket4_base.hh,v 1.13 2007/11/17 04:06:50 pavlin Exp $
 */


#ifndef __XRL_TARGETS_TEST_SOCKET4_BASE_HH__
#define __XRL_TARGETS_TEST_SOCKET4_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlTestSocket4Target"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlTestSocket4TargetBase {
protected:
    XrlCmdMap* _cmds;

public:
    /**
     * Constructor.
     *
     * @param cmds an XrlCmdMap that the commands associated with the target
     *		   should be added to.  This is typically the XrlRouter
     *		   associated with the target.
     */
    XrlTestSocket4TargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlTestSocket4TargetBase();

    /**
     * Set command map.
     *
     * @param cmds pointer to command map to associate commands with.  This
     * argument is typically a pointer to the XrlRouter associated with the
     * target.
     *
     * @return true on success, false if cmds is null or a command map has
     * already been supplied.
     */
    bool set_command_map(XrlCmdMap* cmds);

    /**
     * Get Xrl instance name associated with command map.
     */
    const string& name() const { return _cmds->name(); }

    /**
     * Get version string of instance.
     */
    const char* version() const { return "test_socket4/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values,
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values,
	string&	version) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get status of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_status(
	// Output values,
	uint32_t&	status,
	string&	reason) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Request clean shutdown of Xrl Target
     */
    virtual XrlCmdError common_0_1_shutdown() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when a packet arrives
     *  from an IPv4 source.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     *
     *  @param if_name the interface name the packet arrived on, if known. If
     *  unknown, then it is an empty string.
     *
     *  @param vif_name the vif name the packet arrived on, if known. If
     *  unknown, then it is an empty string.
     *
     *  @param src_host the originating host.
     *
     *  @param src_port the originating IP port.
     *
     *  @param data the data received.
     */
    virtual XrlCmdError socket4_user_0_1_recv_event(
	// Input values,
	const string&	sockid,
	const string&	if_name,
	const string&	vif_name,
	const IPv4&	src_host,
	const uint32_t&	src_port,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when a connection
     *  request is received from an IPv4 source. It applies only to TCP
     *  sockets.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     *
     *  @param src_host the connecting host.
     *
     *  @param src_port the connecting IP port.
     *
     *  @param new_sockid the identifier associated with the new socket that
     *  has been created to handle the new connection.
     *
     *  @param accept if true, the connection request has been accepted,
     *  otherwise it has been rejected.
     */
    virtual XrlCmdError socket4_user_0_1_inbound_connect_event(
	// Input values,
	const string&	sockid,
	const IPv4&	src_host,
	const uint32_t&	src_port,
	const string&	new_sockid,
	// Output values,
	bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when an outgoing
     *  connection request originated by the local host is completed. It
     *  applies only to TCP sockets. Note that if the connection failed, the
     *  error_event will be dispatched instead.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     */
    virtual XrlCmdError socket4_user_0_1_outgoing_connect_event(
	// Input values,
	const string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when an error occurs.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     *
     *  @param error a textual description of the error.
     *
     *  @param fatal indication of whether socket is shutdown because of error.
     */
    virtual XrlCmdError socket4_user_0_1_error_event(
	// Input values,
	const string&	sockid,
	const string&	error,
	const bool&	fatal) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when the peer has
     *  closed the connection. It applies only to TCP sockets. Note that the
     *  socket itself is left open and must be explicitly closed.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     */
    virtual XrlCmdError socket4_user_0_1_disconnect_event(
	// Input values,
	const string&	sockid) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_recv_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_inbound_connect_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_outgoing_connect_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_error_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_disconnect_event(const XrlArgs& in, XrlArgs* out);

    void add_handlers();
    void remove_handlers();
};

#endif // __XRL_TARGETS_TEST_SOCKET4_BASE_HH__