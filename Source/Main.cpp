///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Core/Configuration.h>
#include <Hect/Core/Engine.h>

#include "AssetRefreshLoop.h"
#include "ServerLoop.h"

#ifdef HECT_WINDOWS_BUILD
#ifdef HECT_DEBUG_BUILD
#include <vld.h>
#endif
#endif

int main(int argc, const char* argv[])
{
    argc;
    argv;

    try
    {
        hect::Engine engine("Zeroth", "zeroth/Settings.json");
        
        AssetRefreshLoop assetRefreshLoop(engine.assetCache());
        ServerLoop loop(engine);

        // Update until the flow is complete
        while (engine.window().pollEvents(engine.inputSystem()))
        {
            assetRefreshLoop.tick();
            if (!loop.tick())
            {
                break;
            }
        }
    }
    catch (Error& error)
    {
        HECT_ERROR(error.what());
        Window::showFatalError(error.what());
    }

    return 0;
}