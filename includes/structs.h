/**
 * @file structs.h
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

static const uint64_t INF = 1e9;

#define LISTS_SIZE          (4)
#define EXIT_FAILURE_EPI    (84)

enum info_e {
    NONE,
    ROOMS,
    START,
    END,
    TUNNEL
};

enum field_e {
    INDEX,
    STATUS
};

struct buffer_management_s {
    char *_buffer;
    size_t _n;
    ssize_t _rd;
};

struct linked_list_s {
    char *_description;
    uint32_t _room;
    struct linked_list_s *_next;
};

struct ants_s {
    enum info_e _status;
    struct ants_s *_next;
    uint32_t _id;
    uint32_t _index;
};

struct links_s {
    int32_t *_tunnels_link;
    uint32_t _index;
};

struct edges_s {
    int32_t _distance;
    int32_t _from_room_id;
    int32_t _to_room_id;
};

struct dijkstra_s {
    bool *_visited;
    int32_t *_distance;
    int32_t *_parent;
    struct edges_s *_edges;
    uint32_t _edges_size;
};

struct lemin_s {
    enum info_e _info;
    struct ants_s *_ants;
    struct linked_list_s *_list_end;
    struct linked_list_s *_list_room;
    struct linked_list_s *_list_start;
    struct linked_list_s *_list_tunnel;
    struct links_s *_links;
    uint32_t _number_of_ants;
    uint32_t _number_of_moves;
    uint32_t _number_of_rooms;
};

#endif /* !STRUCTS_H_ */
