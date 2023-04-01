/**
 * @file lemin.c
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ants.h"
#include "array.h"
#include "dijkstra.h"
#include "llist.h"
#include "parser.h"

bool get_number_of_ants(struct lemin_s *lemin, long long number_of_ants)
{
    if (lemin->_number_of_ants == 0) {
        lemin->_number_of_ants = number_of_ants;
        lemin->_info = ROOMS;
        return true;
    }
    return false;
}

int swap_info(struct lemin_s *lemin, const char *buffer)
{
    if (strcmp(buffer, "##start") == EXIT_SUCCESS) {
        lemin->_info = START;
        return true;
    }
    if (strcmp(buffer, "##end") == EXIT_SUCCESS) {
        lemin->_info = END;
        return true;
    }
    for (size_t i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '-')
            lemin->_info = TUNNEL;
    }
    return false;
}

void get_rooms(struct lemin_s *lemin, const char *description, uint32_t room)
{
    struct linked_list_s **list_rooms[LISTS_SIZE] = {&lemin->_list_room, &lemin->_list_start, &lemin->_list_end, &lemin->_list_tunnel};
    enum info_e info[LISTS_SIZE] = {ROOMS, START, END, TUNNEL};

    for (size_t i = 0; i < LISTS_SIZE; i++) {
        if (lemin->_info == info[i])
            list_add_element_at_end(list_rooms[i], description, room);
    }
    return;
}

static void free_lemin(struct lemin_s *lemin)
{
    list_ants_free_elements(&lemin->_ants);
    list_delete_elements(&lemin->_list_room);
    list_delete_elements(&lemin->_list_start);
    list_delete_elements(&lemin->_list_end);
    list_delete_elements(&lemin->_list_tunnel);
    for (uint32_t i = 0; i < lemin->_number_of_rooms; i++)
        free(lemin->_links[i]._tunnels_link);
    free(lemin->_links);
}

int apply_dijkstra_algorithm(struct lemin_s *lemin)
{
    lemin->_number_of_rooms = list_get_size(&lemin->_list_room) + list_get_size(&lemin->_list_start) + list_get_size(&lemin->_list_end);
    if (list_ants_init(&lemin->_ants, lemin->_number_of_ants) == EXIT_FAILURE_EPI)
        return EXIT_FAILURE_EPI;
    fprintf(stdout, "#number_of_ants\n%d\n", lemin->_number_of_ants);
    list_print_title_and_elements("#rooms", &lemin->_list_room);
    list_print_title_and_elements("##start", &lemin->_list_start);
    list_print_title_and_elements("##end", &lemin->_list_end);
    list_print_title_and_elements("#tunnels", &lemin->_list_tunnel);
    parse_tunnels(lemin->_number_of_rooms, &lemin->_links, &lemin->_list_tunnel);
    dijkstra(lemin->_list_start->_room, lemin->_list_end->_room, lemin);
    free_lemin(lemin);
    return EXIT_SUCCESS;
}

int handle_file(void)
{
    struct buffer_management_s buffer_management = {0};
    struct lemin_s lemin = {0};
    char **array = NULL;

    while (true) {
        buffer_management._rd = getline(&buffer_management._buffer, &buffer_management._n, stdin);
        if (buffer_management._rd == -1)
            break;
        buffer_management._buffer[buffer_management._rd - 1] = '\0';
        if ((buffer_management._buffer[0] == '#' && buffer_management._buffer[1] != '#')
        || get_number_of_ants(&lemin, atoll(buffer_management._buffer)) == true
        || swap_info(&lemin, buffer_management._buffer) == true)
            continue;
        array = my_str_to_word_array(buffer_management._buffer, " \t");
        get_rooms(&lemin, buffer_management._buffer, atoll(array[0]));
        free_array(array);
    }
    free(buffer_management._buffer);
    return apply_dijkstra_algorithm(&lemin);
}
