#ifndef __PACKAGE_H__
#define __PACKAGE_H__

#include "../config.h"

typedef enum
{
    FONT_04B_03_E,
} FontEnum;

PONG typedef struct
{
    Font fonts[1];
} Package_t;

#if defined(__cplusplus)
extern "C"
{
#endif
    PONG Package_t *create_package(void);
    PONG void close_package(Package_t **);

#if defined(__cplusplus)
}
#endif

#endif //__PACKAGE_H__