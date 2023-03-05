#ifndef __PONG_CONFIG_H__
#define __PONG_CONFIG_H__

#include <stdint.h>
#include <stddef.h>
#include "includes/raylib.h"
#include "includes/raymath.h"

#define PONG
#define PONG_DEBUG 1

//----------------------------------------------------------------------------------
// Config screen
//----------------------------------------------------------------------------------
#define PONG_WIDTH 640
#define PONG_HEIGHT 480
#define PONG_TITLE "Pong 1.0v"

//----------------------------------------------------------------------------------
// Config info
//----------------------------------------------------------------------------------
#define PONG_FPS 30
#define PONG_VOLUME 0.2

//----------------------------------------------------------------------------------
// Config text
//----------------------------------------------------------------------------------
#define PONG_AUTHOR "Created by Arathorn 2023"

//----------------------------------------------------------------------------------
// Config init.data
//----------------------------------------------------------------------------------
#define PONG_INIT_FILE "data/init.data"
#define PONG_TOKEN_THEME "THEME"
#define PONG_TOKEN_EQUAL "="

#endif // __PONG_CONFIG_H__
