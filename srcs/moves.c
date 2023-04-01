/**
 * @file moves.c
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "ants.h"
#include "structs.h"

static int *reverse(int *array, int n)
{
    for (int i = 0, r = n - 1, tmp = 0; i < r; i++, r--) {
        tmp = array[i];
        array[i] = array[r];
        array[r] = tmp;
    }
    return array;
}

static void handle_first_ants_which_start(struct ants_s **ants, struct links_s *links, struct linked_list_s **list_start)
{
    uint32_t number_of_the_ant = 1;

    for (struct linked_list_s *tmp = *list_start; tmp != NULL; tmp = tmp->_next) {
        for (uint32_t i = 0; i < links[tmp->_room]._index; i++) {
            printf("P%d-%d:", number_of_the_ant, links[tmp->_room]._tunnels_link[i]);
            list_ants_modify_field(ants, number_of_the_ant, INDEX, NONE);
            list_ants_modify_field(ants, number_of_the_ant, STATUS, START);
            number_of_the_ant++;
        }
    }
    printf("\n");
}

static void handle_ants_until_reanching_end(struct ants_s **ants, uint32_t number_of_ants, int32_t *path, uint32_t index)
{
    while (list_ants_reached_end(ants, number_of_ants) == false) {
        for (struct ants_s *tmp = *ants; tmp != NULL; tmp = tmp->_next) {
            if (tmp->_status == END)
                continue;
            printf("P%d-%d:", tmp->_id, path[tmp->_index]);
            list_ants_modify_field(ants, tmp->_id, INDEX, NONE);
            if (tmp->_index == index)
                list_ants_modify_field(ants, tmp->_id, STATUS, END);
            if (tmp->_status == NONE) {
                list_ants_modify_field(ants, tmp->_id, STATUS, START);
                break;
            }
        }
        printf("\n");
    }
}

int handle_moves(struct lemin_s *lemin, uint32_t end_room, int32_t *parent)
{
    int32_t *path = NULL;
    uint32_t index = 0;

    for (int32_t v = end_room; v != -1; v = parent[v]) {
        path = realloc(path, sizeof(int) * (index + 1));
        path[index++] = v;
    }
    path = reverse(path, index);
    dprintf(STDOUT_FILENO, "#moves\n");
    handle_first_ants_which_start(&lemin->_ants, lemin->_links, &lemin->_list_start);
    handle_ants_until_reanching_end(&lemin->_ants, lemin->_number_of_ants, &path[1], index - 1);
    free(path);
    return EXIT_SUCCESS;
}
