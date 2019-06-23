#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "huffman.h"
#include "listsL.c"
#include "listsH.c"

huffNode *newHuffNode(letter *let, huffNode *l, huffNode *r){
    huffNode *newH = malloc(sizeof(huffNode));
    newH->l = let;
    newH->left = l;
    newH->right = r;

    return newH;
}

letter *newLetter(int number, char character){
    letter *newL = malloc(sizeof(letter));
    newL->n = number;
    newL->c = character;

    return newL;
}

void freeLetter(letter *l){
    free(l);
}

void freeHuffNode(huffNode *h){
    freeLetter(h->l);
    free(h);
}

void freeReqHuffnode(huffNode *n){
    if(n->left != NULL){
        freeReqHuffnode(n->left);
    }
    if(n->right != NULL){
        freeReqHuffnode(n->right);
    }
    freeHuffNode(n);
}

void freeHuffmanTree(huffman *ht){
    huffNode *s = ht->start;
    freeReqHuffnode(s);
    free(ht);
}

// updates increments the char inside the array
// return true if it's updated, false if it's not found
bool updateListChar(lList *l, char c){
    startLF(l); //sets the list to the start
    bool found = false;
    while(!found && !endLF(l)){
        letter *let = getLF(l);
        if(let->c == c){
            found = true;
            let->n++;
        } else{
            nextLF(l);
        }
    }
    startLF(l);
    return found;
}

void updateAndInsertLetter(lList *l, char c){
    if(!updateListChar(l, c)){
        //printf("%c not found, inserting\n", c);
        insertLB(l, newLetter(1, c));
    } else{
        //printf("%c found, now at %d\n", c, getLF(l)->n);
    }
}

void readAndInsertLetters(lList *l, char *filename){
    FILE *in = fopen(filename, "r");
    char ch = fgetc(in);
    while(! feof(in)){
        //printf("read %c\n", ch);
        updateAndInsertLetter(l, ch);
        ch = fgetc(in);
    }
    fclose(in);
}

void printOutLetterList(lList *l){
    startLF(l);
    bool endOfList = false;
    while(!endOfList){
        printf("%c %d\n", getLF(l)->c, getLF(l)->n);
        endOfList = !nextLF(l);
    }
}

void moveUpToFreq(hList *l, int n){
    startHF(l); // moves the current to the start
    while(n <= getHF(l)->l->n){
        nextHF(l);
    }
}

// creates a list of huffnodes from the letters
// smallest freq at the end
hList *convertInsertionSort(lList *freq){
    hList *hOut = newHList(newHuffNode(newLetter(-1, '\0'), NULL, NULL));
    // loop the letters
    bool endOfLetters = false;
    while(!endOfLetters){
        letter *cl = getLF(freq);
        //printf("%d %c\n", cl->n, cl->c);
        moveUpToFreq(hOut, cl->n);
        huffNode *newHNode = newHuffNode(cl, NULL, NULL);
        insertHF(hOut, newHNode);

        nextLF(freq);
        endOfLetters = endLF(freq);
    }

    return hOut;
}

void testHListSorted(hList *l);

void getSmallestTwoItem(hList *hIn, huffNode *minNodes[2]){
    startHB(hIn);
    minNodes[0] = getHB(hIn);
    if(endHB(hIn)) minNodes[0] = NULL;
    nextHB(hIn);
    minNodes[1] = getHB(hIn);
    if(endHB(hIn)) minNodes[1] = NULL;
}

void constructHuffmanTree(lList *freq, huffman *tree){
    hList *hSorted = convertInsertionSort(freq);
    testHListSorted(hSorted);
    
    bool treeComplete = false;
    while(!treeComplete){
        huffNode *minNodes[2];
        getSmallestTwoItem(hSorted, minNodes);



        freeHuffNode(minNodes[0]);
        freeHuffNode(minNodes[1]);
        free(minNodes);
    }
    

    freeHList(hSorted);
}

huffman *newHuffmanTree(char *filename){
    huffman *newHuffTree = malloc(sizeof(huffman)); 
    newHuffTree->start = newHuffNode(newLetter(-1, '\0'), NULL, NULL);
    lList *frequencyList = newLList(newLetter(-1, '\0'));
    readAndInsertLetters(frequencyList, filename);

    constructHuffmanTree(frequencyList, newHuffTree);
    freeLListHead(frequencyList);

    return newHuffTree;
}

#ifdef test_huffman
void testHListSorted(hList *l){
    startHF(l);
    bool endOfList = false;
    huffNode *a = getHF(l);
    huffNode *b;
    int r = 0;
    while(!endOfList){
        r++;
        nextHF(l);
        endOfList = endHF(l);
        if(!endOfList){
            b = a;
            a = getHF(l);
            //printf("r:%d   %c %d    %c %d\n", r, b->l->c, b->l->n, a->l->c, a->l->n);
            assert(b->l->n >= a->l->n);
        }
    }
}



void testConstructHuffmanTree(){
    huffman *testHuff = newHuffmanTree("test.txt");
    freeHuffmanTree(testHuff);
}

void testReadAndUpdate(){
    lList *freq = newLList(newLetter(-1, '\0'));
    char *testfile = "test.txt";
    readAndInsertLetters(freq, testfile);
    //printOutLetterList(freq);
    freeLList(freq);
}

void testUpdateListChar(){
    lList *testUL = newLList(newLetter(-1, '\0'));

    insertLB(testUL, newLetter(1, 'a'));
    assert(getLF(testUL)->c == 'a');
    assert(getLF(testUL)->n == 1);
    updateListChar(testUL, 'a');
    assert(getLF(testUL)->c == 'a');
    assert(getLF(testUL)->n == 2);

    assert(!updateListChar(testUL, 'b'));
    insertLB(testUL, newLetter(1, 'b'));
    assert(getLF(testUL)->c == 'b');
    assert(getLF(testUL)->n == 1);
    nextLF(testUL);
    assert(getLF(testUL)->c == 'a');
    assert(getLF(testUL)->n == 2);

    freeLList(testUL);
}

void testConstructFrequencyList(){
    testUpdateListChar();
    testReadAndUpdate();
}

void testDefaultHuffNodeList(){
    huffNode *startH = newHuffNode(newLetter(-1, '\0'), NULL, NULL);
    hList *hList = newHList(startH);

    assert(getHF(hList)->l->n == -1);
    assert(getHF(hList)->l->c == '\0');
    freeHList(hList);
}

void fillAlphabetList(hList *hList){
    for(int a = 0; a < 26; a++){
        char c = 'a' + a;
        //printf("%d:: %c\n", a, c);

        letter *newL = newLetter(a, c);
        huffNode *newHuff = newHuffNode(newL, NULL, NULL);
        insertHF(hList, newHuff);
    }
}

void printAlphabetList(hList *hList){
    startHF(hList);
    int c = 0;
    bool state = true;
    while(state){
        huffNode *cNode = getHF(hList);
        printf("%d: %c\n", cNode->l->n, cNode->l->c);
        c++;
        state = nextHF(hList);
        if(c == 26) state = false;
    }
}

void assertAlphabetList(hList *hList){
    startHF(hList);
    int c = 0;
    bool state = true;
    while(state){
        huffNode *cNode = getHF(hList);
        assert(cNode->l->n == c);
        assert(cNode->l->c == ('a' + c));
        state = nextHF(hList);
        c++;
        if(c == 26) state = false;
    }
}

void testAlphabetHuffList(){
    huffNode *startH = newHuffNode(newLetter(-1, '\0'), NULL, NULL);
    hList *hList = newHList(startH);

    fillAlphabetList(hList);
    //printAlphabetList(hList);
    assertAlphabetList(hList);
    freeHList(hList);
}


void testHuffNodeList(){
    testDefaultHuffNodeList();
    testAlphabetHuffList();
}

void testLetterLists(){
    letter *startL = newLetter(-1, '\0');
    lList *lList = newLList(startL);

    for(int i = 0; i < 26; i++){
        char a = 'a' + i;
        letter *l = newLetter(i, a);
        insertLB(lList, l);
    }
    freeLList(lList);
}

void testHuffNode(huffNode *testH, letter *let, huffNode *l, huffNode *r){
    assert(testH != NULL);
    assert(testH->l == let);
    assert(testH->left == l);
    assert(testH->right == r);
}

void testHuffNodes(){
    letter *testL = newLetter(-1, '\0');
    huffNode *testH = newHuffNode(testL, NULL, NULL);
    testHuffNode(testH, testL, NULL, NULL);
    
    letter *testLL = newLetter(-1, '\0');
    letter *testLR = newLetter(-1, '\0');
    huffNode *testHL = newHuffNode(testLL, NULL, NULL);
    huffNode *testHR = newHuffNode(testLR, NULL, NULL);
    testH->left = testHL;
    testH->right = testHR;
    testHuffNode(testH, testL, testHL, testHR);
    
    freeHuffNode(testHL);
    freeHuffNode(testHR);
    freeHuffNode(testH);
}

void testLetter(letter *testL, int number, char character){
    assert(testL != NULL);
    assert(testL->n == number);
    assert(testL->c == character);
}

void testLetters(){
    letter *testL = newLetter(0, 'a');
    testLetter(testL, 0, 'a');
    testL->n = 1;
    testLetter(testL, 1, 'a');
    testL->c = 'b';
    testLetter(testL, 1, 'b');

    freeLetter(testL);
}

int main(){
    printf("Starting huffman tests\n");

    testLetters();
    testLetterLists();

    testHuffNodes();
    testHuffNodeList();    

    testConstructFrequencyList();
    testConstructHuffmanTree();
    printf("All test passed\n");
    return 0;
}
#endif

void encodeHuffman(char *in, char *out){

}

void decodeHuffman(char *in, char *out){

}

void printHelpText(){
    printf("./huffman [options] [in path] [out path]\n");
    printf("    [options]:\n");
    printf("            e = encode\n");
    printf("            d = decode\n");
    printf("            h = help\n");
}
#ifndef test_huffman
int main(int n, char *args[n]){
    char *mode = args[1];
    char *pathIn = args[2];
    char *pathOut = args[3];

    switch(mode[0]){
        case 'e':
            encodeHuffman(pathIn, pathOut);
            break;
        case 'd':
            decodeHuffman(pathIn, pathOut);
            break;
        default:
            printHelpText();
            break;
    }
    return 0;
}

#endif
