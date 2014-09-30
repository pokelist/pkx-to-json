#include <iostream>
#include <stdio.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

struct pokemon {
    // Uncrypted bytes
    dword encryptionKey;
    word sanityPlaceholder;
    word checksum;

    // Block A
    word pokedexID;
    word heldItem;
    word OTID;
    word experience;
    byte ability;
    byte abilityNumber;
    word hitsRemaining;
    byte bag;
    
    dword pid;
    byte nature;

    // EV's
    byte hp_EV;
    byte atk_EV;
    byte def_EV;
    byte speed_EV;
    byte spa_EV;
    byte spd_EV;
    
    // Contest stats
    byte cool;
    byte beauty;
    byte smart;
    byte tough;
    byte sheen;

    byte markings;
    byte pokerus;
    
    dword training;
    dword ribbons;
    
    byte unusedOne[2];

    byte contestMemoryRibbons;
    byte battleMemoryRibbons;
    byte unusedTwo[5];

    // Block B
    // The name
    byte name[23];
    word nullTerminator;

    // Moves
    word moveOneID;
    word moveTwoID;
    word moveThreeID;
    word moveFourID;

    // PP
    byte moveOneCurrPP;
    byte moveTwoCurrPP;
    byte moveThreeCurrPP;
    byte moveFourCurrPP;

    byte moveOnePPups;
    byte moveTwoPPups;
    byte moveThreePPups;
    byte moveFourPPups;

    word relearnMoveOne;
    word relearnMoveTwo;
    word relearnMoveThree;
    word relearnMoveFour;

    byte trainingFlag;
    byte unusedThree;

    dword ivblock;
    byte rest[111];
};

long getFileSize(FILE *file);
unsigned char* readFileBytes(const char *name);
pokemon populateFields(unsigned char* pkm);

int main() {
    unsigned char* pkm_bytes = readFileBytes("snorlax.pkx");
    pokemon* pkm = (pokemon*) pkm_bytes;
    std::cout << pkm->pokedexID << "\n";

    return 0;
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

long getFileSize(FILE *file) {
    long lCurPos, lEndPos;
    lCurPos = ftell(file);
    fseek(file, 0, 2);
    lEndPos = ftell(file);
    fseek(file, lCurPos, 0);
    return lEndPos;
}

pokemon populateFields(unsigned char* bytes) {
    pokemon pkm;
    pkm.ability = bytes[0x14];
    pkm.abilityNumber = bytes[0x15];
    pkm.nature = bytes[0x1C];

    pkm.hp_EV = bytes[0x1E];
    pkm.atk_EV = bytes[0x1F];
    pkm.def_EV = bytes[0x20];
    pkm.speed_EV = bytes[0x21];
    pkm.spa_EV = bytes[0x22];
    pkm.spd_EV = bytes[0x23];
    std::cout << pkm.ability;
    return pkm;
}
