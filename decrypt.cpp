#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


enum PkxSizes {
    SIZE_PARTY_PKX      = 260,
    SIZE_BOX_PKX        = 232,
    SIZE_PKX_UNCRYPT    = 8,
    SIZE_PKX_CRYPT_LEN  = SIZE_BOX_PKX - SIZE_PKX_UNCRYPT,
    SIZE_PKX_BLK        = 56,
    SIZE_PKX_PARTY_DATA = 28
};


struct Rnd {
    uint32_t mul;
    uint32_t add;
    uint32_t rmul;
    uint32_t radd;
};


const char orders[24][4] = {
    0, 1, 2, 3,
    0, 1, 3, 2,
    0, 2, 1, 3,
    0, 3, 1, 2,
    0, 2, 3, 1,
    0, 3, 2, 1,
    1, 0, 2, 3,
    1, 0, 3, 2,
    2, 0, 1, 3,
    3, 0, 1, 2,
    2, 0, 3, 1,
    3, 0, 2, 1,
    1, 2, 0, 3,
    1, 3, 0, 2,
    2, 1, 0, 3,
    3, 1, 0, 2,
    2, 3, 0, 1,
    3, 2, 0, 1,
    1, 2, 3, 0,
    1, 3, 2, 0,
    2, 1, 3, 0,
    3, 1, 2, 0,
    2, 3, 1, 0,
    3, 2, 1, 0,
};


inline void InitRnd(Rnd* r);
inline uint16_t CryptRNG(uint32_t* data, Rnd* r);
void CryptPkx(uint32_t* pkx, uint32_t* key, uint32_t len, Rnd* cr);
inline uint16_t CalcPkxChecksum(uint16_t* pkx, uint32_t len);
bool VerifyPkxChecksum(uint32_t* pkx, uint16_t currentSum, uint32_t len);
void FixPkxChecksum(uint32_t* pkx, uint32_t len);
inline uint32_t GetShuffleType(uint32_t pid);
void UnshufflePkx(uint32_t* pkx_in, uint32_t* pkx_out);
inline void SetUncryptedDataEqual(uint32_t* pkx_in, uint32_t* pkx_out);

int main(int argc, char** argv) {
    FILE* in_pkx;
    FILE* out_pkx;
    uint32_t box_pkx[SIZE_BOX_PKX / sizeof(uint32_t)];
    uint32_t outbox_pkx[SIZE_BOX_PKX / sizeof(uint32_t)];
    uint32_t party_data[SIZE_PKX_PARTY_DATA / sizeof(uint32_t)];
    
    Rnd xypkx;

    InitRnd(&xypkx);

    if (argc < 3) {
        printf("XYCrypt by Bond697\n");
        printf("Based on research by Xfr and Bond697\n\n");
        printf("Usage:\n");
        printf("xypkmcrypt infile outfile\n");
        while (1);
    }

    in_pkx = fopen(argv[1], "rb+");
    if (!in_pkx) {
        printf("Error opening in pkx file.");
        exit(3);
    }

    fseek(in_pkx, 0, SEEK_SET);
    fread(box_pkx, sizeof(uint32_t), SIZE_BOX_PKX / sizeof(uint32_t), in_pkx);

    fseek(in_pkx, 0, SEEK_END);     // get the size of the file
    uint32_t fsz = ftell(in_pkx); 
    fseek(in_pkx, 0, SEEK_SET);

    if ((fsz != SIZE_PARTY_PKX) && (fsz != SIZE_BOX_PKX)) {
        printf("Pkx is the wrong size.");
        exit(5);
    }

    uint32_t decryptKey = box_pkx[0];    // key is now pid, not checksum

    CryptPkx(&box_pkx[2], &decryptKey, SIZE_PKX_CRYPT_LEN, &xypkx);
    UnshufflePkx(box_pkx, outbox_pkx);
    SetUncryptedDataEqual(box_pkx, outbox_pkx);

    if (!VerifyPkxChecksum(&box_pkx[2], (box_pkx[1] >> 16) & 0xFFFF, SIZE_PKX_CRYPT_LEN)) {
        printf("Checksum failed. Fixing.\n\n");
        FixPkxChecksum(box_pkx, SIZE_PKX_CRYPT_LEN);
    }

    if (fsz == SIZE_PARTY_PKX) {
        decryptKey = box_pkx[0];

        fseek(in_pkx, SIZE_BOX_PKX, SEEK_SET);
        fread(party_data, sizeof(uint32_t), SIZE_PKX_PARTY_DATA / sizeof(uint32_t), in_pkx);
    
        CryptPkx(party_data, &decryptKey, SIZE_PKX_PARTY_DATA, &xypkx);
    }

    out_pkx = fopen(argv[2], "wb+");
    if (!out_pkx) {
        printf("Error opening out pkx file.");
        exit(4);
    }

    fseek(out_pkx, 0, SEEK_SET);
    fwrite(outbox_pkx, sizeof(uint32_t), SIZE_BOX_PKX / sizeof(uint32_t), out_pkx);

    if (fsz == SIZE_PARTY_PKX) {
        fseek(out_pkx, SIZE_BOX_PKX, SEEK_SET);
        fwrite(party_data, sizeof(uint32_t), SIZE_PKX_PARTY_DATA / sizeof(uint32_t), out_pkx);
    }

    fclose(in_pkx);
    fclose(out_pkx);

    return 0;
}


void CryptPkx(uint32_t* pkx, uint32_t* key, uint32_t len, Rnd* cr) {
    uint16_t* epkx = (uint16_t*)pkx;
    uint16_t cryptKey = 0;
    
    for (uint32_t i = 0; i < len / 2; ++i) {
        cryptKey = CryptRNG(key, cr);
        epkx[i] ^= cryptKey;
    }
}


inline void InitRnd(Rnd* r) {
    r->mul = 0x41C64E6D;
    r->add = 0x6073;
    r->rmul = 0xEEB9EB65;
    r->radd = 0xA3561A1;
}


inline uint16_t CryptRNG(uint32_t* data, Rnd* r) {
   *data = ((*data * r->mul) + r->add);
   return (*data >> 16);
}


inline uint16_t CalcPkxChecksum(uint16_t* pkx, uint32_t len) {
    uint16_t sum = 0;

    for (uint32_t i = 0; i < len / 2; ++i) {
        sum += pkx[i];

    }
    return sum;
}


bool VerifyPkxChecksum(uint32_t* pkx, uint16_t currentSum, uint32_t len) {
    uint16_t* epkx = (uint16_t*)pkx;

    uint16_t testSum = CalcPkxChecksum(epkx, len);

    if (testSum == currentSum) {
        return true;
    }
    else {
        return false;
    }
}


void FixPkxChecksum(uint32_t* pkx, uint32_t len) {
    uint16_t* epkx = (uint16_t*)pkx;
    uint16_t newSum = CalcPkxChecksum(&epkx[4], len);

    epkx[3] = newSum;
}


inline uint32_t GetShuffleType(uint32_t pid) {
    return ((pid & 0x3E000) >> 0xD) % 24;
}


void UnshufflePkx(uint32_t* pkx_in, uint32_t* pkx_out) {
    uint8_t* eipkx = (uint8_t*)pkx_in;
    uint8_t* eopkx = (uint8_t*)pkx_out;

    uint32_t blockOrder = GetShuffleType(pkx_in[0]);

    for (uint32_t i = 0; i < 4; ++i) {
        memcpy(eopkx + SIZE_PKX_UNCRYPT + (SIZE_PKX_BLK * i), eipkx + SIZE_PKX_UNCRYPT + (SIZE_PKX_BLK * orders[blockOrder][i]), SIZE_PKX_BLK);
    }
}

inline void SetUncryptedDataEqual(uint32_t* pkx_in, uint32_t* pkx_out) {
    for (uint32_t i = 0; i < 2; ++i) {
        pkx_out[i] = pkx_in[i];
    }
}
