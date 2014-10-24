# include <stdio.h>
# include <string.h>
# include <stdlib.h>


/*****************************************************************************/
/* This structure stores one node in the linked list.                        */
/*****************************************************************************/
typedef struct Node {
  char          character;
  struct Node   *next; 		// stores reference to the next node clockwise
  struct Node   *previous;  // stores reference to the next node anti-clockwise
} Node;


/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

// Pars ints
int* parseIntegers(int, char const *[]);
void validateStrIsInt(const char *);

// Parse Wheel
char* parseWheelFile(const char*);
FILE* openFile(const char*);
int countLines(const char*);
char* decodeMessage(Node*, int*, int);

// Constuct Wheel
Node* constructWheel(char*);
Node* newNode(char);