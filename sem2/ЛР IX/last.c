#include <stdio.h>
#include "table.h"

void displayMenu() {
    printf("\nВыберите действие:\n");
    printf("1. Создать таблицу\n");
    printf("2. Сортировка\n");
    printf("3. Бинарный поиск по ключу\n");
    printf("4. Распечатать таблицу\n");
    printf("5. Реверс таблицы\n");
    printf("6. Перемешать таблицу\n");
    printf("0. Выйти\n");
}

int main() {
    KeyArray keys;
    ValueArray values;
    createKeyArray(&keys);
    createValueArray(&values);
    int choice;
    float key;
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                char filename[STRSIZE];
                printf("Введите имя файла для загрузки данных: ");
                scanf("%s", filename);
                loadTableFromFile(&keys, &values, filename);
                break;
            }
            case 2: {
                printf("\nИсходная таблица:\n");
                printTable(&keys, &values);
                heapSort(&keys);
                printf("\nТаблица после сортировки (HeapSort):\n");
                printTable(&keys, &values);
                break;
            }
            case 3: {
                printf("Введите ключ для поиска: ");
                scanf("%f", &key);
                heapSort(&keys);
                int idx = binarySearch(&keys, key);
                if (idx != -1) {
                    printf("Найдено: %s\n", values.data[keys.entries[idx].index]);
                } else {
                    printf("Ключ не найден.\n");
                }
                break;
            }
            case 4: {
                printTable(&keys, &values);
                break;
            }
            case 5: {
                reverseTable(&keys);
                printf("\nТаблица после реверса:\n");
                printTable(&keys, &values);
                break;
            }
            case 6: {
                shuffleTable(&keys);
                printf("\nТаблица после перемешивания:\n");
                printTable(&keys, &values);
                break;
            }
            case 0:
                return 0;
            default:
                printf("Неверный выбор.\n");
                break;
        }
    }
}