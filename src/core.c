#include "core.h"


/*****************************************************************************/
/* Function: parseIntegers                                                   */
/*    Reads arguements passed from command line and extracts an integer      */
/*    array (coded message) from them. Prints an error if the coded          */
/*    message contains a non-digit value                                     */
/* Parameters:                                                               */
/*    argc       Number of arguements passed from command line               */
/*    argv[]     Array of arguements passed from command line                */
/* Returns:                                                                  */
/*    An array of integers representing the coded message                    */
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
/* Function: validateStrIsInt                                                */
/*    Validates that the passed string contains a valid digit value.         */
/*    Prints an error message and exits if it contains a non-digit value     */
/* Parameters:                                                               */
/*    intStr     a string                                                    */
/* Returns:                                                                  */
/*    (nothing)                                                              */
/*****************************************************************************/
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


/*****************************************************************************/
/* Function: parseIntegers                                                   */
/*    Opens and reads the the first character of each line in a wheel file   */
/*    writing all characters to the flatWheel string.                        */
/*    Prints an error and exits if unable to read the file or if             */
/*    the wheel file contains more than one character per line.              */
/* Parameters:                                                               */
/*    fileName       Points to string containing file name to open           */
/* Returns:                                                                  */
/*    A string with all characters in the wheel file                         */
/*****************************************************************************/
char* parseWheelFile(const char *fileName) {
  FILE *fp = openFile(fileName);
  int linesInFile = countLines(fileName);
  /* stores temp character */
  char ch;
  /* allocate enough memory for all the characters in the file */
  char *flatWheel = malloc(linesInFile * sizeof *flatWheel);
  /* counts length of characters per line in a file */
  int length = 0;

  for (int i = 0; i < linesInFile+1; ++i) {
    /* loops until reaches the end of the line or EOF */
    while ( ((ch = fgetc(fp)) != EOF) && (ch != '\n') ) {
      flatWheel[i] = ch;
      length++;
      /* make sure there's only one character on this line */
      if (length == 2) {
        fprintf(stderr, "Error: Wheel file must contain only one character per line.\n");
        printUsageMessage();
        fclose(fp);
        exit(1);
      }
    }
    length = 0; // reset length
  }

  fclose (fp);
  return flatWheel;
}

/*****************************************************************************/
/* Function: countLines                                                      */
/*    Counts number of newline characters in a file to determine number of   */
/*    lines in a file                                                        */
/* Parameters:                                                               */
/*    fileName       Points to string containing file name to open           */
/* Returns:                                                                  */
/*    Number of lines in a file                                              */
/*****************************************************************************/
int countLines(const char *fileName) {
  FILE *fp = openFile(fileName);

  int  c;
  unsigned long newLineCount = 0;

  /* count newline characters */
  while ( (c = fgetc(fp)) != EOF ) {
      if ( c == '\n' )
        newLineCount++;
  }
  fclose (fp);
  return newLineCount;
}

/*****************************************************************************/
/* Function: openFile                                                        */
/*    Opens a file. Prints an error message and exits if unable              */
/*     to open a file                                                        */
/* Parameters:                                                               */
/*    fileName       Points to string containing file name to open           */
/* Returns:                                                                  */
/*    A pointer to the file                                                  */
/*****************************************************************************/
FILE* openFile(const char *fileName) {
  FILE *fp;
  fp = fopen(fileName, "r");
  if ( fp == NULL ) {
    fprintf(stderr,"Unable to open file '%s' for read access\n", fileName);
    exit(1);
  }

  return fp;
}

/*****************************************************************************/
/* Function: constructWheel                                                  */
/*    Reads the contents of the string (sequence of all characters           */
/*    in the wheel file) and creates a linked list containing all characters */
/*    in the order they appear in the wheel file.                            */
/* Parameters:                                                               */
/*    flatWheel   Points to a string containing all characters               */
/*                in the wheel file                                          */
/* Returns:                                                                  */
/*    A pointer to the first node in the list.                               */
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

/*****************************************************************************/
/* Function: newNode                                                         */
/*    Allocates memory to a new node and populates it with the passed        */
/*    character. The next and previous pointers are set to NULL.             */
/* Parameters:                                                               */
/*    character  A character read from the wheel file                        */
/* Returns:                                                                  */
/*    A pointer to the new node.                                             */
/*****************************************************************************/
Node* newNode(char character) {
  Node *node = malloc(sizeof *node);
  node->character = character;
  node->next = NULL;
  node->previous = NULL;

  return node;
}


/*****************************************************************************/
/* Function: decodeMessage                                                   */
/*       Decodes passed coded message using the given linked list            */
/* Parameters:                                                               */
/*    root              A pointer to the first node in the list.             */
/*    codedMessage      An integer array containing coded message            */
/*    lengthOfMessage   Length of the codedMessage array                     */
/* Returns:                                                                  */
/*    a pointer to a string contained the decoded message                    */
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