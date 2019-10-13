//==============================================================================
/*
    Basic macro for logging (can be extended for other target builds; i.e, using
    NSLog for OS X / iOS). Could also be modified to log to a file instead of
    console.
    3/11/2014
    SDLTutorials.com
    Tim Jones
*/
//==============================================================================
#ifndef __CLOG_H__
    #define __CLOG_H__

    #include <stdio.h>

    #define DEBUG 1

    #ifdef DEBUG
        #define CLog(...) printf(__VA_ARGS__); printf("\n");
    #else
        #define CLog(...) ;
    #endif

#endif