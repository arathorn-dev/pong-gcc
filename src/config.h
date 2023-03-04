#ifndef __PONG_CONFIG_H__
#define __PONG_CONFIG_H__

#include <stdint.h>
#include <stddef.h>
#include "includes/raylib.h"
#include "includes/raymath.h"

#define PONG
#define PONG_DEBUG 1

#define PONG_WIDTH 640
#define PONG_HEIGHT 480
#define PONG_TITLE "Pong 1.0v"
#define PONG_FPS 30

#define PONG_VOLUME 0.2

#define PONG_AUTHOR "Created by Arathorn 2023"

//----------------------------------------------------------------------------------
// Color palette
//----------------------------------------------------------------------------------
// #define PONG_COLOR_0 (Color){8, 24, 32, 255}
// #define PONG_COLOR_1 (Color){52, 104, 86, 255}
// #define PONG_COLOR_2 (Color){136, 192, 112, 255}
// #define PONG_COLOR_3 (Color){224, 248, 208, 255}


// GBP-NSO color.
// #define PONG_COLOR_0 (Color){48, 56, 32, 255}
// #define PONG_COLOR_1 (Color){99, 114, 81, 255}
// #define PONG_COLOR_2 (Color){141, 156, 123, 255}
// #define PONG_COLOR_3 (Color){181, 198, 156, 255}


// Rustic GB
// #define PONG_COLOR_0 (Color){44, 33, 55, 255}
// #define PONG_COLOR_1 (Color){118, 68, 98, 255}
// #define PONG_COLOR_2 (Color){169, 104, 104, 255}
// #define PONG_COLOR_3 (Color){237, 180, 161, 255}
  
// Mist GB
// #define PONG_COLOR_0 (Color){45, 27, 0, 255}
// #define PONG_COLOR_1 (Color){30, 96, 110, 255}
// #define PONG_COLOR_2 (Color){90, 185, 168, 255}
// #define PONG_COLOR_3 (Color){196, 240, 194, 255}

// Gold GB
#define PONG_COLOR_0 (Color) {33, 11, 27, 255}
#define PONG_COLOR_1 (Color) {77, 34, 44, 255}
#define PONG_COLOR_2 (Color) {157, 101, 76, 255}
#define PONG_COLOR_3 (Color) {207, 171, 81, 255}

#endif // __PONG_CONFIG_H__
