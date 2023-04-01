/**
 * @file ants.h
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ANTS_H_
#define ANTS_H_

#include <stdbool.h>
#include "structs.h"

bool list_ants_add_element_at_end(struct ants_s **ants, uint32_t id, uint32_t index);
void list_ants_free_elements(struct ants_s **ants);
int list_ants_init(struct ants_s **ants, uint32_t number_of_ants);
void list_ants_modify_field(struct ants_s **ants, uint32_t id, enum field_e field, enum info_e status);
bool list_ants_reached_end(struct ants_s **ants, uint32_t number_of_ants);

#endif /* !ANTS_H_ */
