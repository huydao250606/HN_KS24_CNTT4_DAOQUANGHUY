//
// Created by Administrator on 17/07/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct Node {
    char text[MAX_LEN];
    struct Node *next;
}Node;

typedef struct Stack {
    Node *top;
}Stack;

Stack clipboardStack={NULL};
Stack redoStack={NULL};

void push(Stack*s,const char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->text, str);
    newNode->next = s->top;
    s->top = newNode;
}
char* pop(Stack*s) {
    if (s->top==NULL) {
        return NULL;
    }
    Node *temp = s->top;
    s->top = temp->next;
    char* result = strdup(temp->text);
    free(temp);
    return result;
}

void clearStack(Stack*s) {
    while (s->top!=NULL) {
        Node* temp = s->top;
        s->top = temp->next;
        free(temp);
    }
}
void copyText() {
    char text[MAX_LEN];
    printf("nhap noi dung can copy: ");
    scanf("%s", text);
    push(&clipboardStack,text);
    clearStack(&clipboardStack);
    printf("Copy thanh cong\n");
}

Void pasteText() {
    if (!clipboardStack.top) {
        printf("clipboard rong\n");
        return;
    }
    printf("Noi dung paste: ");
}

void undo() {
    if (!clipboardStack) {
        printf("clipboard rong\n");
        return;
    }
    char* undone = pop(&clipboardStack);
    push(&redoStack,undone);
    free(undone);
    printf("hoan tac thanh cong");
}
void redo() {
    if (!redoStack) {
        printf("khong co noi dung\n");
        return;
    }
    char* redone = pop(&redoStack);
    push(&clipboardStack,redone);
    free(redone);
    printf("phuc hoi thanh cong");
}
void showClipboard() {
    Node* temp = clipboardStack.top;
    if (!temp) {
        printf("clipboard rong\n");
        return;
    }
    while (temp) {
        printf("%s\n", temp->text);
        temp = temp->next;
    }
}
int main() {
    int choice;
    do {
        printf("1. COPY\n");
        printf("2. PASTE\n");
        printf("3. UNDO\n");
        printf("4. REDO\n");
        printf("5. HIEN THI CLIPBOARD\n");
        printf("6. THOAT\n");
        printf("chon chuc nang: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                copyText();
                break;
            case 2:
                pasteText();
                break;
            case 3:
                undo();
                break;
            case 4:
                redo();
                break;
            case 5:
                showClipboard();
                break;
            case 6:
                printf("thoat chuong trinh\n");
                break;
            default:
                printf("lua chon khong hop le\n");
        }
    }while(choice != 6);
    return 0;
}