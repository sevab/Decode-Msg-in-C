#include "decodeMessage.h"
#include "readWheel.h"

/*TODO
  - Make sure files are closed everywhere
  - rename readWheel.c to smth else considering that it parses, constructs & decodes.
      ALT: create 3 separate files for each function.
  - explain what I mean by flatWheel
  - shall we free memory and delete the list at the end of the program? (Google this)
    Also, run that memory-leaking catching UTILITY
  - refactor: rename previousChild & nextChild to previous & next
  - try creating my own weird wheel (repeating chars, white spaces, etc)
  - (!!!) catch errors if we pass something useless (e.g. non-integers, corrupt files, etc)
  - rename constuct method to construct
 */

int main(int argc, char const *argv[]) {
  // Print args
  printArgs(argc, argv);

  // Process Wheel File
  char fileName[100];
  strcpy(fileName, argv[1]);
  char* flatWheel = parseWheelFile(fileName);
  printf("Decoding wheel values:\n");
  printf("  %s\n", flatWheel);

  // Construct a decoding wheel
  Node* root = constuctWheel(flatWheel);

  // Convert coded message to an int array
  int *codedMessage = parseIntegers(argc, argv);

  // Decode coded message
  char *decodedMessage = decodeMessage(root, codedMessage, argc-2);
  printf("Decoded message:\n");
  printf("  %s\n", decodedMessage);
  return 0;
}



void printArgs(int argc, char const *argv[]) {
  printf("Parameter listing:\n");
  for (int i = 1; i < argc; ++i) {
    printf("  %i: %s\n", i, argv[i]);
  }
}