#ifndef WORLDGEN_H
#define WORLDGEN_H
#include <stdbool.h>
#include "structs.h"

/**
 * Configuration options for world generation.
 */
typedef struct {
    int num_rooms;
    int map_width;
    int map_height;
    int base_room_width;
    int base_room_height;
    int room_size_variance;
    int max_monsters_per_room;
    int max_items_per_room;
    int monster_spawn_chance;
    int item_spawn_chance;
} WorldGenConfig;

/**
 * Starts world generation using parameters in the config file.
 * This function replaces all earlier versions.
 * Exits on error. Does not return an error code.
 */
void start_world_gen(const char* config_path);

/**
 * Loads world generation parameters from an INI-style config file.
 * Any missing values fall back to defaults.
 */
WorldGenConfig load_config(const char* path);

/**
 * Returns true if there are more rooms to read using get_next_room.
 */
bool has_more_rooms(void);

/**
 * Returns the next room in the sequence.
 * 
 * Each call returns a copy of the next room (not a pointer).
 */
Room get_next_room(void);

/**
 * Returns a pointer to a room by index (0-based).
 * Returns NULL if the index is out of bounds.
 */
const Room* get_room_by_index(int index);

/**
 * Frees all memory used by the world generator.
 * Call this after you're done using the world.
 */
void stop_world_gen(void);

#endif