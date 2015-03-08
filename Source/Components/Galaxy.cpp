///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2015 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "Galaxy.h"

namespace zeroth
{

Encoder& operator<<(Encoder& encoder, const ParticleLayer& particleLayer)
{
    encoder << beginObject()
            << encodeValue("name", particleLayer.name)
            << encodeValue("renderShader", particleLayer.renderShader)
            << encodeValue("generateShader", particleLayer.generateShader)
            << encodeValue("size", particleLayer.size)
            << encodeValue("density", particleLayer.density)
            << endObject();

    return encoder;
}

Decoder& operator>>(Decoder& decoder, ParticleLayer& particleLayer)
{
    decoder >> beginObject()
            >> decodeValue("name", particleLayer.name)
            >> decodeValue("renderShader", particleLayer.renderShader)
            >> decodeValue("generateShader", particleLayer.generateShader)
            >> decodeValue("size", particleLayer.size)
            >> decodeValue("density", particleLayer.density)
            >> endObject();

    return decoder;
}

}