/* tree.c */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct TreeNode {
    void *data;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
} TreeNode;

struct Tree {
    TreeNode *root;
    void (*printFunction)(const void *data);
    int (*compareFunction)(const void *a, const void *b);
    void (*destroyFunction)(void *data);
};

static int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

static int height(TreeNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

static TreeNode *createNode(void *data) {
    if (data == NULL) return NULL;
    TreeNode *node = malloc(sizeof(TreeNode));
    if (!node) return NULL;
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

static void destroySubtree(TreeNode *node, void (*destroyFunction)(void *)) {
    if (node == NULL) return;
    destroySubtree(node->left, destroyFunction);
    destroySubtree(node->right, destroyFunction);
    if (destroyFunction)
        destroyFunction(node->data);
    free(node);
}

Tree *createTree(void (*printFunction)(const void *),
                int (*compareFunction)(const void *, const void *),
                void (*destroyFunction)(void *)) {
    if (!printFunction || !compareFunction) return NULL;
    Tree *tree = malloc(sizeof(Tree));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->printFunction = printFunction;
    tree->compareFunction = compareFunction;
    tree->destroyFunction = destroyFunction;
    return tree;
}

void destroyTree(Tree *tree) {
    if (!tree) return;
    destroySubtree(tree->root, tree->destroyFunction);
    free(tree);
}

static int getBalance(TreeNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

static TreeNode *rotateRight(TreeNode *y) {
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

static TreeNode *rotateLeft(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

static TreeNode *insertRecursive(Tree *tree, TreeNode *node, void *data, TreeStatusCode *status) {
    if (node == NULL) {
        *status = TREE_OK;
        return createNode(data);
    }
    int cmp = tree->compareFunction(data, node->data);
    if (cmp < 0) {
        node->left = insertRecursive(tree, node->left, data, status);
    } else if (cmp > 0) {
        node->right = insertRecursive(tree, node->right, data, status);
    } else {
        *status = TREE_DUPLICATE;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && tree->compareFunction(data, node->left->data) < 0)
        return rotateRight(node);
    if (balance < -1 && tree->compareFunction(data, node->right->data) > 0)
        return rotateLeft(node);
    if (balance > 1 && tree->compareFunction(data, node->left->data) > 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && tree->compareFunction(data, node->right->data) < 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

TreeStatusCode insertData(Tree *tree, void *data) {
    if (!tree || !data) return TREE_ERROR;
    TreeStatusCode status = TREE_OK;
    tree->root = insertRecursive(tree, tree->root, data, &status);
    return status;
}

static void *findRecursive(Tree *tree, TreeNode *node, const void *key) {
    if (!node) return NULL;
    int cmp = tree->compareFunction(key, node->data);
    if (cmp == 0) return node->data;
    if (cmp < 0) return findRecursive(tree, node->left, key);
    return findRecursive(tree, node->right, key);
}

void *findData(Tree *tree, const void *key) {
    if (!tree || !key) return NULL;
    return findRecursive(tree, tree->root, key);
}

static void printInOrderRecursive(TreeNode *node, void (*printFunction)(const void *)) {
    if (!node) return;
    printInOrderRecursive(node->left, printFunction);
    printFunction(node->data);
    printInOrderRecursive(node->right, printFunction);
}

void printInOrder(Tree *tree) {
    if (!tree || !tree->printFunction) return;
    printInOrderRecursive(tree->root, tree->printFunction);
}

///////////////////
// Iterator
///////////////////
struct TreeIterator {
    TreeNode **stack;
    int top;
    int capacity;
};

static void pushLeft(TreeIterator *iter, TreeNode *node) {
    while (node != NULL) {
        if (iter->top >= iter->capacity) {
            int new_capacity = iter->capacity * 2;
            TreeNode **new_stack = realloc(iter->stack, new_capacity * sizeof(TreeNode *));
            if (!new_stack) return;  // fail silently; nextData will just return NULL
            iter->stack = new_stack;
            iter->capacity = new_capacity;
        }
        iter->stack[iter->top++] = node;
        node = node->left;
    }
}

TreeIterator *createIterator(Tree *tree) {
    if (!tree || !tree->root) return NULL;

    TreeIterator *iter = malloc(sizeof(TreeIterator));
    if (!iter) return NULL;

    iter->capacity = 16;
    iter->top = 0;
    iter->stack = malloc(iter->capacity * sizeof(TreeNode *));
    if (!iter->stack) {
        free(iter);
        return NULL;
    }

    pushLeft(iter, tree->root);
    return iter;
}

void *nextData(TreeIterator *iter) {
    if (!iter || iter->top == 0) return NULL;

    TreeNode *node = iter->stack[--iter->top];
    void *data = node->data;

    if (node->right)
        pushLeft(iter, node->right);

    return data;
}

void destroyIterator(TreeIterator *iter) {
    if (!iter) return;
    free(iter->stack);
    free(iter);
}