// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
 

enum Dir { LEFT, UP, RIGHT, DOWN };
#define ARR_SIZE 21
#define WINSIZE 504
#define TUNNEL -1

#define BIG_FOOD 3
#define SMALL_FOOD 2
#define WALL 1
#define EMPTY 0

#define UM_GAMEOVER WM_USER + 1


#include "framework.h"

#endif //PCH_H
