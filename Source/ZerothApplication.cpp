///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2014 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#include "ZerothApplication.h"

#include "MainLoop.h"

ZerothApplication::ZerothApplication() :
    hect::Application("Zeroth", "zeroth/Settings.json")
{
}

void ZerothApplication::execute()
{
    MainLoop loop(input(), storage(), renderer(), window());

    while (window().pollEvents(input()))
    {
        if (!loop.tick())
        {
            break;
        }
    }
}