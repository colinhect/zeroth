///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Core/Configuration.h>
#include <Hect/Platform/Platform.h>
#include <Hect/Runtime/Engine.h>

#include "Generated/_reflect_zeroth.h"

#ifdef HECT_WINDOWS_BUILD
#ifdef HECT_DEBUG_BUILD
#include <vld.h>
#endif
#endif

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
        hect::Platform::showFatalError(error.what());
    }

    return 0;
}