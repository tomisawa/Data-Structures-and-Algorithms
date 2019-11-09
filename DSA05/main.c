//
//  main.c
//  DSA05
//
//  Created by tomisawa on 2019/10/31.
//  Copyright © 2019 tomisawa. All rights reserved.
//

#include <stdio.h>
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define HASH(OPERATION, N, DATA)               \
    do {                                         \
        for (int i = 0; i < N; i++) {              \
            if (OPERATION ## HashTable(DATA[i]) < 0) { \
                printf("Error DATA=%d\n", DATA[i]);    \
                ;                                      \
            }                                        \
        }                                          \
    } while (0)

typedef struct {
    enum { EMPTY, USE, DELETE } stat;
    int data;
} HashTable;

HashTable H[24];
const int H_SIZE = COUNTOF(H);

int DATA1[] = { 39, 1, 9, 5, 24, 2, 11, 23, 6, 13 };
const int DATA1_SIZE = COUNTOF(DATA1);

int DATA2[] = { 28, 20, 15, 33 };
const int DATA2_SIZE = COUNTOF(DATA2);

int hash(int x) {
    return x % 24;
}

void InitHashTable() {
    for (int i = 0; i < H_SIZE; i++) {
        H[i].stat = EMPTY;
        H[i].data = 0;
    }
}

void PrintHashValue() {
    printf("\nHash Value\n");
    printf("      x\t: ");
    for (int i = 0; i < DATA1_SIZE; i++) {
        printf("%2d ", DATA1[i]);
    }
    printf("\nhash(x)\t: ");
    for (int i = 0; i < DATA1_SIZE; i++) {
        printf("%2d ", hash(DATA1[i]));
    }
    printf("\n\n");
}

int stimes;
int SearchtHashTable(int data) {
    int hashValue = hash(data);
    stimes = 1;
    while ((H[hashValue].stat != EMPTY && H[hashValue].data != data)) {
        stimes = stimes + 1;
        hashValue = (hashValue + 1) % H_SIZE;
        if (hashValue == hash(data)) return -1;
    }
    if (H[hashValue].stat == USE && H[hashValue].data == data) return hashValue;
    else return -1;
}

// Ref. Algorithm 4.3
int InsertHashTable(int data) {
    int hashValue = hash(data);
    if (SearchtHashTable(data) >= 0) return -1;  // Not allow duplicates
    while (H[hashValue].stat == USE) {
        hashValue = (hashValue + 1) % H_SIZE;
        if (hashValue == hash(data)) return -1;  // Check a round
    }
    H[hashValue].data = data;
    H[hashValue].stat = USE;
    return hashValue;
}

int DeleteHashTable(int data) {
    int i;
    if ((i = SearchtHashTable(data)) < 0) return -1;
    H[i].stat = DELETE;
    H[i].data = -1;
    return 1;
}

void PrintHashTable() {
    printf("Hash Table\n");
    for (int i = 0; i < H_SIZE; i++) {
        printf("%02d ", i);
    }
    printf("\n");
    for (int i = 0; i < H_SIZE; i++) {
        switch (H[i].stat) {
            case EMPTY:
                printf("-- "); break;
            case DELETE:
                printf("DD "); break;
            case USE:
                printf("%02d ", H[i].data); break;
            default:
                printf("!!"); break;
        }
    }
    printf("\n\n");
}

int main(void) {
    int i, data;
    PrintHashValue();
    InitHashTable();

    // Fig4.5(a)
    InsertHashTable(17);
    PrintHashTable();
    HASH(Insert, DATA1_SIZE, DATA1);
    PrintHashTable();

    // FIg4.5(b)
    InsertHashTable(29);
    PrintHashTable();

    // Fig4.5(c)
    HASH(Insert, DATA2_SIZE, DATA2);
    PrintHashTable();

    // Fig.4.6 (a)
    if ((i  = SearchtHashTable(15)) < 0) printf("Not Found(%d times)\n\n", stimes);
    else printf("Found index=%d(%d times)\n\n", i, stimes);

    // Fig.4.6 (b)
    if ((i  = SearchtHashTable(4)) < 0) printf("Not Found(%d times)\n\n", stimes);
    else printf("Found index=%d(%d times)\n\n", i, stimes);

    HASH(Delete, DATA2_SIZE, DATA2);
    PrintHashTable();
    HASH(Delete, DATA1_SIZE, DATA1);
    PrintHashTable();

    HASH(Insert, DATA1_SIZE, DATA1);
    HASH(Insert, DATA2_SIZE, DATA2);
    PrintHashTable();

    while (1) {
        PrintHashTable();
        printf("Search  Data:");
        scanf("%d", &data);
        if ((i  = SearchtHashTable(data)) < 0) printf("Not Found(%d times)\n\n", stimes);
        else printf("Found index=%d(%d times)\n\n", i, stimes);
    }

    return 0;
}
