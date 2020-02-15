/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\bomberman\sdl
** File description:
**      Le fichier principale
*/

#include "bag.h"

#include <stdlib.h>

bag_t *bag_init()
{
    bag_t *bag;

    bag = malloc(sizeof(bag_t));
    if (bag == NULL)
        return (NULL);
    bag->first = NULL;
    bag->last = NULL;
    bag->size = 0;
    return (bag);
}

int bag_add(bag_t *bag)
{
    bomb_t *new_node;

    new_node = malloc(sizeof(bomb_t));
    if (new_node == NULL)
        return (0);
    new_node->prev = NULL;
    new_node->next = bag->first;
    if (bag->first)
        bag->first->prev = new_node;
    else
        bag->last = new_node;
    bag->first = new_node;
    bag->size++;
    return (1);
}

void bag_destroy(bag_t *bag)
{
    bomb_t *next;
    bomb_t *current = bag->first;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(bag);
}
