#ifndef HUFFMAN_H
#define HUFFMAN_H
struct letter{
    int n;
    char c;
};
typedef struct letter letter;

struct huffNode{
    struct letter *l;
    struct huffNode *left;
    struct huffNode *right;
};
typedef struct huffNode huffNode;

struct huffman{
    huffNode *start;
};
typedef struct huffman huffman;
#endif
