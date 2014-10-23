# include <stdio.h>
# include <string.h>
# include <stdlib.h>


typedef struct Node {
  char          character;
  struct Node   *nextChild; // stores reference to the next child clockwise
  struct Node   *previousChild; // stores reference to the next child anti-clockwise
} Node;



// Constuct Wheel
Node* constuctWheel(char*);
Node* newNode(char);
// DELETE:
// void printWheel(Node *);

// Pars ints
int* parseIntegers(int, char const *[]);
char* decodeMessage(Node*, int*, int);

// Parse Wheel
char* parseWheelFile(char[]);
FILE* readFile(char[]);
int countLines(char[]);