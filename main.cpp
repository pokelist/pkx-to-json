#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>

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
    word SecretOTID;
    dword experience;
    byte ability;
    byte abilityNumber;
    byte hitsRemaining;
    byte bag;
    
    dword pid;
    byte nature;

    byte variousFlags;

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
    
    byte unusedOne[3];

    byte contestMemoryRibbons;
    byte battleMemoryRibbons;
    byte unusedTwo[6];

    // Block B
    // The name
    byte name[24];
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
    byte lastHandler[24];
    word nullTerminatorTwo;
    byte lastHandlerGender;
    byte currentlyOwnedByOT;

    word geolocationOne;
    word geolocationTwo;
    word geolocationThree;
    word geolocationFour;
    word geolocationFive;
    word unusedFour;
    word unusedFive;

    byte handlerFriendship;
    byte handlerAffection;
    byte handlerMemoryIntensity;
    byte handlerMemoryFeeling;
    byte unusedSix;
    word handlerMemoryTextVar;
    word unusedSeven;
    word unusedEight;
    byte fullness;
    byte enjoyment;

    byte OTName[24];
    word OTNameNullTerminator;
    byte OTFriendship;
    byte OTAffection;
    byte OTMemoryIntensity;
    byte OTMemoryLine;
    word OTMemoryTextVar;
    byte OTMemoryFeeling;

    byte dateEggReceived[3];
    byte dateMet[3];
    byte unusedNine;
    word eggLocation;
    word metAtLocation;
    byte pokeball;
    byte encounterLevel;
    byte encouterTypeGenIV;

    byte OTGameID;
    byte countryID;
    byte regionID;
    byte DSRegionID;
    byte OTLanguageID;
    dword unusedTen;
};

long getFileSize(FILE *file);
unsigned char* readFileBytes(const char *name);
pokemon populateFields(unsigned char* pkm);

int main() {
    std::string json;
    //unsigned char* pkm_bytes = readFileBytes("snorlax.pkx");
    pokemon* pkm = (pokemon*) readFileBytes("snorlax.pkx");
    //free(pkm_bytes);
    
    free(pkm);
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
