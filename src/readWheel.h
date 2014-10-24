# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct Node {
  char          character;
  struct Node   *next; 		// stores reference to the next node clockwise
  struct Node   *previous;  // stores reference to the next node anti-clockwise
} Node;


// Constuct Wheel
Node* constructWheel(char*);
Node* newNode(char);

// Pars ints
int* parseIntegers(int, char const *[]);
char* decodeMessage(Node*, int*, int);

// Parse Wheel
char* parseWheelFile(const char*);
FILE* readFile(const char*);
int countLines(const char*);
void validateStrIsInt(const char *);
