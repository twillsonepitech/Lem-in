/**
 * @file ants.c
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include "structs.h"

static struct ants_s *list_create_element(uint32_t id, uint32_t index)
{
    struct ants_s *element = (struct ants_s *) malloc(sizeof(struct ants_s));

    if (element == NULL)
        return NULL;
    element->_id = id;
    element->_index = index;
    element->_status = NONE;
    element->_next = NULL;
    return element;
}

bool list_ants_add_element_at_end(struct ants_s **ants, uint32_t id, uint32_t index)
{
    struct ants_s *tmp = NULL;
    struct ants_s *element = list_create_element(id, index);

    if (element == NULL)
        return false;
    if (*ants == NULL) {
        *ants = element;
    } else {
        for (tmp = *ants; tmp->_next != NULL; tmp = tmp->_next);
        tmp->_next = element;
    }
    return true;
}

void list_ants_free_elements(struct ants_s **ants)
{
    struct ants_s *element = NULL;

    while (*ants != NULL) {
        element = *ants;
        *ants = (*ants)->_next;
        free(element);
    }
}

int list_ants_init(struct ants_s **ants, uint32_t number_of_ants)
{
    for (uint32_t id = 1; id <= number_of_ants; id++) {
        if (list_ants_add_element_at_end(ants, id, 0) == false)
            return EXIT_FAILURE_EPI;
    }
    return EXIT_SUCCESS;
}

void list_ants_modify_field(struct ants_s **ants, uint32_t id, enum field_e field, enum info_e status)
{
    for (struct ants_s *tmp = *ants; tmp != NULL; tmp = tmp->_next) {
        if (tmp->_id == id) {
            if (field == INDEX)
                tmp->_index++;
            else
                tmp->_status = status;
        }
    }
}

bool list_ants_reached_end(struct ants_s **ants, uint32_t number_of_ants)
{
    size_t cnt = 0;

    for (struct ants_s *tmp = *ants; tmp != NULL; tmp = tmp->_next) {
        if (tmp->_status == END)
            cnt++;
    }
    return cnt == number_of_ants ? true : false;
}
