/**
 * @file parser.c
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "array.h"
#include "structs.h"

static void *init_links(uint32_t number_of_rooms, struct links_s **links)
{
    *links = (struct links_s *) malloc(sizeof(struct links_s) * number_of_rooms);

    if (*links == NULL)
        return NULL;
    return memset(*links, 0, sizeof(struct links_s) * number_of_rooms);
}

int parse_tunnels(uint32_t number_of_rooms, struct links_s **links, struct linked_list_s **tunnels)
{
    char **connection = NULL;

    if (init_links(number_of_rooms, links) == NULL)
        return EXIT_FAILURE_EPI;
    for (struct linked_list_s *tmp = *tunnels; tmp != NULL; tmp = tmp->_next) {
        connection = my_str_to_word_array(tmp->_description, "-");
        if (connection == NULL)
            return EXIT_FAILURE_EPI;
        int a = atoi(connection[0]), b = atoi(connection[1]);
        (*links)[a]._tunnels_link = realloc((*links)[a]._tunnels_link, sizeof(struct links_s) * ((*links)[a]._index + 1));
        (*links)[a]._tunnels_link[(*links)[a]._index++] = b;
        (*links)[b]._tunnels_link = realloc((*links)[b]._tunnels_link, sizeof(struct links_s) * ((*links)[b]._index + 1));
        (*links)[b]._tunnels_link[(*links)[b]._index++] = a;
        free_array(connection);
    }
    return EXIT_SUCCESS;
}
