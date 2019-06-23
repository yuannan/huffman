#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "huffman.h"
#include "listsH.h"

struct hNode {
    hItem value;
    struct hNode *back;
    struct hNode *next;
};
typedef struct hNode hNode;

// I've used a circular linked hList to save some memory
// The control hNode serves as the start and end
struct hList{
    hNode *control;
    hNode *current;
};
typedef struct hList hList;

// Create a new empty hList, with a default hItem to return in case of error.
hList *newHList(hItem d){
    // creating start and end hNode
    hNode *controlNode = malloc(sizeof(hNode));
    controlNode->value = d;
    controlNode->back = controlNode;
    controlNode->next = controlNode;
    // creating new hList
    hList *newL = malloc(sizeof(hList));
    newL->control = controlNode;
    newL->current = controlNode;

    return newL;
}

void freeHNode(hNode *h){
    free(h->value->l);
    free(h->value);
    free(h);
}

// Free up the hList and all the data in it.
void freeHList(hList *l){
    hNode *c = l->control->next; // start hNode
    while(c != l->control){
        hNode *next = c->next;
        freeHNode(c);
        c = next;
    }
    freeHNode(l->control);
    free(l);
}

// Set the current position before the first hItem or after the last hItem,
// to begin a forward or backward traversal.
void startHF(hList *l){
    l->current = l->control->next;
}
void startHB(hList *l){
    l->current = l->control;
}

// Check whether the current position is at the end or start, to test
// whether a traversal has finished.
bool endHF(hList *l){
    return (l->current == l->control);
}
bool endHB(hList *l){
    return (l->current->back == l->control);
}

// Move the current position one place forwards or backwards, and return true.
// If nextF is called when at the end of the hList, or nextB when at the start,
// the functions do nothing and return false.
bool nextHF(hList *l){
    bool state = !endHF(l);
    if(state){
        l->current = l->current->next;
    }
    return state;
}
bool nextHB(hList *l){
    bool state = !endHB(l);
    if(state){
        l->current = l->current->back;
    }
    return state;
}

// Insert an hItem before the current position during a traversal.  The traversal
// of the remaining hItems is not affected.
void insertHF(hList *l, hItem x){
    hNode *pNode = l->current->back;
    hNode *newNode = malloc(sizeof(hNode));

    pNode->next = newNode;
    newNode->value = x;
    newNode->next = l->current;
    newNode->back = pNode;
    l->current->back = newNode;
}
void insertHB(hList *l, hItem x){
    insertHF(l, x);
    nextHB(l);
}

// Get the current hItem. If getF is called when at the end, or getB is called
// when at the start, the default hItem is returned.
hItem getHF(hList *l){
    return (l->current->value);
}
hItem getHB(hList *l){
    return (l->current->back->value);
}

// Set the current hItem and return true. If setF is called when at the end, or
// setB when at the start, nothing is done and false is returned.
bool setHF(hList *l, hItem x){
    bool state = !endHF(l);
    if(state){
        l->current->value = x;
    }
    return state;
}
bool setHB(hList *l, hItem x){
    bool state = !endHB(l);
    if(state){
        l->current->back->value = x;
    }
    return state;
}

// Delete the current hItem and return true. When iterating forward, either nextF
// or deleteF should be called to delete or step past each hItem. If deleteF/B is
// called at the start/end of the hList, nothing is done and false is returned.
bool deleteHF(hList *l){
    bool state = !endHF(l);
    if(state){
        hNode *c = l->current;
        hNode *p = c->back;
        hNode *n = c->next;
        // setting pointers
        p->next = c->next;
        n->back = c->back;
        l->current = n;
        // freeing the current hNode
        freeHNode(c);
    }
    return state;
}
bool deleteHB(hList *l){
    bool state = nextHB(l);
    if(state){
        deleteHF(l);
    }
    return state;
}
