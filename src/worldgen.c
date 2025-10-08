include "worldgen.h"

/**
 * Starts world generation using parameters in the config file.
 * This function replaces all earlier versions.
 * Exits on error. Does not return an error code.
 */
void start_world_gen(const char* config_path){
    // Implementation would go here
}

/**
 * Loads world generation parameters from an INI-style config file.
 * Any missing values fall back to defaults.
 */
//WorldGenConfig load_config(const char* path);(Dont use)

/**
 * Returns true if there are more rooms to read using get_next_room.
 */
bool has_more_rooms(void){
    // Implementation would go here
    return false; // Placeholder
}

/**
 * Returns the next room in the sequence.
 * 
 * Each call returns a copy of the next room (not a pointer).
 */
Room get_next_room(void){
    // Implementation would go here
    Room room = {0}; // Placeholder
    return room;
}

/**
 * Returns a pointer to a room by index (0-based).
 * Returns NULL if the index is out of bounds.
 */
const Room* get_room_by_index(int index){
    // Implementation would go here
    return NULL; // Placeholder
}

/**
 * Frees all memory used by the world generator.
 * Call this after you're done using the world.
 */
void stop_world_gen(void){
    // Implementation would go here
}

