/**
 * @file array.h
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include <stddef.h>

char **my_str_to_word_array(const char *buffer, const char *delim);
size_t length_array(char **array);
void free_array(char **array);

#endif /* !ARRAY_H_ */
