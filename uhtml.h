#ifndef UHTML_H
#define UHTML_H

// Define a structure for a simple DOM node
typedef struct Node {
    char* tag;
    char* text;
    char* style;
    int x;
    int y;
    struct Node* children;
    struct Node* next;
} Node;

// Function declarations
Node* parseHTML(char* html);
Node* createNode(char* tag, char* text, char* style, int x, int y);
void addChild(Node* parent, Node* child);
void parseStyle(char* style, int* x, int* y);
void applyStyles(Node* node);
void renderDOM(Node* node);
void freeDOM(Node* node);

#endif /* UHTML_H */
