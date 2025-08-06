#ifndef TABLE_H
#define TABLE_H
#define MAXSIZE 100
#define STRSIZE 100

typedef struct {
    float key;
    int index;
} KeyEntry;

typedef struct {
    int size;
    KeyEntry entries[MAXSIZE];
} KeyArray;

typedef struct {
    int size;
    char data[MAXSIZE][STRSIZE];
} ValueArray;

void createKeyArray(KeyArray* arr);
void createValueArray(ValueArray* arr);
void loadTableFromFile(KeyArray* keys, ValueArray* values, const char* filename);
void printTable(KeyArray* keys, ValueArray* values);
void heapify(KeyArray* keys, int n, int i);
void heapSort(KeyArray* keys);
int binarySearch(KeyArray* keys, float key);
void reverseTable(KeyArray* keys);
void shuffleTable(KeyArray* keys);

#endif
