#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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
std::string byte_array_to_string(byte byte_array[], int size_of_array);

int main() {
    unsigned char* pkm_bytes = readFileBytes("snorlax.pkx");
    pokemon* pkm = (pokemon*) pkm_bytes;
    free(pkm_bytes);
    std::ostringstream json;
    //json << "{\"" << "encryptionKey" << "\":\"" << (dword) pkm->encryptionKey << "\",";
    std::cout << "{\"" << "encryptionKey" << "\":\"" << (dword) pkm->encryptionKey << "\",";
    std::cout << "\"" << "sanityPlaceholder" << "\":\"" << (word) pkm->sanityPlaceholder << "\",";
    std::cout << "\"" << "checksum" << "\":\"" << (word) pkm->checksum << "\",";
    std::cout << "\"" << "pokedexID" << "\":\"" << (word) pkm->pokedexID << "\",";
    std::cout << "\"" << "heldItem" << "\":\"" << (word) pkm->heldItem << "\",";
    std::cout << "\"" << "OTID" << "\":\"" << (word) pkm->OTID << "\",";
    std::cout << "\"" << "SecretOTID" << "\":\"" << (word) pkm->SecretOTID << "\",";
    std::cout << "\"" << "experience" << "\":\"" << (dword) pkm->experience << "\",";
    std::cout << "\"" << "ability" << "\":\"" << (int) pkm->ability << "\",";
    std::cout << "\"" << "abilityNumber" << "\":\"" << (int) pkm->abilityNumber << "\",";
    std::cout << "\"" << "hitsRemaining" << "\":\"" << pkm->hitsRemaining << "\",";
    std::cout << "\"" << "bag" << "\":\"" << pkm->bag << "\",";
    std::cout << "\"" << "pid" << "\":\"" << pkm->pid << "\",";
    std::cout << "\"" << "nature" << "\":\"" << (int) pkm->nature << "\",";
    std::cout << "\"" << "variousFlags" << "\":\"" << pkm->variousFlags << "\",";
    std::cout << "\"" << "hp_EV" << "\":\"" << pkm->hp_EV << "\",";
    std::cout << "\"" << "atk_EV" << "\":\"" << pkm->atk_EV << "\",";
    std::cout << "\"" << "def_EV" << "\":\"" << pkm->def_EV << "\",";
    std::cout << "\"" << "speed_EV" << "\":\"" << pkm->speed_EV << "\",";
    std::cout << "\"" << "spa_EV" << "\":\"" << pkm->spa_EV << "\",";
    std::cout << "\"" << "spd_EV" << "\":\"" << pkm->spd_EV << "\",";
    std::cout << "\"" << "cool" << "\":\"" << pkm->cool << "\",";
    std::cout << "\"" << "beauty" << "\":\"" << pkm->beauty << "\",";
    std::cout << "\"" << "smart" << "\":\"" << pkm->smart << "\",";
    std::cout << "\"" << "tough" << "\":\"" << pkm->tough << "\",";
    std::cout << "\"" << "sheen" << "\":\"" << pkm->sheen << "\",";
    std::cout << "\"" << "markings" << "\":\"" << pkm->markings << "\",";
    std::cout << "\"" << "pokerus" << "\":\"" << pkm->pokerus << "\",";
    std::cout << "\"" << "training" << "\":\"" << pkm->training << "\",";
    std::cout << "\"" << "ribbons" << "\":\"" << pkm->ribbons << "\",";
    std::cout << "\"" << "unusedOne" << "\":\"" << pkm->unusedOne << "\",";
    std::cout << "\"" << "contestMemoryRibbons" << "\":\"" << pkm->contestMemoryRibbons << "\",";
    std::cout << "\"" << "battleMemoryRibbons" << "\":\"" << pkm->battleMemoryRibbons << "\",";
    std::cout << "\"" << "unusedTwo" << "\":\"" << pkm->unusedTwo << "\",";
    std::cout << "\"" << "name" << "\":\"" << byte_array_to_string(pkm->name, 24) << "\",";
    std::cout << "\"" << "nullTerminator" << "\":\"" << (word) pkm->nullTerminator << "\",";
    std::cout << "\"" << "moveOneID" << "\":\"" << pkm->moveOneID << "\",";
    std::cout << "\"" << "moveTwoID" << "\":\"" << pkm->moveTwoID << "\",";
    std::cout << "\"" << "moveThreeID" << "\":\"" << pkm->moveThreeID << "\",";
    std::cout << "\"" << "moveFourID" << "\":\"" << pkm->moveFourID << "\",";
    std::cout << "\"" << "moveOneCurrPP" << "\":\"" << pkm->moveOneCurrPP << "\",";
    std::cout << "\"" << "moveTwoCurrPP" << "\":\"" << pkm->moveTwoCurrPP << "\",";
    std::cout << "\"" << "moveThreeCurrPP" << "\":\"" << pkm->moveThreeCurrPP << "\",";
    std::cout << "\"" << "moveFourCurrPP" << "\":\"" << pkm->moveFourCurrPP << "\",";
    std::cout << "\"" << "moveOnePPups" << "\":\"" << pkm->moveOnePPups << "\",";
    std::cout << "\"" << "moveTwoPPups" << "\":\"" << pkm->moveTwoPPups << "\",";
    std::cout << "\"" << "moveThreePPups" << "\":\"" << pkm->moveThreePPups << "\",";
    std::cout << "\"" << "moveFourPPups" << "\":\"" << pkm->moveFourPPups << "\",";
    std::cout << "\"" << "relearnMoveOne" << "\":\"" << pkm->relearnMoveOne << "\",";
    std::cout << "\"" << "relearnMoveTwo" << "\":\"" << pkm->relearnMoveTwo << "\",";
    std::cout << "\"" << "relearnMoveThree" << "\":\"" << pkm->relearnMoveThree << "\",";
    std::cout << "\"" << "relearnMoveFour" << "\":\"" << pkm->relearnMoveFour << "\",";
    std::cout << "\"" << "trainingFlag" << "\":\"" << pkm->trainingFlag << "\",";
    std::cout << "\"" << "unusedThree" << "\":\"" << pkm->unusedThree << "\",";
    std::cout << "\"" << "ivblock" << "\":\"" << pkm->ivblock << "\",";
    std::cout << "\"" << "lastHandler" << "\":\"" << pkm->lastHandler << "\",";
    std::cout << "\"" << "nullTerminatorTwo" << "\":\"" << pkm->nullTerminatorTwo << "\",";
    std::cout << "\"" << "lastHandlerGender" << "\":\"" << pkm->lastHandlerGender << "\",";
    std::cout << "\"" << "currentlyOwnedByOT" << "\":\"" << pkm->currentlyOwnedByOT << "\",";
    std::cout << "\"" << "geolocationOne" << "\":\"" << pkm->geolocationOne << "\",";
    std::cout << "\"" << "geolocationTwo" << "\":\"" << pkm->geolocationTwo << "\",";
    std::cout << "\"" << "geolocationThree" << "\":\"" << pkm->geolocationThree << "\",";
    std::cout << "\"" << "geolocationFour" << "\":\"" << pkm->geolocationFour << "\",";
    std::cout << "\"" << "geolocationFive" << "\":\"" << pkm->geolocationFive << "\",";
    std::cout << "\"" << "unusedFour" << "\":\"" << pkm->unusedFour << "\",";
    std::cout << "\"" << "unusedFive" << "\":\"" << pkm->unusedFive << "\",";
    std::cout << "\"" << "handlerFriendship" << "\":\"" << pkm->handlerFriendship << "\",";
    std::cout << "\"" << "handlerAffection" << "\":\"" << pkm->handlerAffection << "\",";
    std::cout << "\"" << "handlerMemoryIntensity" << "\":\"" << pkm->handlerMemoryIntensity << "\",";
    std::cout << "\"" << "handlerMemoryFeeling" << "\":\"" << pkm->handlerMemoryFeeling << "\",";
    std::cout << "\"" << "unusedSix" << "\":\"" << pkm->unusedSix << "\",";
    std::cout << "\"" << "handlerMemoryTextVar" << "\":\"" << pkm->handlerMemoryTextVar << "\",";
    std::cout << "\"" << "unusedSeven" << "\":\"" << pkm->unusedSeven << "\",";
    std::cout << "\"" << "unusedEight" << "\":\"" << pkm->unusedEight << "\",";
    std::cout << "\"" << "fullness" << "\":\"" << pkm->fullness << "\",";
    std::cout << "\"" << "enjoyment" << "\":\"" << pkm->enjoyment << "\",";
    std::cout << "\"" << "OTName" << "\":\"" << byte_array_to_string(pkm->OTName, 24) << "\",";
    std::cout << "\"" << "OTNameNullTerminator" << "\":\"" << pkm->OTNameNullTerminator << "\",";
    std::cout << "\"" << "OTFriendship" << "\":\"" << pkm->OTFriendship << "\",";
    std::cout << "\"" << "OTAffection" << "\":\"" << pkm->OTAffection << "\",";
    std::cout << "\"" << "OTMemoryIntensity" << "\":\"" << (int) pkm->OTMemoryIntensity << "\",";
    std::cout << "\"" << "OTMemoryLine" << "\":\"" << (int) pkm->OTMemoryLine << "\",";
    std::cout << "\"" << "OTMemoryTextVar" << "\":\"" << (int) pkm->OTMemoryTextVar << "\",";
    std::cout << "\"" << "OTMemoryFeeling" << "\":\"" << (int) pkm->OTMemoryFeeling << "\",";
    std::cout << "\"" << "dateEggReceived" << "\":\"" << (char*) pkm->dateEggReceived << "\",";
    std::cout << "\"" << "dateMet" << "\":\"" << pkm->dateMet << "\",";
    std::cout << "\"" << "unusedNine" << "\":\"" << pkm->unusedNine << "\",";
    std::cout << "\"" << "eggLocation" << "\":\"" << pkm->eggLocation << "\",";
    std::cout << "\"" << "metAtLocation" << "\":\"" << pkm->metAtLocation << "\",";
    std::cout << "\"" << "pokeball" << "\":\"" << (int) pkm->pokeball << "\",";
    std::cout << "\"" << "encounterLevel" << "\":\"" << pkm->encounterLevel << "\",";
    std::cout << "\"" << "encouterTypeGenIV" << "\":\"" << pkm->encouterTypeGenIV << "\",";
    std::cout << "\"" << "OTGameID" << "\":\"" << pkm->OTGameID << "\",";
    std::cout << "\"" << "countryID" << "\":\"" << pkm->countryID << "\",";
    std::cout << "\"" << "regionID" << "\":\"" << pkm->regionID << "\",";
    std::cout << "\"" << "DSRegionID" << "\":\"" << pkm->DSRegionID << "\",";
    std::cout << "\"" << "OTLanguageID" << "\":\"" << pkm->OTLanguageID << "\",";
    std::cout << "\"" << "unusedTen" << "\":\"" << pkm->unusedTen << "\"}";
    std::cout << json.str() << "\n";
    std::ofstream file("json.txt", std::fstream::out);
    file << json.str();
    file.close();
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

std::string byte_array_to_string(byte byte_array[], int size_of_array) {
    std::ostringstream oss("");
    for (int i = 0; i < size_of_array; i++) {
        oss << byte_array[i];
    }
    return oss.str();
}
