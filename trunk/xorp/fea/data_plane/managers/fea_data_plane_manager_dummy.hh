// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2007 International Computer Science Institute
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

// $XORP: xorp/fea/data_plane/managers/fea_data_plane_manager_dummy.hh,v 1.2 2007/07/12 23:45:19 pavlin Exp $

#ifndef __FEA_DATA_PLANE_MANAGERS_FEA_DATA_PLANE_MANAGER_DUMMY_HH__
#define __FEA_DATA_PLANE_MANAGERS_FEA_DATA_PLANE_MANAGER_DUMMY_HH__

#include "fea/fea_data_plane_manager.hh"

class FibConfigEntryGetDummy;
class FibConfigEntryObserverDummy;
class FibConfigEntrySetDummy;
class FibConfigTableGetDummy;
class FibConfigTableObserverDummy;
class FibConfigTableSetDummy;
class IfConfigGetDummy;
class IfConfigObserverDummy;
class IfConfigSetDummy;


/**
 * FEA data plane manager class for Dummy FEA.
 */
class FeaDataPlaneManagerDummy : public FeaDataPlaneManager {
public:
    /**
     * Constructor.
     *
     * @param fea_node the @ref FeaNode this manager belongs to.
     */
    FeaDataPlaneManagerDummy(FeaNode& fea_node);

    /**
     * Virtual destructor.
     */
    virtual ~FeaDataPlaneManagerDummy();

    /**
     * Load the plugins.
     *
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    int load_plugins(string& error_msg);

    /**
     * Register the plugins.
     *
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    int register_plugins(string& error_msg);

private:
};

#endif // __FEA_DATA_PLANE_MANAGERS_FEA_DATA_PLANE_MANAGER_DUMMY_HH__
