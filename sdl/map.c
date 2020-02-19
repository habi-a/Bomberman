/*
** ETNA PROJECT, 10/02/2020 by habi_a
** c:\Users\habiy\Documents\blockerman\sdl
** File description:
**      Le fichier principale
*/

#include "map.h"

#include <stdio.h>
#include <stdlib.h>

static int file_count(const char *file)
{
    char ch = '\0';
    int count = 0;
    FILE *fptr = fopen(file, "r");

    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == 'W' || ch == 'X')
            count++;
    }
    fclose(fptr);
    return (count);
}

static map_t *map_init(SDL_Renderer *renderer)
{
    map_t *map = malloc(sizeof(map_t));

    map->i_max = 0;
    map->j_max = 0;
    map->nb_block = 0;
    map->block_texture = load_block_texture(renderer, "./block.png");
    map->wall_texture = load_block_texture(renderer, "./wall.png");
    map->floor_texture = load_block_texture(renderer, "./floor.png");
    map->block = NULL;
    return (map);
}

map_t *map_load(SDL_Renderer *renderer, int tile_size
                                    , const char *file)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int read = 0;
    char *line = NULL;
    long unsigned int len = 0;
    FILE *fp = fopen(file, "r");
    map_t *map = map_init(renderer);


    map->nb_block = file_count(file);
    map->block = malloc(map->nb_block * sizeof(block_t *));
    printf("test\n");
    while ((read = getline(&line, &len, fp)) != -1 && k < map->nb_block) {
        for (i = 0; i < read && line[i] != '\n'; i++) {
            if (line[i] == 'W') {
                map->block[k++] = block_load(map->wall_texture, i, j, tile_size);
            }
            else if (line[i] == 'X')
                map->block[k++] = block_load(map->block_texture, i, j, tile_size);
        }
        j++;
    }
    fclose(fp);
    map->i_max = i;
    map->j_max = j;
    if (line != NULL) {
        free(line);
    }
    return (map);
}

void map_draw(map_t *map, SDL_Renderer *renderer, int tilesize)
{
    for (int j = 0; j < map->j_max; j++)
        for (int i = 0; i < map->i_max; i++) {
            SDL_Rect tmp_pos = { i * tilesize, j * tilesize, tilesize, tilesize};
            SDL_RenderCopy(renderer, map->floor_texture, NULL, &(tmp_pos));
        }
    for (int i = 0; i < map->nb_block; i++)
        block_draw(map->block[i], renderer);
}


void map_destroy(map_t *map)
{
    if (map != NULL) {
        if (map->block != NULL) {
            for (int i = 0; i < map->nb_block; i++)
                block_destroy(map->block[i]);
            if (map->block_texture != NULL)
                SDL_DestroyTexture(map->block_texture);
            if (map->wall_texture != NULL)
                SDL_DestroyTexture(map->wall_texture);
            if (map->floor_texture != NULL)
                SDL_DestroyTexture(map->floor_texture);
            free(map->block);
        }
        free(map);
    }
}
