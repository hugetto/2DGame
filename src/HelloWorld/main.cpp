//==============================================================================
/*
    EntryPoing
    Hug Beneit
*/
//==============================================================================

#include "pch.h"



int main(int argc, char* argv[])
{
    int lResult = MyGame::CMyApp::GetInstance()->Execute(argc, argv);
    _CrtDumpMemoryLeaks();
    return lResult;
}