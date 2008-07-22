/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/mfea_client_xif.cc,v 1.27 2007/07/16 22:29:24 pavlin Exp $"

#include "mfea_client_xif.hh"

bool
XrlMfeaClientV0p1Client::send_recv_kernel_signal_message4(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const uint32_t&	message_type,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv4&	source_address,
	const IPv4&	dest_address,
	const vector<uint8_t>&	protocol_message,
	const RecvKernelSignalMessage4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mfea_client/0.1/recv_kernel_signal_message4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("message_type", message_type);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source_address", source_address);
    x.args().add("dest_address", dest_address);
    x.args().add("protocol_message", protocol_message);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_kernel_signal_message4, cb));
}


/* Unmarshall recv_kernel_signal_message4 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_kernel_signal_message4(
	const XrlError&	e,
	XrlArgs*	a,
	RecvKernelSignalMessage4CB		cb
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

bool
XrlMfeaClientV0p1Client::send_recv_kernel_signal_message6(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const uint32_t&	message_type,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv6&	source_address,
	const IPv6&	dest_address,
	const vector<uint8_t>&	protocol_message,
	const RecvKernelSignalMessage6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mfea_client/0.1/recv_kernel_signal_message6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("message_type", message_type);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source_address", source_address);
    x.args().add("dest_address", dest_address);
    x.args().add("protocol_message", protocol_message);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_kernel_signal_message6, cb));
}


/* Unmarshall recv_kernel_signal_message6 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_kernel_signal_message6(
	const XrlError&	e,
	XrlArgs*	a,
	RecvKernelSignalMessage6CB		cb
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

bool
XrlMfeaClientV0p1Client::send_recv_dataflow_signal4(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const IPv4&	source_address,
	const IPv4&	group_address,
	const uint32_t&	threshold_interval_sec,
	const uint32_t&	threshold_interval_usec,
	const uint32_t&	measured_interval_sec,
	const uint32_t&	measured_interval_usec,
	const uint32_t&	threshold_packets,
	const uint32_t&	threshold_bytes,
	const uint32_t&	measured_packets,
	const uint32_t&	measured_bytes,
	const bool&	is_threshold_in_packets,
	const bool&	is_threshold_in_bytes,
	const bool&	is_geq_upcall,
	const bool&	is_leq_upcall,
	const RecvDataflowSignal4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mfea_client/0.1/recv_dataflow_signal4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("source_address", source_address);
    x.args().add("group_address", group_address);
    x.args().add("threshold_interval_sec", threshold_interval_sec);
    x.args().add("threshold_interval_usec", threshold_interval_usec);
    x.args().add("measured_interval_sec", measured_interval_sec);
    x.args().add("measured_interval_usec", measured_interval_usec);
    x.args().add("threshold_packets", threshold_packets);
    x.args().add("threshold_bytes", threshold_bytes);
    x.args().add("measured_packets", measured_packets);
    x.args().add("measured_bytes", measured_bytes);
    x.args().add("is_threshold_in_packets", is_threshold_in_packets);
    x.args().add("is_threshold_in_bytes", is_threshold_in_bytes);
    x.args().add("is_geq_upcall", is_geq_upcall);
    x.args().add("is_leq_upcall", is_leq_upcall);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_dataflow_signal4, cb));
}


/* Unmarshall recv_dataflow_signal4 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_dataflow_signal4(
	const XrlError&	e,
	XrlArgs*	a,
	RecvDataflowSignal4CB		cb
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

bool
XrlMfeaClientV0p1Client::send_recv_dataflow_signal6(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const IPv6&	source_address,
	const IPv6&	group_address,
	const uint32_t&	threshold_interval_sec,
	const uint32_t&	threshold_interval_usec,
	const uint32_t&	measured_interval_sec,
	const uint32_t&	measured_interval_usec,
	const uint32_t&	threshold_packets,
	const uint32_t&	threshold_bytes,
	const uint32_t&	measured_packets,
	const uint32_t&	measured_bytes,
	const bool&	is_threshold_in_packets,
	const bool&	is_threshold_in_bytes,
	const bool&	is_geq_upcall,
	const bool&	is_leq_upcall,
	const RecvDataflowSignal6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mfea_client/0.1/recv_dataflow_signal6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("source_address", source_address);
    x.args().add("group_address", group_address);
    x.args().add("threshold_interval_sec", threshold_interval_sec);
    x.args().add("threshold_interval_usec", threshold_interval_usec);
    x.args().add("measured_interval_sec", measured_interval_sec);
    x.args().add("measured_interval_usec", measured_interval_usec);
    x.args().add("threshold_packets", threshold_packets);
    x.args().add("threshold_bytes", threshold_bytes);
    x.args().add("measured_packets", measured_packets);
    x.args().add("measured_bytes", measured_bytes);
    x.args().add("is_threshold_in_packets", is_threshold_in_packets);
    x.args().add("is_threshold_in_bytes", is_threshold_in_bytes);
    x.args().add("is_geq_upcall", is_geq_upcall);
    x.args().add("is_leq_upcall", is_leq_upcall);
    return _sender->send(x, callback(this, &XrlMfeaClientV0p1Client::unmarshall_recv_dataflow_signal6, cb));
}


/* Unmarshall recv_dataflow_signal6 */
void
XrlMfeaClientV0p1Client::unmarshall_recv_dataflow_signal6(
	const XrlError&	e,
	XrlArgs*	a,
	RecvDataflowSignal6CB		cb
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