#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

/**
 * Compass directions used to connect rooms and place doors.
 * 
 * The order of values must not be changed — code relies on DIR_NORTH = 0
 * and NUM_DIRECTIONS = 4 for array indexing (e.g., neighbor_ids[...]).
 */
typedef enum {
    DIR_NORTH = 0,
    DIR_SOUTH,
    DIR_EAST,
    DIR_WEST,
    NUM_DIRECTIONS
} Direction;

/**
 * Represents a monster placed inside a room.
 * 
 * Monsters are stored in a dynamically allocated array within each room.
 * Each monster has a display character, name, and simple combat stats.
 */
typedef struct {
    int id;             // Unique ID for this monster instance
    int x, y;           // Tile location within the room grid
    char symbol;        // Character used for rendering (e.g., 'G')
    const char* name;   // Display name (e.g., "Goblin")
    int hp;             // Current health
    int attack;         // Damage dealt when attacking
} Monster;

/**
 * Represents an item placed inside a room.
 * 
 * Items are passive — they do not have combat stats.
 * Each item has a location, a symbol, and a display name.
 */
typedef struct {
    int id;             // Unique ID for this item instance
    int x, y;           // Tile location within the room grid
    char symbol;        // Character used for rendering (e.g., '*')
    const char* name;   // Display name (e.g., "Potion")
} Item;

/**
 * Represents a door located on a wall of a room.
 * 
 * Doors have a tile location (`x`, `y`) within the room
 * and a direction (`dir`) that indicates which wall the door is on.
 */
typedef struct {
    int x, y;           // Position within the room grid
    Direction dir;      // Wall direction (e.g., DIR_NORTH = top wall)
} Door;

/**
 * Represents a single room in the dungeon.
 * 
 * Each room has:
 * - A grid of tiles (`width` × `height`)
 * - Up to four neighbors (linked by ID in `neighbor_ids`)
 * - Arrays of monsters, items, and doors
 * 
 * Memory for monsters, items, and doors is dynamically allocated.
 */
typedef struct {
    int id;                         // Unique room ID

    int width, height;             // Tile grid size

    int neighbor_ids[NUM_DIRECTIONS]; 
    // Neighboring room IDs: one per direction. Use -1 if no neighbor.

    bool is_start;                 // True if this is the starting room
    bool is_exit;                  // True if this is the exit room

    int grid_placement;            // Used for UI layout in A2 (ignore in A1)

    int num_monsters;              // Number of monsters in this room
    Monster* monsters;             // Dynamically allocated array

    int num_items;                 // Number of items in this room
    Item* items;                   // Dynamically allocated array

    int num_doors;                 // Number of doors in this room
    Door* doors;                   // Dynamically allocated array
} Room;

/**
 * Represents the player character.
 * 
 * Tracks the player’s location and health.
 * The controller ensures that tile coordinates are always valid.
 */
typedef struct {
    Room * current_room;          // The room the player is in
    int tile_x, tile_y;           // Position within the room grid
    int health;                   // Current health value
    bool alive;                   // True if the player is alive
} Player;

#endif // STRUCTS_H