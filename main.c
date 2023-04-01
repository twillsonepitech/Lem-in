/**
 * @file main.c
 * @author thomas willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include "lemin.h"

int main(int argc, __attribute__((unused)) char const *argv[])
{
    if (argc != 1) {
        fprintf(stderr, "USAGE: ./lemin < [FILE]\n");
        return 84;
    }
    return handle_file();
}
