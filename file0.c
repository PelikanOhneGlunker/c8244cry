#pragma once

#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static const uint8_t hashlist[] = {
    0x16, 0x61, 0x1B, 0xBC, 0xCC, 0xCA, 0xA7, 0x71, 0x11, 0x19, 0x99, 0x91, 0x15, 0x5B,
    0xB5, 0x50, 0x07, 0x76, 0x64, 0x4B, 0xB4, 0x4A, 0xAB, 0xBE, 0xE8, 0x86, 0x65, 0x52
};

void crypt(const char* text, uintptr_t** calculationMem_out, int length, bool addition = true) {// nr of elements is length
    if (!text || !calculationMem_out) return;
    uintptr_t* calculationMem = static_cast<uintptr_t*>(
        malloc(sizeof(uintptr_t) * length)
    );
    if (!calculationMem) {
        perror("malloc calculationMem");
        *calculationMem_out = NULL;
        return;
    }
    /* allocate and fill hash bytes of same length (cycled through hashlist) */
    uint8_t* hash = static_cast<uint8_t*>(
        malloc(sizeof(uint8_t) * length)
        );
    if (!hash) {
        perror("malloc hash");
        free(calculationMem);
        *calculationMem_out = NULL;
        return;
    }
    /* Nr of elements in list */
    size_t hashlist_len = sizeof(hashlist) / sizeof(hashlist[0]);
    for (size_t i = 0; i < length; ++i) {
        hash[i] = hashlist[i % hashlist_len];
    }
    /* compute sums into calculationMem */
    if (addition) {
        for (size_t i = 0; i < length; ++i) {
            calculationMem[i] = (uintptr_t)((uint8_t)text[i]) + (uintptr_t)hash[i];
            printf("%" PRIuPTR " ", calculationMem[i]);
        }
    }
    else {
        for (size_t i = 0; i < length; ++i) {
            calculationMem[i] = (uintptr_t)((uint8_t)text[i]) - (uintptr_t)hash[i];
            printf("%" PRIuPTR " ", calculationMem[i]);
        }
    }

    printf("\n");
    *calculationMem_out = calculationMem;
}

void printContent(const char* inddd, const char* name, bool addition = true) {
    if (addition) {
        if (inddd) printf("idddd variable verschlüsselt: %s\n", inddd);
        else printf("idddd variable: (null)\n");
        if (name) printf("name variable verschlüsselt: %s\n", name);
        else printf("name variable: (null)\n");
    }
    else {
        if (inddd) printf("idddd variable entschlüsselt: %s\n", inddd);
        else printf("idddd variable: (null)\n");
        if (name) printf("name variable entschlüsselt: %s\n", name);
        else printf("name variable: (null)\n");
    }
}

int main(void) {
    puts("start program");
    char iddd[] = "58916467893456012745";
    int idddd_len = 20;
    char name[] = "Magenta-WLAN-DKL7";
    int name_len = 23;

    uintptr_t* calcMem = NULL;
    printContent(iddd, name);
    crypt(iddd, &calcMem, idddd_len);
    printContent(iddd, name);
    free(calcMem);
    uintptr_t* calcMemName = NULL;
    crypt(name, &calcMemName, name_len);
    printContent(iddd, name);
    free(calcMemName);

    uintptr_t* calcDecryMem = NULL;
    crypt(iddd, &calcDecryMem, idddd_len, false);
    printContent(iddd, name, false);
    free(calcDecryMem);
    uintptr_t* calcDecryMemName = NULL;
    crypt(name, &calcDecryMemName, name_len, false);
    printContent(iddd, name, false);
    free(calcDecryMemName);
    
    puts("finish program");
    while (true);
    return 0;
}
