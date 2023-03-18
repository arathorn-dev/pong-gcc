#ifndef __PONG_CONFIG_H__
#define __PONG_CONFIG_H__

#include <stdint.h>
#include <stddef.h>
#include "includes/raylib.h"
#include "includes/raymath.h"

#define PONG
#define PONG_DEBUG 1

//----------------------------------------------------------------------------------
// Config screen.
//----------------------------------------------------------------------------------
#define PONG_SCREEN_WIDTH 640
#define PONG_SCREEN_HEIGHT 480
#define PONG_SCREEN_TITLE "Pong 1.0v"

//----------------------------------------------------------------------------------
// Config info.
//----------------------------------------------------------------------------------
#define PONG_FPS 30
#define PONG_VOLUME 0.2
#define PONG_MAX_SCORE 2

//----------------------------------------------------------------------------------
// Config sizes.
//----------------------------------------------------------------------------------
#define PONG_WIDTH 20
#define PONG_HEIGHT 100
#define PONG_GUI_HEIGHT 50
#define PONG_SCORE_SPACE 10.0f
#define PONG_PALETTE_SPACE 0
#define PONG_COUNTER_WINNER_PAGE 3.0f

//----------------------------------------------------------------------------------
// Config text.
//----------------------------------------------------------------------------------
#define PONG_AUTHOR "Created by Arathorn 2023"

//----------------------------------------------------------------------------------
// Config particles.
//----------------------------------------------------------------------------------
#define PONG_MAX_PARTICLES 20

//----------------------------------------------------------------------------------
// Config init.data
//----------------------------------------------------------------------------------
#define PONG_INIT_FILE "data/init.data"
#define PONG_TOKEN_THEME "THEME"
#define PONG_TOKEN_EQUAL "="

#endif // __PONG_CONFIG_H__
