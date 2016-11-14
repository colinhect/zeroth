///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2016 Colin Hill
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect/Core/Export.h>

#ifdef HECT_WINDOWS_BUILD

#ifdef ZEROTH_EXPORTS
#define ZEROTH_EXPORT __declspec(dllexport)
#else
#define ZEROTH_EXPORT __declspec(dllimport)
#endif

#else
#define ZEROTH_EXPORT
#endif

