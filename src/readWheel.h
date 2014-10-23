# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct Node {
  char          character;
  struct Node   *next; 		// stores reference to the next node clockwise
  struct Node   *previous;  // stores reference to the next node anti-clockwise
} Node;


// Constuct Wheel
Node* constuctWheel(char*);
Node* newNode(char);

// Pars ints
int* parseIntegers(int, char const *[]);
char* decodeMessage(Node*, int*, int);

// Parse Wheel
char* parseWheelFile(char[]);
FILE* readFile(char[]);
int countLines(char[]);