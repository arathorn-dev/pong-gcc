#include "./includes/utils.h"

List_t *init_list(void)
{
    List_t *list = MemAlloc(sizeof(List_t));
    if (list == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize List_t pointer.");
        return NULL;
    }

    list->data = NULL;
    list->next = NULL;
    list->type = EMPTY_E;

    return list;
}
void add_element_list(List_t *const list, ObjectType type, void *data)
{
    List_t *aux = list;
    while (aux->next != NULL)
        aux = aux->next;

    aux->next = (List_t *)MemAlloc(sizeof(List_t));
    aux->next->data = data;
    aux->next->type = type;
    aux->next->next = NULL;
}

void *get_element_list(const List_t *list, size_t position)
{
    size_t counter = 0;
    const List_t *aux = list;
    void *value = NULL;

    while (aux->next != NULL)
    {
        if (counter == position)
        {
            value = aux->data;
            break;
        }
        aux = aux->next;
    }

    return value;
}

void close_list(List_t **ptr)
{
    if (ptr != NULL)
    {
        List_t *aux = (*ptr);
        while (aux->next != NULL)
        {
            List_t *el = aux;
            aux = aux->next;
            if (el->data != NULL)
            {
                MemFree(el->data);
                el->data = NULL;
            }
            MemFree(el);
            el = NULL;
        }
        (*ptr) = NULL;
    }
}