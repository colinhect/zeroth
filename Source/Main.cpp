///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect.h>

#include "Generated/RegisterTypes.h"

int main(int argc, char* const argv[])
{
    try
    {
        zeroth::registerTypes();

        hect::Engine engine(argc, argv);
        return engine.main();
    }
    catch (hect::Exception& exception)
    {
        HECT_ERROR(exception.what());
    }

    return 0;
}