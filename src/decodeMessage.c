#include "decodeMessage.h"
#include "readWheel.h"

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



void printArgs(int argc, char const *argv[]) {
  printf("Parameter listing:\n");
  for (int i = 1; i < argc; ++i) {
    printf("  %i: %s\n", i, argv[i]);
  }
  printf("\n");
}

/* Make sure at least 2 args are passed */
void validateArgsLength(int argc, char const *argv[]) {
  if ( argc < 3 ) {
    fprintf(stderr, "Error: You forgot to pass coded message.\n");
    printUsageMessage();
    exit(1);
  }
}
void printUsageMessage() {
  fprintf(stderr,"Usage: decodeMessage <fileName> [coded message consisting of integers separated by space]\n");
}