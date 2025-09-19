#ifndef DUNGEON_CONTROLLER_H
#define DUNGEON_CONTROLLER_H

#include "structs.h"
#include "tree.h"
#include <stddef.h> // for size_t
#include <stdbool.h>

/**
 * This module manages the player and dungeon state during gameplay.
 * 
 * It allows access to rooms, movement, rendering, and tracking of
 * visited rooms. The dungeon controller is responsible for all
 * high-level logic in the game.
 * 
 * Students must call only the public functions listed below and
 * must not modify the controller internals directly.
 */

// -------------------------
// Status Codes
// -------------------------

/**
 * Return codes for all controller API functions.
 * 
 * These codes allow the caller to distinguish between success,
 * invalid inputs, not-found errors, memory issues, and more.
 */
typedef enum {
    CONTROLLER_OK,
    CONTROLLER_INVALID_ARGUMENT,
    CONTROLLER_NOT_FOUND,
    CONTROLLER_NO_DOOR,
    CONTROLLER_OUT_OF_BOUNDS,
    CONTROLLER_ALREADY_IN_ROOM,
    CONTROLLER_ALLOCATION_FAILED,
    CONTROLLER_ERROR
} ControllerStatusCode;

// -------------------------
// Controller Struct
// -------------------------

#define MAX_ROOMS 256  // Assumes room IDs range from 0 to MAX_ROOMS-1

/**
 * Represents the global dungeon controller state.
 * 
 * This struct contains all runtime information for the game,
 * including the dungeon layout, player state, and visited rooms.
 * 
 * Students should treat this as opaque and interact only via
 * the public controller_* functions.
 */
typedef struct Controller {
    Tree *room_tree;            // Tree of Room*, keyed by room ID
    Player player;              // Current player state
    int visited[MAX_ROOMS];     // visited[i] = 1 if room with ID i has been visited
    int max_room_id;            // Highest room ID encountered (inclusive)
} Controller;

// -------------------------
// Initialization & Cleanup
// -------------------------

/**
 * Creates and initializes the game controller.
 * 
 * This function loads the dungeon using the world generator config
 * and places the player in the starting room.
 * 
 * @param config_file Path to the worldgen .ini file
 * @return Pointer to the new controller, or NULL on failure
 */
Controller *controller_init(const char *config_file);

/**
 * Frees all memory associated with the controller.
 * 
 * This includes the tree, all rooms, and internal tracking arrays.
 */
void controller_free(Controller *ctrl);

// -------------------------
// Player and Room Access
// -------------------------

/**
 * Retrieves a pointer to the room the player is currently in.
 *
 * The pointer is valid as long as the controller exists.
 * Do not modify or free it.
 */
ControllerStatusCode get_current_room(const Controller *ctrl, const Room **room);

/**
 * Retrieves the ID of the room the player is currently in.
 */
ControllerStatusCode get_player_room_id(const Controller *ctrl, int *room_id_out);

/**
 * Looks up a room by its ID and returns a pointer to it.
 *
 * The pointer is valid as long as the controller exists.
 * Do not modify or free it.
 */
ControllerStatusCode get_room_by_id(const Controller *ctrl, int id, const Room **room);

/**
 * Gets the player’s current position within their current room.
 * 
 * Output values `x` and `y` are tile coordinates in the room grid.
 */
ControllerStatusCode get_player_position(const Controller *ctrl, int *x, int *y);

/**
 * Retrieves the player's current health value.
 */
ControllerStatusCode get_player_health(const Controller *ctrl, int *hp);

/**
 * Returns whether the player is still alive.
 * 
 * The output is 1 if alive, 0 if dead.
 */
ControllerStatusCode is_player_alive(const Controller *ctrl, bool *alive);

// -------------------------
// Movement
// -------------------------

/**
 * Attempts to move the player by (dx, dy) tiles within the current room.
 * 
 * Fails with CONTROLLER_OUT_OF_BOUNDS if the destination is outside
 * the room grid, or CONTROLLER_INVALID_ARGUMENT for null input.
 */
ControllerStatusCode move_player_within_room(Controller *ctrl, int dx, int dy);

/**
 * Attempts to move the player through a door in the given direction.
 * 
 * Fails with CONTROLLER_NO_DOOR if no door exists on that wall,
 * or CONTROLLER_NOT_FOUND if the neighboring room is invalid.
 */
ControllerStatusCode move_player_direction(Controller *ctrl, Direction dir);

// -------------------------
// Rendering
// -------------------------

/**
 * Renders the room the player is currently in.
 * 
 * The function allocates a printable string describing the room’s contents.
 * The caller must free the string using `free()` when done.
 */
ControllerStatusCode render_current_room(const Controller *ctrl, char **str);

/**
 * Renders a specific room by ID.
 * 
 * The function allocates a printable string describing the room’s contents.
 * The caller must free the string using `free()` when done.
 */
ControllerStatusCode render_room_by_id(const Controller *ctrl, const int room_id, char **str);

// -------------------------
// Visited Rooms
// -------------------------

/**
 * Returns a dynamically allocated array of visited room IDs.
 * 
 * The array contains all room IDs that have been marked as visited.
 * The caller must free the array after use.
 */
ControllerStatusCode get_visited_room_ids(const Controller *ctrl, int **ids, size_t *count);

// -------------------------
// Tile Validity
// -------------------------

/**
 * Determines if a tile (x, y) is walkable in the given room.
 * 
 * A tile is walkable if it lies within bounds and does not contain
 * a monster, item, or wall.
 *
 * The result is returned via the `result` pointer (true = walkable).
 */
ControllerStatusCode is_walkable(const Room *room, int x, int y, bool *result);

#endif // DUNGEON_CONTROLLER_H