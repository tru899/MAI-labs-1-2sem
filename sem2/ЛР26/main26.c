#include "deck.h"

void mergeSort(StaticDeck *D) {
    if (size(D) <= 1) return;

    StaticDeck left, right;
    initDeck(&left);
    initDeck(&right);
    
    for (int i = 0; i < (size(D) / 2); i++) {
        pushBack(&left, frontKey(D), topFront(D));
        popFront(D);
    }
    while (!empty(D)) {
        pushBack(&right, frontKey(D), topFront(D));
        popFront(D);
    }

    mergeSort(&left);
    mergeSort(&right);

    initDeck(D);
    while (!empty(&left) && !empty(&right)) {
        if (frontKey(&left) <= frontKey(&right)) {
            pushBack(D, frontKey(&left), topFront(&left));
            popFront(&left);
        } else {
            pushBack(D, frontKey(&right), topFront(&right));
            popFront(&right);
        }
    }
    while (!empty(&left)) {
        pushBack(D, frontKey(&left), topFront(&left));
        popFront(&left);
    }
    while (!empty(&right)) {
        pushBack(D, frontKey(&right), topFront(&right));
        popFront(&right);
    }
}

void menu() {
    printf("\n");
    printf("1. Добавить в начало ");
    printf("2. Добавить в конец ");
    printf("3. Удалить из начала ");
    printf("4. Удалить с конца ");
    printf("5. Очистить дек ");
    printf("6. Отсортировать по ключу ");
    printf("7. Показать дек ");
    printf("8. Показать размер дека ");
    printf("0. Выход\n");
    printf("Выбор: ");
}

int main() {
    StaticDeck d;
    initDeck(&d);

    int choice;
    key_type key;
    value_type value;

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите ключ и значение: ");
                scanf("%d %d", &key, &value);
                pushFront(&d, key, value);
                break;
            case 2:
                printf("Введите ключ и значение: ");
                scanf("%d %d", &key, &value);
                pushBack(&d, key, value);
                break;
            case 3:
                printf("Удалено из начала: %d\n", popFront(&d));
                break;
            case 4:
                printf("Удалено с конца: %d\n", popBack(&d));
                break;
            case 5:
                clearDeck(&d);
                printf("Дек очищен\n");
                break;
            case 6:
                mergeSort(&d);
                printf("Дек отсортирован\n");
                printDeck(&d);
                break;
            case 7:
                printDeck(&d);
                break;
            case 8:
                printf("Размер дека: %d\n", size(&d));
                break;
            case 0:
                printf("Выход\n");
                break;
            default:
                printf("Неверный выбор\n");
        }

    } while (choice != 0);

    return 0;
}
