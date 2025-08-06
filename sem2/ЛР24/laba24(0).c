#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { node_number, node_operator, node_variable } NodeType;

typedef struct TreeNode {
    NodeType type;
    union {
        double number;
        char op;
        char variable;
    } data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode **data;
    int top;
    int capacity;
} Stack;

Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->data = malloc(capacity * sizeof(TreeNode *));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int isEmpty(Stack *stack) { return stack->top == -1; }

void push(Stack *stack, TreeNode *node) {
    if (stack->top == stack->capacity - 1) {
        printf("Переполнение стека\n");
        exit(1);
    }
    stack->data[++stack->top] = node;
}

TreeNode *pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Переполнение стека\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

TreeNode *peek(Stack *stack) {
    return isEmpty(stack) ? NULL : stack->data[stack->top];
}

TreeNode *createNumberNode(double value) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->type = node_number;
    node->data.number = value;
    node->left = node->right = NULL;
    return node;
}

TreeNode *createOperatorNode(char op) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->type = node_operator;
    node->data.op = op;
    node->left = node->right = NULL;
    return node;
}

TreeNode *createVariableNode(char var) {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->type = node_variable;
    node->data.variable = var;
    node->left = node->right = NULL;
    return node;
}

int getPriority(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

TreeNode *buildExpressionTree(const char *expression) {
    Stack *values = createStack(strlen(expression));
    Stack *operators = createStack(strlen(expression));

    for (int i = 0; expression[i]; i++) {
        if (expression[i] == ' ') continue;

        if (expression[i] == '(') {
            push(operators, createOperatorNode(expression[i]));
        } else if (expression[i] == ')') {
            while (!isEmpty(operators) && peek(operators)->data.op != '(') {
                TreeNode *opNode = pop(operators);
                opNode->right = pop(values);
                opNode->left = pop(values);
                push(values, opNode);
            }
            pop(operators);
        } else if (isdigit(expression[i]) || expression[i] == '.') {
            double num = 0;
            int dot = 0;
            double fraction = 1.0;
            while (expression[i] && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') dot = 1;
                else {
                    if (dot) {
                        fraction *= 0.1;
                        num += (expression[i] - '0') * fraction;
                    } else {
                        num = num * 10 + (expression[i] - '0');
                    }
                }
                i++;
            }
            i--;
            push(values, createNumberNode(num));
        } else if (isalpha(expression[i])) {
            push(values, createVariableNode(expression[i]));
        } else {
            TreeNode *opNode = createOperatorNode(expression[i]);
            while (!isEmpty(operators) && getPriority(peek(operators)->data.op) >= getPriority(expression[i])) {
                TreeNode *topOp = pop(operators);
                topOp->right = pop(values);
                topOp->left = pop(values);
                push(values, topOp);
            }
            push(operators, opNode);
        }
    }

    while (!isEmpty(operators)) {
        TreeNode *opNode = pop(operators);
        opNode->right = pop(values);
        opNode->left = pop(values);
        push(values, opNode);
    }

    TreeNode *result = pop(values);
    free(values->data); free(values);
    free(operators->data); free(operators);
    return result;
}

bool needParenthesesLeft(TreeNode *parent, TreeNode *child) {
    return child && child->type == node_operator &&
           getPriority(parent->data.op) > getPriority(child->data.op);
}

bool needParenthesesRight(TreeNode *parent, TreeNode *child) {
    if (!child || child->type != node_operator) return false;
    int parentP = getPriority(parent->data.op);
    int childP = getPriority(child->data.op);
    return parentP > childP || (parentP == childP && (parent->data.op == '-' || parent->data.op == '/'));
}

void printInfix(TreeNode *root) {
    if (!root) return;

    if (root->left && needParenthesesLeft(root, root->left)) {
        printf("(");
        printInfix(root->left);
        printf(")");
    } else if (root->left) {
        printInfix(root->left);
    }

    switch (root->type) {
        case node_number:
            if (root->data.number == (int)root->data.number)
                printf("%d", (int)root->data.number);
            else
                printf("%g", root->data.number);
            break;
        case node_operator:
            printf("%c", root->data.op);
            break;
        case node_variable:
            printf("%c", root->data.variable);
            break;
    }

    if (root->right && needParenthesesRight(root, root->right)) {
        printf("(");
        printInfix(root->right);
        printf(")");
    } else if (root->right) {
        printInfix(root->right);
    }
}

void printTree(TreeNode *root, int level) {
    if (!root) return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("    ");
    switch (root->type) {
        case node_number:
            if (root->data.number == (int)root->data.number)
                printf("%d\n", (int)root->data.number);
            else
                printf("%g\n", root->data.number);
            break;
        case node_operator: printf("%c\n", root->data.op); break;
        case node_variable: printf("%c\n", root->data.variable); break;
    }
    printTree(root->left, level + 1);
}

void freeTree(TreeNode *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

TreeNode *copyTree(TreeNode *root) {
    if (!root) return NULL;
    TreeNode *node = malloc(sizeof(TreeNode));
    node->type = root->type;
    node->data = root->data;
    node->left = copyTree(root->left);
    node->right = copyTree(root->right);
    return node;
}

TreeNode *applyDistributiveInternal(TreeNode *node) {
    if (!node) return NULL;
    node->left = applyDistributiveInternal(node->left);
    node->right = applyDistributiveInternal(node->right);

    if (node->type == node_operator && node->data.op == '*') {
        TreeNode *left = node->left;
        TreeNode *right = node->right;

        if (left && (left->type == node_variable || left->type == node_number) &&
            right && right->type == node_operator &&
            (right->data.op == '+' || right->data.op == '-')) {

            TreeNode *newLeft = createOperatorNode('*');
            newLeft->left = copyTree(left);
            newLeft->right = copyTree(right->left);

            TreeNode *newRight = createOperatorNode('*');
            newRight->left = copyTree(left);
            newRight->right = copyTree(right->right);

            TreeNode *newRoot = createOperatorNode(right->data.op);
            newRoot->left = newLeft;
            newRoot->right = newRight;

            TreeNode *result = applyDistributiveInternal(newRoot);
            freeTree(node);
            return result;
        }

        if (right && (right->type == node_variable || right->type == node_number) &&
            left && left->type == node_operator &&
            (left->data.op == '+' || left->data.op == '-')) {

            TreeNode *newLeft = createOperatorNode('*');
            newLeft->left = copyTree(left->left);
            newLeft->right = copyTree(right);

            TreeNode *newRight = createOperatorNode('*');
            newRight->left = copyTree(left->right);
            newRight->right = copyTree(right);

            TreeNode *newRoot = createOperatorNode(left->data.op);
            newRoot->left = newLeft;
            newRoot->right = newRight;

            TreeNode *result = applyDistributiveInternal(newRoot);
            freeTree(node);
            return result;
        }
    }

    return node;
}

TreeNode *applyDistributive(TreeNode *node) {
    return applyDistributiveInternal(copyTree(node));
}

void printMenu() {
    printf("\nМеню:\n1. Ввести выражение\n2. Вывести выражение\n3. Упростить выражение\n4. Выход\nВыберите пункт: ");
}

int main() {
    char expression[256] = "";
    TreeNode *root = NULL, *simplifiedRoot = NULL;
    int choice;
    bool hasExpression = false;

    do {
        printMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Введите арифметическое выражение: ");
                fgets(expression, sizeof(expression), stdin);
                expression[strcspn(expression, "\n")] = '\0';

                freeTree(root); root = NULL;
                freeTree(simplifiedRoot); simplifiedRoot = NULL;

                root = buildExpressionTree(expression);
                hasExpression = true;
                printf("Выражение сохранено.\n");
                break;

            case 2:
                if (!hasExpression) {
                    printf("Сначала введите выражение (пункт 1).\n");
                    break;
                }
                printf("\nТекстовое представление: ");
                printInfix(root);
                printf("\n\nДерево выражения:\n");
                printTree(root, 0);
                break;

            case 3:
                if (!hasExpression) {
                    printf("Сначала введите выражение (пункт 1).\n");
                    break;
                }
                freeTree(simplifiedRoot);
                simplifiedRoot = applyDistributive(root);
                printf("\nУпрощенное выражение (текст): ");
                printInfix(simplifiedRoot);
                printf("\n\nУпрощенное дерево выражения:\n");
                printTree(simplifiedRoot, 0);
                break;

            case 4:
                printf("Выход из программы.\n");
                break;

            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 4);

    freeTree(root);
    freeTree(simplifiedRoot);
    return 0;
}
