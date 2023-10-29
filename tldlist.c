#include "tldlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//TLDNode struct def
struct tldnode {
    char *tldname; //domain name
    long count; //visit count
    struct tldnode *left; //binary tree node left
    struct tldnode *right; //binary tree node right
};

//TLDList struct def
struct tldlist {
    Date *begin; 
    Date *end;
    TLDNode *root;
    long totalEntries;
};

struct tlditerator {
    int index;
    int size;
    TLDNode **nodes;
};


//function to create a new TLDNode
TLDNode *tldnode_create(char *tldname) {
    TLDNode *node = malloc(sizeof(TLDNode));
    if (node == NULL) {
        return NULL; //failed to allocate
    }
    node->tldname = strdup(tldname);
    if (node->tldname == NULL) {
        free(node);
        return NULL; //failed to allocate
    }
    node->count = 1;
    node->left = NULL; //new nodes dont have left/roght
    node->right = NULL;
    return node;
}

//recursively add a TLDNode to the tree
int tldlist_add_helper(TLDNode **root, char *tldname) {
    if (*root == NULL) {
        *root = tldnode_create(tldname);
        if (*root == NULL) {
            return 0;
        }
        return 1;//successful, counting entry
    }
    int cmp = strcmp(tldname, (*root)->tldname);
    if (cmp < 0) {
        return tldlist_add_helper(&((*root)->left), tldname);
    } else if (cmp > 0) {
        return tldlist_add_helper(&((*root)->right), tldname);
    } else {
        (*root)->count++;
        return 1; //successful, counting entry
    }
}

TLDList *tldlist_create(Date *begin, Date *end) {
    TLDList *tld = malloc(sizeof(TLDList));
    if (tld == NULL) {
        return NULL;
    }
    tld->begin = date_duplicate(begin);
    tld->end = date_duplicate(end);
    tld->root = NULL;
    tld->totalEntries = 0;
    return tld;
}

void tldlist_destroy_helper(TLDNode *node) {
    if (node == NULL) { //if the node is null, stop
        return;
    }
    tldlist_destroy_helper(node->left); //recursively deallocates all nodes to the left
    tldlist_destroy_helper(node->right); //recursively deallocates all nodes to the right
    free(node->tldname); //deallocate memory for name member
    free(node); //deallocate mmemory for entire node
}

void tldlist_destroy(TLDList *tld) {
    tldlist_destroy_helper(tld->root);
    date_destroy(tld->begin);
    date_destroy(tld->end);
    free(tld);
}

int tldlist_add(TLDList *tld, char *hostname, Date *d) {
    if (date_compare(d, tld->begin) < 0 || date_compare(d, tld->end) > 0) {
        return 0; //outside date range
    }
    int result = tldlist_add_helper(&(tld->root), strrchr(hostname, '.') + 1);
    if (result) {
        tld->totalEntries++;
    }
    return result;
}

long tldlist_count(TLDList *tld) {
    return tld->totalEntries;
}

TLDIterator *tldlist_iter_create_helper(TLDNode *node, TLDIterator *iter) {
    if (node == NULL) {
        return NULL;
    }
    if (iter == NULL) {
        iter = malloc(sizeof(TLDIterator));
        if (iter == NULL) {
            return NULL; 
        }
        iter->index = 0;
        iter->size = 0;
        iter->nodes = NULL;
    }
    if (iter->index >= iter->size) {
        iter->size = 2 * iter->size + 1;
        iter->nodes = realloc(iter->nodes, iter->size * sizeof(TLDNode *));
        if (iter->nodes == NULL) {
            free(iter);
            return NULL; //
        }
    }
    iter->nodes[iter->index++] = node;
    tldlist_iter_create_helper(node->left, iter);
    tldlist_iter_create_helper(node->right, iter);
    return iter;
}

TLDIterator *tldlist_iter_create(TLDList *tld) {
    return tldlist_iter_create_helper(tld->root, NULL);
}

TLDNode *tldlist_iter_next(TLDIterator *iter) {
    if (iter->index <= 0) {
        return NULL; //no elements to return
    }
    return iter->nodes[--iter->index];
}

void tldlist_iter_destroy(TLDIterator *iter) {
    free(iter->nodes);
    free(iter);
}

char *tldnode_tldname(TLDNode *node) {
    return node->tldname;
}

long tldnode_count(TLDNode *node) {
    return node->count;
}
