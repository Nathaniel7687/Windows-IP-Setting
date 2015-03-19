// <�ܼ� ���� ����Ʈ>
#pragma warning(disable: 4996)
#include "Singly Linked List.h"

//���� ���Ḯ��Ʈ ���� ����
HeadNode *createHeadNode(void)
{
    HeadNode *list;

    list = (HeadNode *)malloc(sizeof(HeadNode));    //��� ��� �Ҵ�
    list->head = NULL;       //���� ����Ʈ�̹Ƿ� NULL ����

    return list;
}

// ����Ʈ ��ü �޸� ���� ����
void freeHeadNode(HeadNode *list)
{
    Node *p;

    while(list->head != NULL) {
        p = list->head;
        list->head = list->head->link;
        free(p);
        p = NULL;
    }
}

//����Ʈ�� ������ ��� ���� ����
void addLastNode(HeadNode *list, Data x)
{
    Node *newNode;
    newNode = (Node *)malloc(sizeof(Node));
    
    memcpy(&newNode->data, &x, sizeof(Data));
    newNode->link = NULL;

    if(list->head == NULL)
        list->head = newNode;
    else {
        Node *prev;
        prev = list->head;

        while(prev->link != NULL)
            prev = prev->link;

        prev->link = newNode;
    }
}

// ����Ʈ�� ��� ������ �������� �ٲٴ� ����
void reverse(HeadNode *list)
{
    //Node *p;
    //Node *q;
    //Node *r;

    //p = list->head;
    //q = NULL;
    //r = NULL;

    //// ����� ������ �ݴ�� �ٲٱ�
    //while(p != NULL) {
    //    r = q;
    //    q = p;
    //    p = p->link;
    //    q->link = r;
    //}

    //list->head = q;
}

// ����Ʈ�� ������ ��� ���� ����
void deleteLastNode(HeadNode *list)
{
    //Node *prev;
    //Node *current;

    //// ���� ����Ʈ�� ���, ���� ���� �ߴ�
    //if(list->head == NULL)
    //    return;

    //// ����Ʈ�� ��尡 �� ���� �ִ� ���
    //if(list->head->link == NULL) {
    //    free(list->head);  // ù ��° ����� �޸𸮸� ����
    //    list->head = NULL; // ����Ʈ ���� �����͸� null�� ����

    //    return;
    //}
    //else {  // ����Ʈ�� ��尡 ���� �� �ִ� ���
    //    prev = list->head;
    //    current = list->head->link;

    //    while(current ->link != NULL) {
    //        prev = current;
    //        current = current->link;
    //    }

    //    free(current);
    //    prev->link = NULL;
    //}
}

// ��� ������� ����Ʈ�� ����ϴ� ����
void printList(HeadNode *list)
{
    Node* p;

    //printf("list = (");
    p = list->head;

    while(p != NULL) {
        //printf("%s", p->data);
        p = p->link;
        //if(p != NULL)
            //printf(", ");
    }

    printf(") \n");
}
