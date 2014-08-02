///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Core/Configuration.h>
#include <Hect/Core/Engine.h>

#include "AssetRefreshLoop.h"
#include "MainLoop.h"

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
        
        MainLoop loop(engine);

        while (engine.window().pollEvents(engine.inputSystem()))
        {
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