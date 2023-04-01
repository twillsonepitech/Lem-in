/**
 * @file array.c
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **my_str_to_word_array(const char *buffer, const char *delim)
{
    char *cpy = strdup(buffer);
    char **array = (char **) malloc(sizeof(char *) * (strlen(buffer) + 1));
    char *token = NULL;
    int i = 0;

    if (array == NULL)
        return NULL;
    token = strtok(cpy, delim);
    while (token != NULL) {
        array[i++] = strdup(token);
        token = strtok(NULL, delim);
    }
    free(cpy);
    array[i] = NULL;
    return array;
}

size_t length_array(char **array)
{
    size_t cnt = 0;

    for (int i = 0; array[i] != NULL; i++)
        cnt++;
    return cnt;
}

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
