#include "decodeMessage.h"


/*****************************************************************************/
/* Function: main                                                            */
/*****************************************************************************/
int main(int argc, char const *argv[]) {
  validateArgsLength(argc, argv);
  /* Convert coded message to an int array if it consists of valid integers */
  int *codedMessage = parseIntegers(argc, argv);

  printArgs(argc, argv);

  /* Process wheel file and print wheel values */
  char* flatWheel = parseWheelFile(argv[1]);
  printf("Decoding wheel values:\n  %s\n\n", flatWheel);

  /* Construct a decoding wheel */
  Node* root = constructWheel(flatWheel);

  /* Decode and print coded message */
  char *decodedMessage = decodeMessage(root, codedMessage, argc-2);
  printf("Decoded message:\n  %s\n\n", decodedMessage);

  return 0;
}

/*****************************************************************************/
/* Function: printArgs                                                       */
/*    Prints every arguement passed from command line                        */
/* Parameters:                                                               */
/*    argc       Number of arguements passed from command line               */
/*    argv[]     Array of arguements passed from command line                */
/* Returns:                                                                  */
/*    (nothing)                                                              */
/*****************************************************************************/
void printArgs(int argc, char const *argv[]) {
  printf("Parameter listing:\n");
  for (int i = 1; i < argc; ++i) {
    printf("  %i: %s\n", i, argv[i]);
  }
  printf("\n");
}

/*****************************************************************************/
/* Function: validateArgsLength                                              */
/*    Prints an error message and exits if the arguement list contains       */
/*    less than 3 arguements                                                 */
/* Parameters:                                                               */
/*    argc       Number of arguements passed from command line               */
/*    argv[]     Array of arguements passed from command line                */
/* Returns:                                                                  */
/*    (nothing)                                                              */
/*****************************************************************************/
void validateArgsLength(int argc, char const *argv[]) {
  if ( argc < 3 ) {
    fprintf(stderr, "Error: You forgot to pass coded message.\n");
    printUsageMessage();
    exit(1);
  }
}

/*****************************************************************************/
/* Function: printUsageMessage                                               */
/*    Prints an error message explaining the usage of the decodeMessage app  */
/* Parameters:                                                               */
/*    (nothing)                                                              */
/* Returns:                                                                  */
/*    (nothing)                                                              */
/*****************************************************************************/
void printUsageMessage() {
  fprintf(stderr,"Usage: decodeMessage <fileName> [coded message consisting of integers separated by space]\n");
}