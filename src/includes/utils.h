#ifndef __UTILS_H__
#define __UTILS_H__
#include "../config.h"

//----------------------------------------------------------------------------------
// struct List.
//----------------------------------------------------------------------------------
PONG typedef enum {
    EMPTY_E,
    SCREEN_E,
} ObjectType;

PONG typedef struct List_t
{
    void *data;
    ObjectType type;
    struct List_t *next;
} List_t;

#if defined(__cplusplus)
extern "C"
{
#endif

    PONG List_t *init_list(void);
    PONG void add_element_list(List_t *const, ObjectType type, void *);
    PONG void *get_element_list(const List_t *, size_t);
    PONG void close_list(List_t **);

#if defined(__cplusplus)
}
#endif

#endif //__UTILS_H__