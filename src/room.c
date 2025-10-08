include "room.h"

/**
 * This module defines operations on Room structures.
 * 
 * The `Room` struct is the data type stored in the binary tree.
 * Each tree node holds a pointer to a Room, and the tree uses the
 * functions below to manage its contents.
 * 
 * These functions are required for loading, comparing, duplicating,
 * and releasing Room data in a modular system.
 */

/**
 * Compares two Room objects by ID.
 *
 * Used by the tree to maintain ordering. Rooms with lower IDs are
 * placed in the left subtree; higher IDs go to the right.
 *
 * @param a Pointer to a Room (as void*)
 * @param b Pointer to a Room (as void*)
 * @return Negative if a < b, 0 if equal, positive if a > b
 */
int compare_rooms(const void *a, const void *b){
    const Room *room_a = (const Room *)a;
    const Room *room_b = (const Room *)b;
    return room_a->id - room_b->id;
}

/**
 * Creates a deep copy of a Room.
 *
 * This is used when inserting a Room into the tree. It must allocate
 * and copy all internal arrays (monsters, items, doors).
 *
 * @param data Pointer to the original Room (as void*)
 * @return Pointer to a new Room copy, or NULL on failure
 */
void *copy_room(void *data){
    Room *original = (Room *)data;
    if (original == NULL) {
        return NULL;
    }

    Room *copy = malloc(sizeof(Room));
    if (copy == NULL) {
        return NULL;
    }

    // Copy basic fields
    copy->id = original->id;
    copy->width = original->width;
    copy->height = original->height;

    // Copy monsters
    copy->num_monsters = original->num_monsters;
    if (copy->num_monsters > 0) {
        copy->monsters = malloc(copy->num_monsters * sizeof(Monster));
        if (copy->monsters == NULL) {
            free(copy);
            return NULL;
        }
        memcpy(copy->monsters, original->monsters, copy->num_monsters * sizeof(Monster));
    } else {
        copy->monsters = NULL;
    }

    // Copy items
    copy->num_items = original->num_items;
    if (copy->num_items > 0) {
        copy->items = malloc(copy->num_items * sizeof(Item));
        if (copy->items == NULL) {
            free(copy->monsters);
            free(copy);
            return NULL;
        }
        memcpy(copy->items, original->items, copy->num_items * sizeof(Item));
    } else {
        copy->items = NULL;
    }

    // Copy doors
    copy->num_doors = original->num_doors;
    if (copy->num_doors > 0) {
        copy->doors = malloc(copy->num_doors * sizeof(Door));
        if (copy->doors == NULL) {
            free(copy->items);
            free(copy->monsters);
            free(copy);
            return NULL;
        }
        memcpy(copy->doors, original->doors, copy->num_doors * sizeof(Door));
    } else {
        copy->doors = NULL;
    }

    return copy;
}

/**
 * Frees all memory associated with a Room.
 *
 * This includes the Room itself and any dynamically allocated arrays
 * of monsters, items, and doors.
 *
 * @param data Pointer to the Room to destroy (as void*)
 */
void destroy_room(void *data){
    Room *room = (Room *)data;
    if (room != NULL) {
        free(room->monsters);
        free(room->items);
        free(room->doors);
        free(room);
    }
}

/**
 * Prints a summary of a Room to stdout.
 *
 * Useful for debugging. Output format is not standardized.
 *
 * @param data Pointer to the Room to print (as void*)
 */
void print_room(const void *data){
    return;
} // Optional debug

/**
 * Returns the ID of a Room.
 *
 * This is a convenience wrapper often used in testing.
 *
 * @param room Pointer to a Room
 * @return Integer room ID
 */
int get_room_id(const Room *room){
    if (room == NULL) {
        return -1; // Indicate error
    }
    return room->id;
}

/**
 * Returns true if the given (x, y) coordinate is inside the room grid.
 * 
 * A tile is in bounds if 0 ≤ x < room->width and 0 ≤ y < room->height.
 * This check is commonly used before moving the player or placing items.
 *
 * @param room Pointer to the Room
 * @param x Tile x-coordinate
 * @param y Tile y-coordinate
 * @return true if the tile is valid, false if out of bounds
 */
bool is_in_bounds(const Room *room, int x, int y){
    if (room == NULL) {
        return false;
    }
    return (x >= 0 && x < room->width && y >= 0 && y < room->height);
}

