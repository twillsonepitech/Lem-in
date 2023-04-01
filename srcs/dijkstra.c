/**
 * @file dijkstra.c
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
#include <stdbool.h>
#include "moves.h"
#include "structs.h"

static uint32_t my_abs(int32_t x)
{
    return x < 0 ? -x : x;
}

static uint32_t init_edges_size(uint32_t number_of_rooms, struct links_s *links)
{
    (void) number_of_rooms;
    uint32_t edges_size = 0;

    for (uint32_t i = 0; i < number_of_rooms; i++) {
        edges_size += links[i]._index;
    }
    return edges_size;
}

static struct edges_s *init_edges(uint32_t number_of_rooms, struct links_s *links, uint32_t edges_size)
{
    struct edges_s *edges = NULL;
    uint32_t index = 0;

    edges = (struct edges_s *) malloc(sizeof(struct edges_s) * edges_size);
    (void) memset(edges, 0, sizeof(struct edges_s) * edges_size);
    for (uint32_t i = 0; i < number_of_rooms; i++) {
        for (uint32_t j = 0; j < links[i]._index; j++, index++) {
            edges[index]._from_room_id = i;
            edges[index]._to_room_id = links[i]._tunnels_link[j];
            edges[index]._distance = my_abs(i - links[i]._tunnels_link[j]);
        }
    }
    return edges;
}

static struct dijkstra_s init_dijkstra(uint32_t start_room, uint32_t number_of_rooms, struct links_s *links)
{
    struct dijkstra_s dijkstra = {
        ._visited = (bool *) malloc(sizeof(bool) * number_of_rooms),
        ._distance = (int *) malloc(sizeof(int) * number_of_rooms),
        ._parent = (int *) malloc(sizeof(int) * number_of_rooms),
        ._edges_size = init_edges_size(number_of_rooms, links),
    };

    dijkstra._edges = init_edges(number_of_rooms, links, dijkstra._edges_size);
    (void) memset(dijkstra._visited, false, sizeof(bool) * number_of_rooms);
    for (uint32_t i = 0; i < number_of_rooms; i++)
        dijkstra._distance[i] = INF;
    (void) memset(dijkstra._parent, -1, sizeof(int) * number_of_rooms);
    dijkstra._distance[start_room] = 0;
    return dijkstra;
}

static void destroy_dijkstra(struct dijkstra_s dijkstra)
{
    free(dijkstra._visited);
    free(dijkstra._distance);
    free(dijkstra._parent);
    free(dijkstra._edges);
}

static struct dijkstra_s find_strongly_connected_components(struct dijkstra_s dijkstra, int u, struct edges_s *edges)
{
    for (uint32_t i = 0; i < dijkstra._edges_size; i++) {
        if (edges[i]._from_room_id == u) {
            int v = edges[i]._to_room_id;
            int new_distance = dijkstra._distance[u] + edges[i]._distance;
            if (new_distance < dijkstra._distance[v]) {
                dijkstra._distance[v] = new_distance;
                dijkstra._parent[v] = u;
            }
        }
    }
    return dijkstra;
}

int dijkstra(uint32_t start_room, uint32_t end_room, struct lemin_s *lemin)
{
    struct dijkstra_s dijkstra = init_dijkstra(start_room, lemin->_number_of_rooms, lemin->_links);

    while (dijkstra._visited[end_room] == false) {
        int u = -1;
        for (uint32_t i = 0; i < lemin->_number_of_rooms; i++) {
            if (dijkstra._visited[i] == false && (u == -1 || dijkstra._distance[i] < dijkstra._distance[u]))
                u = i;
        }
        dijkstra._visited[u] = true;
        dijkstra = find_strongly_connected_components(dijkstra, u, dijkstra._edges);
    }
    handle_moves(lemin, end_room, dijkstra._parent);
    destroy_dijkstra(dijkstra);
    return EXIT_SUCCESS;
}
