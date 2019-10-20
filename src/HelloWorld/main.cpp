//==============================================================================
/*
    Entry Point
    Hug Beneit
*/
//==============================================================================

#define _CRTDBG_MAP_ALLOC
#include "CMyApp.h"
#include <iostream>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#pragma warning( disable : 26812 )

int main(int argc, char* argv[])
{
    int lResult = MyGame::CMyApp::GetInstance()->Execute(argc, argv);
    _CrtDumpMemoryLeaks();  //Check for memory leaks
    return lResult;
}