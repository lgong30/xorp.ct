/*
 * Copyright (c) 2001-2004 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP$"

#include "ospfv2_xif.hh"

bool
XrlOspfv2V0p1Client::send_set_router_id(
	const char*	the_tgt,
	const uint32_t&	id,
	const SetRouterIdCB&	cb
)
{
    Xrl x(the_tgt, "ospfv2/0.1/set_router_id");
    x.args().add("id", id);
    return _sender->send(x, callback(this, &XrlOspfv2V0p1Client::unmarshall_set_router_id, cb));
}


/* Unmarshall set_router_id */
void
XrlOspfv2V0p1Client::unmarshall_set_router_id(
	const XrlError&	e,
	XrlArgs*	a,
	SetRouterIdCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}
