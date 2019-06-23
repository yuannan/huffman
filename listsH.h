#include <stdbool.h>
#include "huffman.h"

// The type of items stored in the hList. Change this for different applications.
typedef struct huffNode* hItem;

// The hList type is opaque (declared here, and defined in hLists.c).
struct hList;
typedef struct hList hList;

// Create a new empty hList, with a default hItem to return in case of error.
hList *newHList(hItem d);

//void freeHNode(hNode *h);
// Free up the hList and all the data in it.
void freeHList(hList *l);

// Set the current position before the first hItem or after the last hItem,
// to begin a forward or backward traversal.
void startHF(hList *l);
void startHB(hList *l);

// Check whether the current position is at the end or start, to test
// whether a traversal has finished.
bool endHF(hList *l);
bool endHB(hList *l);

// Move the current position one place forwards or backwards, and return true.
// If nextF is called when at the end of the hList, or nextB when at the start,
// the functions do nothing and return false.
bool nextHF(hList *l);
bool nextHB(hList *l);

// Insert an hItem before the current position during a traversal.  The traversal
// of the remaining hItems is not affected.
void insertHF(hList *l, hItem x);
void insertHB(hList *l, hItem x);

// Get the current hItem. If getF is called when at the end, or getB is called
// when at the start, the default hItem is returned.
hItem getHF(hList *l);
hItem getHB(hList *l);

// Set the current hItem and return true. If setF is called when at the end, or
// setB when at the start, nothing is done and false is returned.
bool setHF(hList *l, hItem x);
bool setHB(hList *l, hItem x);

// Delete the current hItem and return true. When iterating forward, either nextF
// or deleteF should be called to delete or step past each hItem. If deleteF/B is
// called at the start/end of the hList, nothing is done and false is returned.
bool deleteHF(hList *l);
bool deleteHB(hList *l);
