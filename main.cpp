#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define VARASSTR(v) #v

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
    unsigned char* pkm_bytes = readFileBytes("snorlax.pkx");
    pokemon* pkm = (pokemon*) pkm_bytes;
    free(pkm_bytes);
    std::ostringstream json;
    json << "{\"" << "encryptionKey" << "\":\"" << pkm->encryptionKey << "\",";
    json << "\"" << "sanityPlaceholder" << "\":\"" << pkm->sanityPlaceholder << "\",";
    json << "\"" << "checksum" << "\":\"" << pkm->checksum << "\",";
    json << "\"" << "pokedexID" << "\":\"" << pkm->pokedexID << "\",";
    json << "\"" << "heldItem" << "\":\"" << pkm->heldItem << "\",";
    json << "\"" << "OTID" << "\":\"" << pkm->OTID << "\",";
    json << "\"" << "SecretOTID" << "\":\"" << pkm->SecretOTID << "\",";
    json << "\"" << "experience" << "\":\"" << pkm->experience << "\",";
    json << "\"" << "ability" << "\":\"" << (int) pkm->ability << "\",";
    json << "\"" << "abilityNumber" << "\":\"" << (int) pkm->abilityNumber << "\",";
    json << "\"" << "hitsRemaining" << "\":\"" << (int) pkm->hitsRemaining << "\",";
    json << "\"" << "bag" << "\":\"" << (int) pkm->bag << "\",";
    json << "\"" << "pid" << "\":\"" << pkm->pid << "\",";
    json << "\"" << "nature" << "\":\"" << pkm->nature << "\",";
    json << "\"" << "variousFlags" << "\":\"" << pkm->variousFlags << "\",";
    json << "\"" << "hp_EV" << "\":\"" << pkm->hp_EV << "\",";
    json << "\"" << "atk_EV" << "\":\"" << pkm->atk_EV << "\",";
    json << "\"" << "def_EV" << "\":\"" << pkm->def_EV << "\",";
    json << "\"" << "speed_EV" << "\":\"" << pkm->speed_EV << "\",";
    json << "\"" << "spa_EV" << "\":\"" << pkm->spa_EV << "\",";
    json << "\"" << "spd_EV" << "\":\"" << pkm->spd_EV << "\",";
    json << "\"" << "cool" << "\":\"" << pkm->cool << "\",";
    json << "\"" << "beauty" << "\":\"" << pkm->beauty << "\",";
    json << "\"" << "smart" << "\":\"" << pkm->smart << "\",";
    json << "\"" << "tough" << "\":\"" << pkm->tough << "\",";
    json << "\"" << "sheen" << "\":\"" << pkm->sheen << "\",";
    json << "\"" << "markings" << "\":\"" << pkm->markings << "\",";
    json << "\"" << "pokerus" << "\":\"" << pkm->pokerus << "\",";
    json << "\"" << "training" << "\":\"" << pkm->training << "\",";
    json << "\"" << "ribbons" << "\":\"" << pkm->ribbons << "\",";
    json << "\"" << "unusedOne" << "\":\"" << pkm->unusedOne << "\",";
    json << "\"" << "contestMemoryRibbons" << "\":\"" << pkm->contestMemoryRibbons << "\",";
    json << "\"" << "battleMemoryRibbons" << "\":\"" << pkm->battleMemoryRibbons << "\",";
    json << "\"" << "unusedTwo" << "\":\"" << pkm->unusedTwo << "\",";
    json << "\"" << "name" << "\":\"" << pkm->name << "\",";
    json << "\"" << "nullTerminator" << "\":\"" << pkm->nullTerminator << "\",";
    json << "\"" << "moveOneID" << "\":\"" << pkm->moveOneID << "\",";
    json << "\"" << "moveTwoID" << "\":\"" << pkm->moveTwoID << "\",";
    json << "\"" << "moveThreeID" << "\":\"" << pkm->moveThreeID << "\",";
    json << "\"" << "moveFourID" << "\":\"" << pkm->moveFourID << "\",";
    json << "\"" << "moveOneCurrPP" << "\":\"" << pkm->moveOneCurrPP << "\",";
    json << "\"" << "moveTwoCurrPP" << "\":\"" << pkm->moveTwoCurrPP << "\",";
    json << "\"" << "moveThreeCurrPP" << "\":\"" << pkm->moveThreeCurrPP << "\",";
    json << "\"" << "moveFourCurrPP" << "\":\"" << pkm->moveFourCurrPP << "\",";
    json << "\"" << "moveOnePPups" << "\":\"" << pkm->moveOnePPups << "\",";
    json << "\"" << "moveTwoPPups" << "\":\"" << pkm->moveTwoPPups << "\",";
    json << "\"" << "moveThreePPups" << "\":\"" << pkm->moveThreePPups << "\",";
    json << "\"" << "moveFourPPups" << "\":\"" << pkm->moveFourPPups << "\",";
    json << "\"" << "relearnMoveOne" << "\":\"" << pkm->relearnMoveOne << "\",";
    json << "\"" << "relearnMoveTwo" << "\":\"" << pkm->relearnMoveTwo << "\",";
    json << "\"" << "relearnMoveThree" << "\":\"" << pkm->relearnMoveThree << "\",";
    json << "\"" << "relearnMoveFour" << "\":\"" << pkm->relearnMoveFour << "\",";
    json << "\"" << "trainingFlag" << "\":\"" << pkm->trainingFlag << "\",";
    json << "\"" << "unusedThree" << "\":\"" << pkm->unusedThree << "\",";
    json << "\"" << "ivblock" << "\":\"" << pkm->ivblock << "\",";
    json << "\"" << "lastHandler" << "\":\"" << pkm->lastHandler << "\",";
    json << "\"" << "nullTerminatorTwo" << "\":\"" << pkm->nullTerminatorTwo << "\",";
    json << "\"" << "lastHandlerGender" << "\":\"" << pkm->lastHandlerGender << "\",";
    json << "\"" << "currentlyOwnedByOT" << "\":\"" << pkm->currentlyOwnedByOT << "\",";
    json << "\"" << "geolocationOne" << "\":\"" << pkm->geolocationOne << "\",";
    json << "\"" << "geolocationTwo" << "\":\"" << pkm->geolocationTwo << "\",";
    json << "\"" << "geolocationThree" << "\":\"" << pkm->geolocationThree << "\",";
    json << "\"" << "geolocationFour" << "\":\"" << pkm->geolocationFour << "\",";
    json << "\"" << "geolocationFive" << "\":\"" << pkm->geolocationFive << "\",";
    json << "\"" << "unusedFour" << "\":\"" << pkm->unusedFour << "\",";
    json << "\"" << "unusedFive" << "\":\"" << pkm->unusedFive << "\",";
    json << "\"" << "handlerFriendship" << "\":\"" << pkm->handlerFriendship << "\",";
    json << "\"" << "handlerAffection" << "\":\"" << pkm->handlerAffection << "\",";
    json << "\"" << "handlerMemoryIntensity" << "\":\"" << pkm->handlerMemoryIntensity << "\",";
    json << "\"" << "handlerMemoryFeeling" << "\":\"" << pkm->handlerMemoryFeeling << "\",";
    json << "\"" << "unusedSix" << "\":\"" << pkm->unusedSix << "\",";
    json << "\"" << "handlerMemoryTextVar" << "\":\"" << pkm->handlerMemoryTextVar << "\",";
    json << "\"" << "unusedSeven" << "\":\"" << pkm->unusedSeven << "\",";
    json << "\"" << "unusedEight" << "\":\"" << pkm->unusedEight << "\",";
    json << "\"" << "fullness" << "\":\"" << pkm->fullness << "\",";
    json << "\"" << "enjoyment" << "\":\"" << pkm->enjoyment << "\",";
    json << "\"" << "OTName" << "\":\"" << pkm->OTName << "\",";
    json << "\"" << "OTNameNullTerminator" << "\":\"" << pkm->OTNameNullTerminator << "\",";
    json << "\"" << "OTFriendship" << "\":\"" << pkm->OTFriendship << "\",";
    json << "\"" << "OTAffection" << "\":\"" << pkm->OTAffection << "\",";
    json << "\"" << "OTMemoryIntensity" << "\":\"" << pkm->OTMemoryIntensity << "\",";
    json << "\"" << "OTMemoryLine" << "\":\"" << pkm->OTMemoryLine << "\",";
    json << "\"" << "OTMemoryTextVar" << "\":\"" << pkm->OTMemoryTextVar << "\",";
    json << "\"" << "OTMemoryFeeling" << "\":\"" << pkm->OTMemoryFeeling << "\",";
    json << "\"" << "dateEggReceived" << "\":\"" << pkm->dateEggReceived << "\",";
    json << "\"" << "dateMet" << "\":\"" << pkm->dateMet << "\",";
    json << "\"" << "unusedNine" << "\":\"" << pkm->unusedNine << "\",";
    json << "\"" << "eggLocation" << "\":\"" << pkm->eggLocation << "\",";
    json << "\"" << "metAtLocation" << "\":\"" << pkm->metAtLocation << "\",";
    json << "\"" << "pokeball" << "\":\"" << pkm->pokeball << "\",";
    json << "\"" << "encounterLevel" << "\":\"" << pkm->encounterLevel << "\",";
    json << "\"" << "encouterTypeGenIV" << "\":\"" << pkm->encouterTypeGenIV << "\",";
    json << "\"" << "OTGameID" << "\":\"" << pkm->OTGameID << "\",";
    json << "\"" << "countryID" << "\":\"" << pkm->countryID << "\",";
    json << "\"" << "regionID" << "\":\"" << pkm->regionID << "\",";
    json << "\"" << "DSRegionID" << "\":\"" << pkm->DSRegionID << "\",";
    json << "\"" << "OTLanguageID" << "\":\"" << pkm->OTLanguageID << "\",";
    json << "\"" << "unusedTen" << "\":\"" << pkm->unusedTen << "\"}";
    std::cout << json.str() << "\n";
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
