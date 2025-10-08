#include "dungeon_controller.h"
/**
 * Loads a procedurally generated dungeon from a config file.
 * 
 * Rooms are created by invoking the world generator from within `load_dungeon()`
 * and are then inserted into a balanced binary tree using comparison, copy, and 
 * destroy functions appropriate for `Room` structs. Rooms are ordered by their `id` 
 * field in the tree.
 * 
 * The caller owns the returned Tree* and must call destroyTree() when done.
 *
 * Optional output parameters:
 *  - `first_room_out`: receives a pointer to the starting room (i.e., the room with is_start = true).
 *  - `num_rooms_out`: receives the total number of rooms inserted into the tree.
 * 
 * @param config_file      Path to the worldgen config file (.ini)
 * @param first_room_out   Optional; pointer to receive the first Room*
 * @param num_rooms_out    Optional; pointer to receive total room count
 * 
 * @return Pointer to the tree containing all Room* nodes, or NULL on failure
 *         (e.g., file not found, parsing error, memory allocation failure).
 */
Tree *load_dungeon(const char *config_file, Room **first_room_out, int *num_rooms_out){
    return NULL;
}