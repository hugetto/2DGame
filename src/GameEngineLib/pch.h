#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define    NOMINMAX
#include "targetver.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <iostream>
#include <crtdbg.h>