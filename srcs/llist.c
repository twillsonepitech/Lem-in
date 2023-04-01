/**
 * @file llist.c
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"

static struct linked_list_s *list_create_element(const char *description, uint32_t room)
{
    struct linked_list_s *list = (struct linked_list_s *) malloc(sizeof(struct linked_list_s));

    if (list == NULL)
        return NULL;
    list->_description = strdup(description);
    list->_room = room;
    list->_next = NULL;
    return list;
}

bool list_add_element_at_end(struct linked_list_s **list, const char *description, uint32_t room)
{
    struct linked_list_s *tmp = NULL;
    struct linked_list_s *element = list_create_element(description, room);

    if (element == NULL)
        return false;
    if (*list == NULL) {
        *list = element;
    } else {
        for (tmp = *list; tmp->_next != NULL; tmp = tmp->_next);
        tmp->_next = element;
    }
    return true;
}

void list_print_elements(struct linked_list_s **list)
{
    for (struct linked_list_s *tmp = *list; tmp != NULL; tmp = tmp->_next) {
        fprintf(stdout, "%s\n", tmp->_description);
    }
}

void list_delete_elements(struct linked_list_s **list)
{
    struct linked_list_s *element = NULL;

    while (*list != NULL) {
        element = *list;
        *list = (*list)->_next;
        free(element->_description);
        free(element);
    }
}

size_t list_get_size(struct linked_list_s **list)
{
    size_t cnt = 0;

    for (struct linked_list_s *tmp = *list; tmp != NULL; tmp = tmp->_next)
        cnt++;
    return cnt;
}

void list_print_title_and_elements(const char *title, struct linked_list_s **list)
{
    dprintf(STDOUT_FILENO, "%s\n", title);
    list_print_elements(list);
}
