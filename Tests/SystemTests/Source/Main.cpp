///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect.h>

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

int main(int argc, char* const argv[])
{
    try
    {
        // Use hardcoded command-line arguments for the engine to use
        char settingsPath[] = "ZerothSystemTests.settings";
        char* const engineArgv[] = { argv[0], settingsPath };

        hect::Engine engine(2, engineArgv);

        return Catch::Session().run(argc, argv);
    }
    catch (hect::Exception& exception)
    {
        HECT_ERROR(exception.what());
    }

    return EXIT_SUCCESS;
}
