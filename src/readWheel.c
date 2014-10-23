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
        currentNode = currentNode->previousChild;
      }
    } else {
      for (int k = 0; k < codedMessage[i]; ++k) {
        currentNode = currentNode->nextChild;
      }
    }
    decodedMessage[i] = currentNode->character;
  }

  return decodedMessage;
}


/*****************************************************************************/
/* Construct a wheel                                                         */
/*****************************************************************************/
Node* constuctWheel(char *flatWheel) {
  unsigned long wheelLength = strlen(flatWheel);

  /* instantiate root separately */
  Node *root = newNode(flatWheel[0]);
  Node *previousNode = NULL;
  Node *currentNode = root;

  for (int i = 1; i < wheelLength; ++i) {
    currentNode->nextChild     = newNode(flatWheel[i]);
    currentNode->previousChild = previousNode;

    previousNode = currentNode;
    currentNode = currentNode->nextChild;
  }
  /* link the ends of the wheel*/
  currentNode->nextChild = root;
  currentNode->previousChild = previousNode;
  root->previousChild = currentNode;
  // DELETE:
  // printWheel(root);
  return root;
}

// DELETE: since wouldn't work for other wheels
// void printWheel(Node *root) {
//   do {
//     printf("%c\n", root->character);
//     root = (*root).previousChild;
//   } while(root->character != 'A'); // } while(1);
// }


Node* newNode(char character) {
  Node *node = malloc(sizeof *node);

  (*node).character = character;
  (*node).nextChild = NULL;
  (*node).previousChild = NULL;

  // return pointer to the newly created node
  return node;
}


/*****************************************************************************/
/* Parce Coded Message                                                       */
/*****************************************************************************/
int* parseIntegers(int argc, char const *argv[]) {
  int *codedMessage = malloc((argc-2) * sizeof *codedMessage);

  int i;
  int j = 0;
  /* skip first arguements which aren't integers */
  // TODO: are we incrementing i & j properly?? http://stackoverflow.com/questions/24853/what-is-the-difference-between-i-and-i
  for (i = 2; i < argc; ++i, j++) {
    codedMessage[j] = atoi(argv[i]);
    // printf("%i ", codedMessage[j]);
  }
  return codedMessage;
}

/*****************************************************************************/
/* Parce Wheel                                                               */
/*****************************************************************************/
char* parseWheelFile(char fileName[]) {
  /* TODO: Shall we rather assume that characters are strings? */

  FILE *fp = readFile(fileName);
  int linesInFile = countLines(fileName);

  /* allocate enough memory to store characters from each line in the wheel file */
  char line[3];
  char *flatWheel = malloc(linesInFile * sizeof *flatWheel);
  int i = 0;
  while (fgets(line, 3, fp) != NULL) {
    flatWheel[i] = line[0]; // alt: sscanf (line, "%c", &line[0]);
    i++;
  }

  fclose (fp);
  return flatWheel;
}


int countLines(char fileName[]) {
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

FILE* readFile(char fileName[]) {
  FILE *fp;
  fp = fopen(fileName, "r");
  if ( fp == NULL ) {
    printf (" Cannot open file for read access \n ");
    exit (1);
  }
  return fp;
}