/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#ifndef PLATFORM_H
#define PLATFORM_H

/**
*	@file
*
*	Platform abstractions, common header includes, workarounds for compiler warnings
*/

// Allow "DEBUG" in addition to default "_DEBUG"
#ifdef _DEBUG
#define DEBUG 1
#endif

#ifdef _WIN32
	// Remove warnings from warning level 4.
#pragma warning(disable:4514) // warning C4514: 'acosl' : unreferenced inline function has been removed
#pragma warning(disable:4100) // warning C4100: 'hwnd' : unreferenced formal parameter
#pragma warning(disable:4127) // warning C4127: conditional expression is constant
#pragma warning(disable:4512) // warning C4512: 'InFileRIFF' : assignment operator could not be generated
#pragma warning(disable:4611) // warning C4611: interaction between '_setjmp' and C++ object destruction is non-portable
#pragma warning(disable:4706) // warning C4706: assignment within conditional expression
#pragma warning(disable:4710) // warning C4710: function 'x' not inlined
#pragma warning(disable:4702) // warning C4702: unreachable code
#pragma warning(disable:4505) // unreferenced local function has been removed
#pragma warning(disable:4239) // nonstandard extension used : 'argument' ( conversion from class Vector to class Vector& )
#pragma warning(disable:4097) // typedef-name 'BaseClass' used as synonym for class-name 'CFlexCycler::CBaseFlex'
#pragma warning(disable:4324) // Padding was added at the end of a structure
#pragma warning(disable:4244) // type conversion warning.
#pragma warning(disable:4305) // truncation from 'const double ' to 'float '
#pragma warning(disable:4786) // Disable warnings about long symbol names

#if _MSC_VER >= 1300
#pragma warning(disable:4511) // Disable warnings about private copy constructors
#endif
#endif

#include "archtypes.h"     // DAL

// Misc C-runtime library headers
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using byte = unsigned char;
using word = unsigned short;
using func_t = unsigned int;
using string_t = unsigned int;
using qboolean = int;

#define ARRAYSIZE(p)		(sizeof(p)/sizeof(p[0]))

// Prevent tons of unused windows definitions
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOWINRES
#define NOSERVICE
#define NOMCX
#define NOIME
#define NOMINMAX
#include "winsani_in.h"
#include <Windows.h>
#include "winsani_out.h"
#include <malloc.h>

//Avoid the ISO conformant warning
#define stricmp _stricmp
#define strnicmp _strnicmp
#define itoa _itoa
#define strupr _strupr
#define strdup _strdup

#define DLLEXPORT __declspec( dllexport )

#define stackalloc(size) _alloca(size)

//Note: an implementation of stackfree must safely ignore null pointers
#define stackfree(address)

#else // _WIN32
#define FALSE 0
#define TRUE (!FALSE)
typedef uint32 ULONG;
typedef unsigned char BYTE;
typedef int BOOL;
#define MAX_PATH PATH_MAX
#include <limits.h>
#include <stdarg.h>
#include <alloca.h>
#define _vsnprintf(a,b,c,d) vsnprintf(a,b,c,d)

#define stricmp strcasecmp
#define _strnicmp strncasecmp
#define strnicmp strncasecmp
#define _snprintf snprintf
#define _alloca alloca

#define DLLEXPORT __attribute__ ( ( visibility( "default" ) ) )

#define stackalloc(size) alloca(size)

//Note: an implementation of stackfree must safely ignore null pointers
#define stackfree(address)

#endif //_WIN32

#define V_min(a,b)  (((a) < (b)) ? (a) : (b))
#define V_max(a,b)  (((a) > (b)) ? (a) : (b))

#define clamp( val, min, max ) ( ((val) > (max)) ? (max) : ( ((val) < (min)) ? (min) : (val) ) )

// Methods to invoke the constructor, copy constructor, and destructor
template <class T>
inline void Construct(T* pMemory)
{
	new(pMemory) T;
}

template <class T>
inline void CopyConstruct(T* pMemory, T const& src)
{
	new(pMemory) T(src);
}

template <class T>
inline void Destruct(T* pMemory)
{
	pMemory->~T();

#ifdef _DEBUG
	memset(pMemory, 0xDD, sizeof(T));
#endif
}

#endif //PLATFORM_H
