//
//  main.c
//  HashMethod
//
//  Created by tomisawa on 2018/11/28.
//  Copyright © 2018年 tomisawa. All rights reserved.
//

#include <stdio.h>
#define N_HASHTABLE 27
#define N_DATA 18
#define N_ADD_DATA 9

#define HASH(OPERATION, N, DATA)               \
  do {                                         \
    for (int i = 0; i < N; i++) {              \
      if (OPERATION##HashTable(DATA[i]) < 0) { \
        printf("Error DATA=%d\n", DATA[i]);    \
        ;                                      \
      }                                        \
    }                                          \
  } while (0)

typedef enum { EMPTY, USE, DELETE } element_stat;
typedef struct {
  element_stat stat;
  int data;
} HashTable;

int stimes;

HashTable htable[N_HASHTABLE];

int SampleData[N_DATA] = {3, 4, 6, 7, 9, 11, 14, 15, 17,
                          18, 20, 23, 24, 26, 27, 29, 30, 32};
int AddSampleData[N_ADD_DATA] = {2, 5, 8, 10, 12, 13, 16, 19, 21};
int DeleteSampleData[N_ADD_DATA] = {2, 5, 8, 10, 12, 13, 16, 19, 21};

int hash(int x) { return x % 27; }

void Fig2_6() {
  printf("\nHash Value\n");
  printf("      x\t:");
  for (int i = 0; i < N_DATA; i++)
    printf("%2d ", SampleData[i]);
  printf("\nhash[x]\t:");
  for (int i = 0; i < N_DATA; i++)
    printf("%2d ", hash(SampleData[i]));
  printf("\n---\n");
}

void InitHashTable() {
  for (int i = 0; i < N_HASHTABLE; i++) {
    htable[i].stat = EMPTY;
    htable[i].data = 0;
  }
}

int Algorithm2_8() {
  for (int i = 0; i < N_DATA; i++) {
    int hashValue = hash(SampleData[i]);
    while (htable[hashValue].stat != EMPTY)
      hashValue = (hashValue + 1) % N_HASHTABLE;
    htable[hashValue].data = SampleData[i];
    htable[hashValue].stat = USE;
  }
  return 1;
}

int SeartHashTable(int data) {
  int hashValue = hash(data);
  stimes = 1;

  while ((htable[hashValue].stat == USE && htable[hashValue].data != data)) {
    stimes = stimes + 1;
    hashValue = (hashValue + 1) % N_HASHTABLE;
    if (hashValue == hash(data)) return -1;
  }

  if (htable[hashValue].stat == USE && htable[hashValue].data == data)
    return hashValue;
  else
    return -1;
}

int InsertHashTable(int data) {
  int hashValue = hash(data);
  if (SeartHashTable(data) >= 0) return -1;
  while (htable[hashValue].stat == USE) {
    hashValue = (hashValue + 1) % N_HASHTABLE;
    if (hashValue == hash(data)) return -1;
  }
  htable[hashValue].data = data;
  htable[hashValue].stat = USE;
  return hashValue;
}

void PrintHashTable() {
  printf("Hash Table\n");
  for (int i = 0; i < N_HASHTABLE; i++)
    printf("%02d ", i);
  printf("\n");
  for (int i = 0; i < N_HASHTABLE; i++)
    switch (htable[i].stat) {
    case EMPTY:
      printf("-- "); break;
    case DELETE:
      printf("DD "); break;
    case USE:
      printf("%02d ", htable[i].data); break;
    default:
      printf("Error"); break;
    }
  printf("\n---\n");
}

void PrintHashTableStat() {
  printf("\nHashTableStat\n");
  for (int i = 0; i < N_HASHTABLE; i++) {
    if (htable[i].stat == EMPTY)
      printf("E");
    if (htable[i].stat == USE)
      printf("-");
    if (htable[i].stat == DELETE)
      printf("D");
  }
  printf("\n---\n");
}

int main() {
  int data, index;

  Fig2_6();
  InitHashTable();

  Algorithm2_8();
  PrintHashTable();
  PrintHashTableStat();

  InitHashTable();
    
//  HASH(Delete, N_DATA, SampleData);
//  PrintHashTable();
//  PrintHashTableStat();
  
  HASH(Insert, N_DATA, SampleData);
  PrintHashTable();
  PrintHashTableStat();

  while (1) {
    PrintHashTable();
    printf("Search  Data:");
    scanf("%d", &data);
    if ((index=SeartHashTable(data)) < 0)
      printf("Not Found\n");
    else
      printf("Found index=%d\n",index);
  }

  return 0;
}
