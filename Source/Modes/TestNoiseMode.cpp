///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "TestNoiseMode.h"

using namespace zeroth;

TestNoiseMode::TestNoiseMode(Engine& engine) :
    _galaxyGenerator(engine),
    _mouse(engine.platform().mouse()),
    _keyboard(engine.platform().keyboard())
{
    AssetCache& assetCache = engine.assetCache();
    _screenMesh = assetCache.getHandle<Mesh>("Hect/Screen.mesh");
    _showGalaxyShader = assetCache.getHandle<Shader>("Galaxy/Noise/Show.shader");

    _galaxyGenerator.generateDensity(GalaxyType_Spiral, 123, _density);

    Image image = engine.renderer().downloadTextureImage(_density);

    FileSystem& fileSystem = engine.fileSystem();
    fileSystem.setWriteDirectory("D:/Desktop");

    auto stream = fileSystem.openFileForWrite("Density.png");
    BinaryEncoder encoder(*stream);
    encoder << encodeValue(image);

    _keyboard.addListener(*this);
}

bool TestNoiseMode::tick(Engine& engine, double timeStep)
{
    return _active;
}

void TestNoiseMode::render(Engine& engine, RenderTarget& target)
{
    Renderer::Frame frame = engine.renderer().beginFrame(target);
    frame.clear();
    frame.setShader(*_showGalaxyShader);

    Uniform& uniform = _showGalaxyShader->uniform("densityMap");
    frame.setUniform(uniform, _density);

    frame.renderMesh(*_screenMesh);
}

void TestNoiseMode::receiveEvent(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType_KeyDown)
    {
        if (event.key == Key_Esc)
        {
            _active = false;
        }
    }
}
