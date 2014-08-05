///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include <Hect/Core/Configuration.h>

#include "ZerothApplication.h"

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
        ZerothApplication application;
        application.execute();
    }
    catch (hect::Error& error)
    {
        HECT_ERROR(error.what());
        hect::Window::showFatalError(error.what());
    }

    return 0;
}