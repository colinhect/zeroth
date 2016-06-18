///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect.h>
#include <celero/Celero.h>

int main(int argc, char* argv[])
{
    try
    {
        // Use hardcoded command-line arguments for the engine to use
        char settingsPath[] = "ZerothPerformanceTests.settings";
        char* const engineArgv[] = { argv[0], settingsPath };

        hect::Engine engine(2, engineArgv);

        celero::Run(argc, argv);
        return 0;
    }
    catch (hect::Exception& exception)
    {
        HECT_ERROR(exception.what());
    }

    return EXIT_SUCCESS;
}
