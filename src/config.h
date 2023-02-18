#ifndef __PONG_CONFIG_H__
#define __PONG_CONFIG_H__

#include <stdint.h>
#include <stddef.h>
#include "includes/raylib.h"

#define PONG
#define PONG_DEBUG 1

#define PONG_WIDTH 640
#define PONG_HEIGHT 480
#define PONG_TITLE "Pong 1.0v"


//----------------------------------------------------------------------------------
// Color palette
//----------------------------------------------------------------------------------
#define PONG_COLOR_0 (Color){8, 24, 32, 255}
#define PONG_COLOR_1 (Color){52, 104, 86, 255}
#define PONG_COLOR_2 (Color){136, 192, 112, 255}
#define PONG_COLOR_3 (Color){224, 248, 208, 255}

#endif // __PONG_CONFIG_H__
