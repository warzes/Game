#pragma once

//=============================================================================
// Engine header
//=============================================================================
#include "Macros.h"
#include "Config.h"

//=============================================================================
// Standart header
//=============================================================================
SE_PRAGMA_WARNING_DISABLE_MSVC(4514)
SE_PRAGMA_WARNING_DISABLE_MSVC(4820)

SE_PRAGMA_WARNING_LEVEL(3)

#define _STL_WARNING_LEVEL 3
#include <stdint.h>

#if SE_PLATFORM_WINDOWS
#	define WIN32_LEAN_AND_MEAN      // 
#	define WIN32_EXTRA_LEAN         // 
#	define NOMINMAX
#	include <windows.h>
#endif

SE_PRAGMA_WARNING_POP