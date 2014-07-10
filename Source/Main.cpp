///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Core/Configuration.h>
#include <Hect/IO/JsonValue.h>
#include <Hect/IO/FileSystem.h>
#include <Hect/Graphics/Renderer.h>
#include <Hect/Graphics/Window.h>

#include "RegisterComponents.h"

using namespace hect;

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

#include "ServerLoop.h"

int main(int argc, const char* argv[])
{
    argc;
    argv;

    try
    {
        registerComponents();

        // Create file system
        FileSystem fileSystem;

        // Add the working directory as a data source
        Path workingDirectory = fileSystem.workingDirectory();
        fileSystem.addDataSource(workingDirectory);

        // Set the working directory as the write directory
        fileSystem.setWriteDirectory(workingDirectory);

        // Load the settings
        JsonValue settings;
        {
            FileReadStream stream = fileSystem.openFileForRead("zeroth/Settings.json");
            settings.decodeFromJson(stream);
        }

        // Add the data sources listed in the settings
        for (const JsonValue& dataSource : settings["dataSources"])
        {
            fileSystem.addDataSource(dataSource.asString());
        }

        // Load video mode
        VideoMode videoMode;
        videoMode.decodeFromJsonValue(settings["videoMode"]);

        // Create window/renderer
        Window window("Sample", videoMode);
        Renderer renderer(window);

        // Load the input axes from the settings
        InputAxis::Array axes;
        for (const JsonValue& axisValue : settings["inputAxes"])
        {
            InputAxis axis;
            axis.decodeFromJsonValue(axisValue);
            axes.push_back(axis);
        }

        // Create the input system
        InputSystem inputSystem(axes);

        AssetCache assetCache(fileSystem);

        // Create the logic flow
        ServerLoop loop(assetCache, inputSystem, window, renderer);

        // Update until the flow is complete
        while (window.pollEvents(inputSystem))
        {
            if (!loop.tick())
            {
                break;
            }
        }
    }
    catch (Error& error)
    {
        Window::showFatalError(error.what());
    }

    return 0;
}