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
    catch (hect::Error& error)
    {
        HECT_ERROR(error.what());
    }

    return 0;
}