#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "table.h"

void createKeyArray(KeyArray* arr) {
    arr->size = 0;
}

void createValueArray(ValueArray* arr) {
    arr->size = 0;
}

void trim(char* str) {
    char* start = str;
    while (*start == ' ' || *start == '\t') {
        start++;
    }
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n')) {
        str[--len] = '\0';
    }
}

void loadTableFromFile(KeyArray* keys, ValueArray* values, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка при открытии файла.\n");
        return;
    }
    keys->size = 0;
    values->size = 0;
    float key;
    char str[STRSIZE * 2];
    while (fscanf(file, "%f %[^\n]\n", &key, str) == 2) {
        if (keys->size >= MAXSIZE) {
            printf("Достигнут лимит таблицы (%d элементов)\n", MAXSIZE);
            break;
        }
        trim(str);
        keys->entries[keys->size].key = key;
        keys->entries[keys->size].index = values->size;
        strncpy(values->data[values->size], str, STRSIZE - 1);
        values->data[values->size][STRSIZE - 1] = '\0';
        keys->size++;
        values->size++;
    }
    fclose(file);
}

void printTable(KeyArray* keys, ValueArray* values) {
    printf("+--------+---------------------------------------------+\n");
    printf("|  Ключ  | Значение                                    |\n");
    printf("+--------+---------------------------------------------+\n");
    for (int i = 0; i < keys->size; i++) {
        printf("| %6.2f | %-45s |\n", keys->entries[i].key, values->data[keys->entries[i].index]);
    }
    printf("+--------+---------------------------------------------+\n");
}

void heapify(KeyArray* keys, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && keys->entries[left].key > keys->entries[largest].key) {
        largest = left;
    }
    if (right < n && keys->entries[right].key > keys->entries[largest].key) {
        largest = right;
    }
    if (largest != i) {
        KeyEntry temp = keys->entries[i];
        keys->entries[i] = keys->entries[largest];
        keys->entries[largest] = temp;
        heapify(keys, n, largest);
    }
}

void heapSort(KeyArray* keys) {
    int n = keys->size;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(keys, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        KeyEntry temp = keys->entries[0];
        keys->entries[0] = keys->entries[i];
        keys->entries[i] = temp;
        heapify(keys, i, 0);
    }
}

int binarySearch(KeyArray* keys, float key) {
    int left = 0;
    int right = keys->size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (keys->entries[mid].key < key) {
            left = mid + 1;
        } else if (keys->entries[mid].key > key) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

void reverseTable(KeyArray* keys) {
    int n = keys->size;
    for (int i = 0; i < n / 2; i++) {
        KeyEntry temp = keys->entries[i];
        keys->entries[i] = keys->entries[n - i - 1];
        keys->entries[n - i - 1] = temp;
    }
}

void shuffleTable(KeyArray* keys) {
    int n = keys->size;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        KeyEntry temp = keys->entries[i];
        keys->entries[i] = keys->entries[j];
        keys->entries[j] = temp;
    }
}
