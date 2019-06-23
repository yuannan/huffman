#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "lists.h"

struct node {
    item value;
    struct node *back;
    struct node *next;
};
typedef struct node node;

// I've used a circular linked list to save some memory
// The control node serves as the start and end
struct list{
    node *control;
    node *current;
};
typedef struct list list;

// Create a new empty list, with a default item to return in case of error.
list *newList(item d){
    // creating start and end node
    node *controlNode = malloc(sizeof(node));
    controlNode->value = d;
    controlNode->back = controlNode;
    controlNode->next = controlNode;
    // creating new list
    list *newL = malloc(sizeof(list));
    newL->control = controlNode;
    newL->current = controlNode;

    return newL;
}

// Free up the list and all the data in it.
void freeList(list *l){
    node *c = l->control->next; // start node
    while(c != l->control){
        node *next = c->next;
        free(c);
        c = next;
    }
    free(l->control);
    free(l);
}

// Set the current position before the first item or after the last item,
// to begin a forward or backward traversal.
void startF(list *l){
    l->current = l->control->next;
}
void startB(list *l){
    l->current = l->control;
}

// Check whether the current position is at the end or start, to test
// whether a traversal has finished.
bool endF(list *l){
    return (l->current == l->control);
}
bool endB(list *l){
    return (l->current->back == l->control);
}

// Move the current position one place forwards or backwards, and return true.
// If nextF is called when at the end of the list, or nextB when at the start,
// the functions do nothing and return false.
bool nextF(list *l){
    bool state = !endF(l);
    if(state){
        l->current = l->current->next;
    }
    return state;
}
bool nextB(list *l){
    bool state = !endB(l);
    if(state){
        l->current = l->current->back;
    }
    return state;
}

// Insert an item before the current position during a traversal.  The traversal
// of the remaining items is not affected.
void insertF(list *l, item x){
    node *pNode = l->current->back;
    node *newNode = malloc(sizeof(node));

    pNode->next = newNode;
    newNode->value = x;
    newNode->next = l->current;
    newNode->back = pNode;
    l->current->back = newNode;
}
void insertB(list *l, item x){
    insertF(l, x);
    nextB(l);
}

// Get the current item. If getF is called when at the end, or getB is called
// when at the start, the default item is returned.
item getF(list *l){
    return (l->current->value);
}
item getB(list *l){
    return (l->current->back->value);
}

// Set the current item and return true. If setF is called when at the end, or
// setB when at the start, nothing is done and false is returned.
bool setF(list *l, item x){
    bool state = !endF(l);
    if(state){
        l->current->value = x;
    }
    return state;
}
bool setB(list *l, item x){
    bool state = !endB(l);
    if(state){
        l->current->back->value = x;
    }
    return state;
}

// Delete the current item and return true. When iterating forward, either nextF
// or deleteF should be called to delete or step past each item. If deleteF/B is
// called at the start/end of the list, nothing is done and false is returned.
bool deleteF(list *l){
    bool state = !endF(l);
    if(state){
        node *c = l->current;
        node *p = c->back;
        node *n = c->next;
        // setting pointers
        p->next = c->next;
        n->back = c->back;
        l->current = n;
        // freeing the current node
        free(c);
    }
    return state;
}
bool deleteB(list *l){
    bool state = nextB(l);
    if(state){
        deleteF(l);
    }
    return state;
}
