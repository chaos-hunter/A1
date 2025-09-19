/* tree.h */
#ifndef TREE_H
#define TREE_H

typedef struct Tree Tree;

/*
 * Status codes returned by tree operations
 */
typedef enum {
    TREE_OK,
    TREE_DUPLICATE,
    TREE_NOT_FOUND,
    TREE_ERROR
} TreeStatusCode;

/*
 * Tree structure stores user data and performs comparisons via provided functions.
 *
 * - All data is treated as opaque.
 * - Duplicate values are inserted to the right (duplicates allowed).
 * - Returned pointers from findData should not be modified or assumed valid after tree changes.
 * - Tree does not free user data unless a destroy function is provided.
 */

/*
 * Create a new tree with function pointers for:
 *   - printing (required),
 *   - comparing (required),
 *   - destroying user data (optional).
 *
 * Returns NULL if print or compare functions are missing or if allocation fails.
 */
Tree *createTree(void (*printFunction)(const void *data),
                 int (*compareFunction)(const void *a, const void *b),
                 void (*destroyFunction)( void *data));

/*
 * Destroy the tree and all its nodes.
 * If destroyFunction was provided, it will be called on each data element.
 */
void destroyTree(Tree *tree);

/*
 * Insert data into the tree.
 * Returns TREE_OK on success, TREE_DUPLICATE if the value already exists, or TREE_ERROR on failure.
 */
TreeStatusCode insertData(Tree *tree, void *data);

/*
 * Search for a matching data item.
 * Returns a pointer to the matching data, or NULL if not found.
 * The returned pointer must not be modified or stored.
 */
void *findData(Tree *tree, const void *key);

/*
 * Print the contents of the tree in sorted order using the printFunction.
 */
void printInOrder(Tree *tree);


// Tree Iterator
typedef struct TreeIterator TreeIterator;

// Iterator API
TreeIterator *createIterator(Tree *tree);
void *nextData(TreeIterator *iter);      // Returns NULL when done
void destroyIterator(TreeIterator *iter);

#endif /* TREE_H */