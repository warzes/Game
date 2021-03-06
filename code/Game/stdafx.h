#pragma once

//=============================================================================
// Pre Engine header
//=============================================================================
#include "Macros.h"
#include "Config.h"
#include "InlineFunc.h"
#include "Example.h"

//=============================================================================
// Standart header
//=============================================================================
SE_PRAGMA_WARNING_DISABLE_MSVC(4514)
SE_PRAGMA_WARNING_DISABLE_MSVC(4820)
SE_PRAGMA_WARNING_DISABLE_MSVC(5045)

SE_PRAGMA_WARNING_LEVEL(3)

#define _STL_WARNING_LEVEL 3

// TEMP
#define _CRT_SECURE_NO_WARNINGS 

#include <cstdint>
#include <cassert>

#include <sstream>
#include <fstream>
#include <iostream>

#include <exception>
#include <algorithm>
#include <functional>

#include <string>
#include <string_view>

#include <list>
#include <vector>
#include <set>
#include <map>

#include <memory>

#if SE_PLATFORM_WINDOWS
#	define WIN32_LEAN_AND_MEAN      // 
#	define WIN32_EXTRA_LEAN         // 
#	define VC_EXTRALEAN
#	define NOMINMAX
#	define _WIN32_WINNT 0x0600		// Windows Vista
#	include <windows.h>
#endif

#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#if EXAMPLE_BREAKOUT
#	include <irrKlang/irrKlang.h>
#endif

#include <stb_image.h>

SE_PRAGMA_WARNING_POP

//=============================================================================
// Post Engine header
//=============================================================================