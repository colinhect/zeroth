///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Generated/RegisterTypes.h>

#include <Hect.h>

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

HECT_PROJECT_MAIN_TEST_HARNESS(zeroth, "ZerothSystemTests.settings", { code = Catch::Session().run(argc, argv); })
