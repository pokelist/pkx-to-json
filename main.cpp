#include <iostream>
#include <stdio.h>

// Get the size of a file
long getFileSize(FILE *file) {
    long lCurPos, lEndPos;
    lCurPos = ftell(file);
    fseek(file, 0, 2);
    lEndPos = ftell(file);
    fseek(file, lCurPos, 0);
    return lEndPos;
}

unsigned char* readFileBytes(const char *name) {
    long fileSize;
    unsigned char *buffer;
    FILE *file;

    if (!(file = fopen(name, "rb"))) {
        std::cout << "Could not open specified file" << std::endl;
    }

    fileSize = getFileSize(file);

    // Make room!
    buffer = new unsigned char[fileSize];
    // Read it!
    fread(buffer, fileSize, 1, file);
    return buffer;
}

int main() {
    unsigned char* pkm = readFileBytes("snorlax.pkx");
    // print the array 
    for (int i = 0; i <= 232; i++)
        printf("%X ", pkm[i]);
}
