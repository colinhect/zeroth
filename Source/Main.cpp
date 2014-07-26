///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Core/Configuration.h>
#include <Hect/Graphics/Renderer.h>
#include <Hect/Graphics/Window.h>
#include <Hect/IO/JsonValue.h>
#include <Hect/IO/FileSystem.h>
#include <Hect/Reflection/Type.h>

#include "AssetRefreshLoop.h"
#include "ServerLoop.h"

class HectTypes;

using namespace hect;

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
        Type::registerTypes<HectTypes>();
        
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

        // Create the input system
        InputSystem inputSystem;

        // Load the input axes from the settings
        for (const JsonValue& axisValue : settings["inputAxes"])
        {
            InputAxis axis;
            axis.decodeFromJsonValue(axisValue);
            inputSystem.addAxis(axis);
        }

        size_t threadCount = settings["assetCache"]["threadCount"].or(8).asUnsigned();
        AssetCache assetCache(fileSystem, threadCount);

        AssetRefreshLoop assetRefreshLoop(assetCache);
        ServerLoop loop(assetCache, inputSystem, window, renderer);

        // Update until the flow is complete
        while (window.pollEvents(inputSystem))
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