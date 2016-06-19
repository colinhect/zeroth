///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Generated/RegisterTypes.h>

#include <Hect.h>
#include <celero/Celero.h>

HECT_MAIN_SYSTEM_TEST_HARNESS_PROJECT(zeroth, "ZerothPerformanceTests.settings", { celero::Run(argc, const_cast<char**>(argv)); })
