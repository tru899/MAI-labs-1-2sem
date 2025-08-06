#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    float data;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* tree_create_el(float value) {
    Tree* elem = (Tree*)(malloc(sizeof(Tree)));
    elem->data = value;
    elem->left = NULL;
    elem->right = NULL;
    return elem;
}

Tree* tree_add_root(Tree* root, float value) {
    if (root == NULL) {
        return tree_create_el(value);
    }
    return root;
}

void tree_insert_el(Tree* root, Tree* elem) {
    if (elem->data < root->data) {
        if (root->left == NULL) {
            root->left = elem;
        } else {
            tree_insert_el(root->left, elem);
        }
    } else {
        if (root->right == NULL) {
            root->right = elem;
        } else {
        tree_insert_el(root->right, elem);
        }
    }
}

void tree_print(Tree* root, int tabs) {
    if (root == NULL) {
        return;
    }
    tree_print(root->right, tabs+1);

    for (int i = 0; i < tabs; i++) {
        printf("\t");
    }
    printf("%.2f\n", root->data);
    tree_print(root->left, tabs+1);
    }

Tree* find_min(Tree* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Tree* tree_delete_el(Tree* root, float value) {
    if (root == NULL) {
        return NULL;
    }
    
    if (value < root->data) {
        root->left = tree_delete_el(root->left, value);
    }
    else if (value > root->data) {
        root->right = tree_delete_el(root->right, value);
    }
    else {
        if (root->left == NULL) {
            Tree* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Tree* temp = root->left;
            free(root);
            return temp;
        }
        else {
            Tree* temp = find_min(root->right);
            root->data = temp->data;
            root->right = tree_delete_el(root->right, temp->data);
        }
    }
    return root;
}

int tree_degree(Tree* root) {
    if (root == NULL) {
        return 0;
    }

    int degree = 0;
    if (root->left != NULL) {
        degree++;
    }
    if (root->right != NULL) {
        degree++;
    }

    int left_degree = tree_degree(root->left);
    int right_degree = tree_degree(root->right);

    int max_subtree_degree = 0;
    if (left_degree > right_degree) {
        max_subtree_degree = left_degree;
    } else {
        max_subtree_degree = right_degree;
    }

    if (max_subtree_degree > degree) {
        degree = max_subtree_degree;
        return degree;
    } else {
        return degree;
    }
}

int tree_find(Tree* root, float value) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == value) {
        return 1;
    }
    if (value < root->data) {
        return tree_find(root->left, value);
    } else {
        return tree_find(root->right, value);
    }
}

void menu() {
    printf("Выберите действие\n");
    printf("1. Добавить новый узел\n");
    printf("2. Вывод дерева\n");
    printf("3. Удаление узла\n");
    printf("4. Определить степень двоичного дерева\n");
    printf("5. Выход\n");
    printf("\n");
}

int main() {
    Tree* elem = NULL;
    float value;
    int mode = -1;

    while(mode) {
        menu();
        value = 0;
        scanf("%d", &mode);

        switch (mode) {
            case 1:
                printf("Введите значение: ");
                scanf("%f", &value);
                if (elem == NULL) {
                    elem = tree_add_root(elem, value);
                } else {
                    tree_insert_el(elem, tree_create_el(value));
                }
                break;

            case 2:
                printf("Дерево:\n");
                printf("\n");
                tree_print(elem, 0);
                break;

            case 3:
                printf("Введите значение: ");
                scanf("%f", &value);

                if (!tree_find(elem, value)) {
                    printf("Узел с таким значением не найден\n");
                } else {
                    elem = tree_delete_el(elem, value);
                    printf("Узел %.2f удалён\n", value);
                }
                break;

            case 4:
                printf("Степень дерева = %d\n", tree_degree(elem));
                break;

            case 5:
                printf("Вы вышли из программы\n");
                mode = 0;
                break;

            default:
                printf("error\n");
                break;
        }
        printf("\n");
    }
}
