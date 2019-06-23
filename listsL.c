#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "listsL.h"

struct lNode {
    lItem value;
    struct lNode *back;
    struct lNode *next;
};
typedef struct lNode lNode;

// I've used a circular linked lList to save some memory
// The control lNode serves as the start and end
struct lList{
    lNode *control;
    lNode *current;
};
typedef struct lList lList;

// Create a new empty lList, with a default lItem to return in case of error.
lList *newLList(lItem d){
    // creating start and end lNode
    lNode *controlNode = malloc(sizeof(lNode));
    controlNode->value = d;
    controlNode->back = controlNode;
    controlNode->next = controlNode;
    // creating new lList
    lList *newL = malloc(sizeof(lList));
    newL->control = controlNode;
    newL->current = controlNode;

    return newL;
}

// frees the linked lists but leaves the values pointers
void freeLListHead(lList *l){
    lNode *c = l->control->next;
    while(c != l->control){
        lNode *next = c->next;
        free(c);
        c = next;
    }
    free(l->control);
    free(l);
}

void freeLNode(lNode *l){
    free(l->value);
    free(l);
}

// Free up the lList and all the data in it.
void freeLList(lList *l){
    lNode *c = l->control->next; // start lNode
    while(c != l->control){
        lNode *next = c->next;
        freeLNode(c);
        c = next;
    }
    freeLNode(l->control);
    free(l);
}

// Set the current position before the first lItem or after the last lItem,
// to begin a forward or backward traversal.
void startLF(lList *l){
    l->current = l->control->next;
}
void startLB(lList *l){
    l->current = l->control;
}

// Check whether the current position is at the end or start, to test
// whether a traversal has finished.
bool endLF(lList *l){
    return (l->current == l->control);
}
bool endLB(lList *l){
    return (l->current->back == l->control);
}

// Move the current position one place forwards or backwards, and return true.
// If nextF is called when at the end of the lList, or nextB when at the start,
// the functions do nothing and return false.
bool nextLF(lList *l){
    bool state = !endLF(l);
    if(state){
        l->current = l->current->next;
    }
    return state;
}
bool nextLB(lList *l){
    bool state = !endLB(l);
    if(state){
        l->current = l->current->back;
    }
    return state;
}

// Insert an lItem before the current position during a traversal.  The traversal
// of the remaining lItems is not affected.
void insertLF(lList *l, lItem x){
    lNode *pNode = l->current->back;
    lNode *newNode = malloc(sizeof(lNode));

    pNode->next = newNode;
    newNode->value = x;
    newNode->next = l->current;
    newNode->back = pNode;
    l->current->back = newNode;
}
void insertLB(lList *l, lItem x){
    insertLF(l, x);
    nextLB(l);
}

// Get the current lItem. If getF is called when at the end, or getB is called
// when at the start, the default lItem is returned.
lItem getLF(lList *l){
    return (l->current->value);
}
lItem getLB(lList *l){
    return (l->current->back->value);
}

// Set the current lItem and return true. If setF is called when at the end, or
// setB when at the start, nothing is done and false is returned.
bool setLF(lList *l, lItem x){
    bool state = !endLF(l);
    if(state){
        l->current->value = x;
    }
    return state;
}
bool setLB(lList *l, lItem x){
    bool state = !endLB(l);
    if(state){
        l->current->back->value = x;
    }
    return state;
}

// Delete the current lItem and return true. When iterating forward, either nextF
// or deleteF should be called to delete or step past each lItem. If deleteF/B is
// called at the start/end of the lList, nothing is done and false is returned.
bool deleteLF(lList *l){
    bool state = !endLF(l);
    if(state){
        lNode *c = l->current;
        lNode *p = c->back;
        lNode *n = c->next;
        // setting pointers
        p->next = c->next;
        n->back = c->back;
        l->current = n;
        // freeing the current lNode
        freeLNode(c);
    }
    return state;
}
bool deleteLB(lList *l){
    bool state = nextLB(l);
    if(state){
        deleteLF(l);
    }
    return state;
}
