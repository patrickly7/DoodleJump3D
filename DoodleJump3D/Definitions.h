/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __DEFINITIONS_H_
#define __DEFINITIONS_H_

//#include <vld.h>

#include "Simplex\Simplex.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"
#include "SFML\Audio.hpp"

enum class GameState {
    MAIN_MENU,
    GAME,
    PAUSE_MENU,
    END_MENU,
    CLOSE
};

enum class Movement_Key {
    RIGHT,
    TOP_RIGHT,
    TOP,
    TOP_LEFT,
    LEFT,
    BOTTOM_LEFT,
    BOTTOM,
    BOTTOM_RIGHT,
    NONE
};
#endif //__DEFINITIONS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/