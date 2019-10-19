#pragma once

#define _CRTDBG_MAP_ALLOC
#include "CMyApp.h"
#include <iostream>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#pragma warning( disable : 26812 )