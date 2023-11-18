#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "uhtml.h"

typedef struct Node {
    char* tag;
    char* text;
    char* style;
    int x;  // New attributes for positioning
    int y;
    struct Node* children;
    struct Node* next;
} Node;

Node* createNode(char* tag, char* text, char* style, int x, int y) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->tag = strdup(tag);
    newNode->text = strdup(text);
    newNode->style = strdup(style);
    newNode->x = x;
    newNode->y = y;
    newNode->children = NULL;
    newNode->next = NULL;
    return newNode;
}

void addChild(Node* parent, Node* child) {
    if (parent->children == NULL) {
        parent->children = child;
    } else {
        Node* temp = parent->children;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = child;
    }
}
Node* parseHTMLRecursive(char* html) {
    // Simplified parsing logic for demonstration purposes
    Node* root = NULL;
    Node* currentParent = NULL;

    char* token = strtok(html, "<>");

    while (token != NULL) {
        if (token[0] == '/') {
            // Closing tag
            // Pop from the stack (not implemented for simplicity)
            currentParent = currentParent->next;
        } else if (token[0] != '!') {
            // Opening tag
            char* tag = strtok(token, " \t\n\r");
            char* style = strtok(NULL, " \t\n\r");

            int x = 0, y = 0;
            if (style != NULL) {
                parseStyle(style, &x, &y);
            }

            Node* newNode = createNode(tag, "", style, x, y);

            if (root == NULL) {
                root = newNode;
                currentParent = root;
            } else {
                addChild(currentParent, newNode);
                currentParent = newNode;
            }
        } else {
            // Comment or other non-element content (not handled in this example)
        }

        token = strtok(NULL, "<>");
    }

    return root;
}

Node* parseHTML(char* html) {
    // Call the recursive parser
    return parseHTMLRecursive(html);
}
void parseStyle(char* style, int* x, int* y) {
    // Simplified CSS parsing for demonstration
    // Extract x and y values from the style attribute
    char* xPosition = strstr(style, "x:");
    char* yPosition = strstr(style, "y:");

    if (xPosition) {
        *x = atoi(xPosition + 2); // Skip "x:" and convert the rest to an integer
    }

    if (yPosition) {
        *y = atoi(yPosition + 2); // Skip "y:" and convert the rest to an integer
    }
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, Node* node) {
    SDL_Color color = {255, 255, 255};  // White color

    SDL_Surface* surface = TTF_RenderText_Solid(font, node->text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    SDL_Rect dstRect = {node->x, node->y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void renderDOM(SDL_Renderer* renderer, TTF_Font* font, Node* node) {
    if (node == NULL) return;

    // Render current node
    if (node->text != NULL) {
        renderText(renderer, font, node);
    }

    // Render children
    renderDOM(renderer, font, node->children);

    // Render next sibling
    renderDOM(renderer, font, node->next);
}

void freeDOM(Node* node) {
    if (node == NULL) return;

    freeDOM(node->children);
    freeDOM(node->next);

    free(node->tag);
    free(node->text);
    free(node->style);
    free(node);
}

