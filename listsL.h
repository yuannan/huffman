#include <stdbool.h>
#include "huffman.h"

// The type of items stored in the lList. Change this for different applications.
typedef struct letter* lItem;

// The lList type is opaque (declared here, and defined in lLists.c).
struct lList;
typedef struct lList lList;

// Create a new empty lList, with a default lItem to return in case of error.
lList *newLList(lItem d);

// Free up the lList and all the data in it.
void freeLList(lList *l);

// Set the current position before the first lItem or after the last lItem,
// to begin a forward or backward traversal.
void startLF(lList *l);
void startLB(lList *l);

// Check whether the current position is at the end or start, to test
// whether a traversal has finished.
bool endLF(lList *l);
bool endLB(lList *l);

// Move the current position one place forwards or backwards, and return true.
// If nextF is called when at the end of the lList, or nextB when at the start,
// the functions do nothing and return false.
bool nextLF(lList *l);
bool nextLB(lList *l);

// Insert an lItem before the current position during a traversal.  The traversal
// of the remaining lItems is not affected.
void insertLF(lList *l, lItem x);
void insertLB(lList *l, lItem x);

// Get the current lItem. If getF is called when at the end, or getB is called
// when at the start, the default lItem is returned.
lItem getLF(lList *l);
lItem getLB(lList *l);

// Set the current lItem and return true. If setF is called when at the end, or
// setB when at the start, nothing is done and false is returned.
bool setLF(lList *l, lItem x);
bool setLB(lList *l, lItem x);

// Delete the current lItem and return true. When iterating forward, either nextF
// or deleteF should be called to delete or step past each lItem. If deleteF/B is
// called at the start/end of the lList, nothing is done and false is returned.
bool deleteLF(lList *l);
bool deleteLB(lList *l);
