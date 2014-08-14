///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Core/Configuration.h>
#include <Hect/Platform/Platform.h>
#include <Hect/Runtime/Engine.h>

using namespace hect;

#include "ZerothGameMode.h"

#ifdef HECT_WINDOWS_BUILD
#ifdef HECT_DEBUG_BUILD
#include <vld.h>
#endif
#endif

int main(int argc, const char* argv[])
{
    try
    {
        Engine::initialize(argc, argv);
        ZerothGameMode().execute();
        Engine::deinitialize();
    }
    catch (Error& error)
    {
        HECT_ERROR(error.what());
        Platform::showFatalError(error.what());
    }

    return 0;
}