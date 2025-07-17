//
// Created by Administrator on 17/07/2025.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Project {
    int id;
    char title[100];
    char owner[100];
    int priority;
}Project;

typedef struct SingleNode {
    Project project;
    struct SingleNode *next;
}SingleNode;

typedef struct DoubleNode {
    Project project;
    struct DoubleNode *next;
    struct DoubleNode *prev;
}DoubleNode;

SingleNode *finishProjectNode = NULL;

SingleNode *createSingleNode(Project project) {
    SingleNode *node = (SingleNode *)malloc(sizeof(SingleNode));
    node->project = project;
    node->next = NULL;
    return node;
}

SingleNode *insertSingleNode(SingleNode *head, Project project) {
    SingleNode *newNode = createSingleNode(project);
    if (head==NULL) {
        return newNode;
    }
    SingleNode *temp = head;
    while (temp->next!=NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

void displaySingleList(SingleNode *head) {
    printf("DOING PROJECT\n");
    if (head == NULL) {
        printf("Danh sach trong.\n");
        return;
    }
    SingleNode *temp = head;
    while (temp != NULL) {
        printf("ID: %d\n",temp->project.id);
        printf("Ten du an: %s\n",temp->project.title);
        printf("Nguoi quan ly: %s\n",temp->project.owner);
        printf("Do uu tien: %d\n",temp->project.priority);
        printf("----------------------------------\n");
        temp = temp->next;
    }
}

SingleNode *deleteProject(SingleNode *head,int id) {
    if (head ==NULL) {
        printf("Danh sach trong\n");
        return head;
    }
    SingleNode *temp = head;
    SingleNode *prev =NULL;
    while (temp != NULL && temp->project.id !=id) {
        prev =temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay du an co ID = %d\n",id);
        return head;
    }
    if (temp ==head) {
        head = head->next;
    }else {
        prev->next=temp->next;
    }
    finishProjectNode=temp;
    return head;
}

void updateProject(SingleNode *head,int id) {
    if (head == NULL) {
        printf("Danh sach trong\n");
        return;
    }
    SingleNode *temp = head;
    while (temp != NULL && temp->project.id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay du an co ID = %d\n",id);
        return;
    }
    printf("ID: %d\n",temp->project.id);
    printf("Ten du an: %s\n",temp->project.title);
    printf("Nguoi quan ly: %s\n",temp->project.owner);
    printf("Do uu tien: %d\n",temp->project.priority);

    fflush(stdin);
    printf("Nhap ten du an: ");
    gets(temp->project.title);
    printf("Nhap nguoi quan ly: ");
    gets(temp->project.owner);
    printf("Nhap do uu tien: ");
    scanf("%d",&temp->project.priority);
    printf("Cap nhat thanh cong\n");
}

DoubleNode *createDoubleNode(Project project) {
    DoubleNode *node = (DoubleNode *)malloc(sizeof(DoubleNode));
    node->project = project;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

DoubleNode *insertDoubleNode(DoubleNode *head, Project project) {
    DoubleNode *newNode = createDoubleNode(project);
    if (head==NULL) {
        return newNode;
    }
    DoubleNode *temp=head;
    while (temp->next!=NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev=temp;
    return head;
}

void displayDoubleList(DoubleNode *head) {
    printf("DONE PROJECT\n");
    if (head ==NULL) {
        printf("Danh sach hoan thanh rong\n");
        return;
    }
    while (head!=NULL) {
        printf("ID: %d\n",head->project.id);
        printf("Ten du an: %s\n",head->project.title);
        printf("Nguoi quan ly: %s\n",head->project.owner);
        printf("Do uu tien: %d\n",head->project.priority);
        head = head->next;
    }
}

void displayAllProject(SingleNode *doingList,DoubleNode *doneList) {
    displaySingleList(doingList);
    displayDoubleList(doneList);
}

SingleNode *sortProject(SingleNode *head) {
    if (head==NULL || head->next==NULL) {
        return head;
    }
    for (SingleNode *i = head; i != NULL; i=i->next ) {
        for (SingleNode *j =i->next; j != NULL; j=j->next) {
            if (i->project.priority > j->project.priority) {
                Project temp = i->project;
                i->project = j->project;
                j->project = temp;
            }
        }
    }
    return head;
}

void searchProject(SingleNode *head, char *keyword) {
    SingleNode *temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strstr(temp->project.title, keyword)) {
            printf("ID: %d\n",temp->project.id);
            printf("Ten du an: %s\n",temp->project.title);
            printf("Nguoi quan ly: %s\n",temp->project.owner);
            printf("Do uu tien: %d\n",temp->project.priority);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Khong tim thay\n");
    }
}

int main() {
    int choice;
    SingleNode *doingList = NULL;
    DoubleNode *doneList = NULL;
    do {
        printf("\n1. Them moi du an\n");
        printf("2. Hien thi danh sach du an ca nhan\n");
        printf("3. Xoa du an\n");
        printf("4. Cap nhat thong tin du an\n");
        printf("5. Danh dau du an da hoan thanh\n");
        printf("6. Sap xep du an theo do uu tien\n");
        printf("7. Tim kiem du an theo ten\n");
        printf("8. Thoat chuong trinh\n");
        printf("nhap lua chon cua ban: ");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                Project p;
                printf("Nhap ID: ");
                scanf("%d",&p.id);
                fflush(stdin);
                printf("Nhap ten du an: ");
                gets(p.title);
                printf("Nhap ten nguoi quan ly du an: ");
                gets(p.owner);
                printf("Nhap muc do uu tien: ");
                scanf("%d",&p.priority);
                doingList = insertSingleNode(doingList,p);
                break;
            case 2:
                displaySingleList(doingList);
                break;
            case 3:
                int id;
                printf("Nhap ID can xoa: ");
                scanf("%d",&id);
                doingList = deleteProject(doingList,id);
                if (finishProjectNode != NULL) {
                    printf("Xoa thanh cong\n");
                    free(finishProjectNode);
                    finishProjectNode = NULL;
                }
                break;
            case 4:
                int updateID;
                printf("Nhap ID can cap nhat: ");
                scanf("%d",&updateID);
                updateProject(doingList,updateID);
                break;
            case 5:
                int index;
                printf("nhap id du an: ");
                scanf("%d",&index);
                doingList = deleteProject(doingList,index);
                if (finishProjectNode != NULL) {
                    doneList = insertDoubleNode(doneList,finishProjectNode->project);
                    free(finishProjectNode);
                    finishProjectNode = NULL;
                }
                break;
            case 6:
                doingList = sortProject(doingList);
                printf("Da sap xep theo do uu tien\n");
                break;
            case 7:
                char keyword[50];
                fflush(stdin);
                printf("nhap ten du an: ");
                gets(keyword);
                searchProject(doingList,keyword);
                break;
            case 8:
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
    }while (choice != 8);
    return 0;
}
