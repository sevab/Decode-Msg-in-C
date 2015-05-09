## Decode-Msg-in-C
A coursework for History and Applications of C, Objective C, C++ and C# university module I took

### Problem Statement

You have been sent a coded message in the form of a series of positive and negative integers, and a file that contains data which allows you to decode that message. You must write a C program to decode the message.


The file contains a list of characters from which you must create a decoding wheel. Note that the number of characters in the file may vary, there may be repeated characters and they may include, for example, white-space characters.

Your executable program must be called decodeMessage and should accept an unlimited number of parameters from the command line. The first parameter is the name of the file containing the decoding wheel; the remainder are the integers representing the coded message.

```bash
decodeMessage exampleWheel.txt -1 6 2 0 -4
```

The program must read the data contained in the appropriate file and construct a decoding wheel. There are many different ways of doing this, but top marks will only be awarded if the wheel is implemented as a circular, doubly-linked list. Once the decoding wheel has been constructed, the program must process each of the codes (the integers on the command line) to produce the decoded message.

Example program output:
```
Parameter listing:
  1: exampleWheel.txt 2: -1
  3: 6
  4: 2
  5: 0
  6: -4
Decoding wheel values:
  AMWOSEGLPH
Decoded message:
  HELLO
```




### Compilation instructions
To compile the program `cd` into the CW1 directory and run compileLink file in bash using `sh compileLink`. This will compile the appropriate files in the src directory into the build directory and then run the decodeMessage program using an example coded message and example wheel file which is also located in the `src` directory.

To run decodeMessage program using your own wheel file and message place your wheel .txt file into the src directory and run the following command from within the CW1 directory:

```bash
./build/decodeMessage src/nameOfWheelFile.txt [list of integers]
```
