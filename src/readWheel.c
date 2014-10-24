#include "readWheel.h"

/*****************************************************************************/
/* Decode a wheel                                                            */
/*****************************************************************************/
char* decodeMessage(Node *root, int *codedMessage, int lengthOfMessage) {
  char *decodedMessage = malloc(lengthOfMessage * sizeof *decodedMessage);
  Node *currentNode = root;

  for (int i = 0; i < lengthOfMessage; ++i) {
    if (codedMessage[i] < 0) {
      for (int j = 0; j > codedMessage[i]; --j) {
        currentNode = currentNode->previous;
      }
    } else {
      for (int k = 0; k < codedMessage[i]; ++k) {
        currentNode = currentNode->next;
      }
    }
    decodedMessage[i] = currentNode->character;
  }

  return decodedMessage;
}


/*****************************************************************************/
/* Construct a wheel                                                         */
/*****************************************************************************/
Node* constructWheel(char *flatWheel) {
  unsigned long wheelLength = strlen(flatWheel);

  /* construct root node separately */
  Node *root = newNode(flatWheel[0]);
  Node *previousNode = NULL;
  Node *currentNode = root;

  for (int i = 1; i < wheelLength; ++i) {
    currentNode->next     = newNode(flatWheel[i]);
    currentNode->previous = previousNode;

    previousNode = currentNode;
    currentNode = currentNode->next;
  }

  /* construct last node separately */
  currentNode->next = root;
  currentNode->previous = previousNode;
  /* link the root node with the last node */
  root->previous = currentNode;
  return root;
}

/* return pointer to the newly created node */
Node* newNode(char character) {
  Node *node = malloc(sizeof *node);
  node->character = character;
  node->next = NULL;
  node->previous = NULL;

  return node;
}


/*****************************************************************************/
/* Parce Coded Message                                                       */
/*****************************************************************************/
int* parseIntegers(int argc, char const *argv[]) {
  int *codedMessage = malloc((argc-2) * sizeof *codedMessage);
  int i;
  int j = 0;
  /* parse input integers into codedMessage int array while
   * skiping first 2 arguements which aren't integers */
  for (i = 2; i < argc; ++i, ++j) {
    validateStrIsInt(argv[i]);
    codedMessage[j] = atoi(argv[i]);
  }
  return codedMessage;
}

/*****************************************************************************/
/* Parce Wheel                                                               */
/*****************************************************************************/
/* mention how it would read the first character of each line,
 * so doesn't matter if each line contains more characters, which indeed is not specified in the spec (i.e. Coursework) */

char* parseWheelFile(const char *fileName) {
  FILE *fp = readFile(fileName);
  int linesInFile = countLines(fileName);
  char ch;
  char *flatWheel = malloc(linesInFile * sizeof *flatWheel); // allocate flatWheel.
  int length = 0;


  for (int i = 0; i < linesInFile+1; ++i) {
    while ( ((ch = fgetc(fp)) != EOF) && (ch != '\n') ) {
      flatWheel[i] = ch;
      length++;
      /* make sure there's only one character on this line */
      if (length == 2) {
        fprintf(stderr, "Error: Wheel file must contain only one character per line.\n");
        printUsageMessage();
        exit(1);
      }
    }
    length = 0; // reset length
  }

  fclose (fp);
  return flatWheel;
}


int countLines(const char *fileName) {
  FILE *fp = readFile(fileName);

  int  c;
  unsigned long newLineCount = 0;

  /* count newline characters */
  while ( (c = fgetc(fp)) != EOF ) {
      if ( c == '\n' ) newLineCount++;
  }
  fclose (fp);
  return newLineCount;
}

FILE* readFile(const char *fileName) {
  FILE *fp;
  fp = fopen(fileName, "r");
  if ( fp == NULL ) {
    fprintf(stderr,"Unable to open file '%s' for read access\n", fileName);
    exit(1);
  }

  return fp;
}
void validateStrIsInt(const char *intStr) {
  char * endptr = NULL;
  int out;
  strtol(intStr, &endptr, 10);
  if(*endptr != 0) {
    fprintf(stderr, "Error: Coded message must consist of integers separated by space.\n");
    printUsageMessage();
    exit(1);
  }
}