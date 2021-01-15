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

// TEMP
#define _CRT_SECURE_NO_WARNINGS 

#include <cstdint>
#include <cassert>

#include <sstream>
#include <iostream>

#include <exception>
#include <algorithm>

#include <string>

#include <vector>
#include <set>

#if SE_PLATFORM_WINDOWS
//#	define WIN32_LEAN_AND_MEAN      // 
//#	define WIN32_EXTRA_LEAN         // 
//#	define NOMINMAX
#	define _WIN32_WINNT 0x0501
#	include <windows.h>
#	if USE_GDI
#		include <gdiplus.h>
#	endif
#endif

#include <GL/gl.h>
//#include <GL/glext.h>
#if SE_PLATFORM_WINDOWS
//#	include <GL/wglext.h>
#endif

SE_PRAGMA_WARNING_POP