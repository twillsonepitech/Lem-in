/**
 * @file llist.h
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LLIST_H_
#define LLIST_H_

#include <stdbool.h>
#include "structs.h"

bool list_add_element_at_end(struct linked_list_s **list, const char *description, uint32_t room);
void list_delete_elements(struct linked_list_s **list);
void list_print_elements(struct linked_list_s **list);
size_t list_get_size(struct linked_list_s **list);
void list_print_title_and_elements(const char *title, struct linked_list_s **list);

#endif /* !LLIST_H_ */
