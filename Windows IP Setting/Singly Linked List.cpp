// <단순 연결 리스트>
#pragma warning(disable: 4996)
#include "Singly Linked List.h"

//공백 연결리스트 생성 연산
HeadNode *createHeadNode(void)
{
    HeadNode *list;

    list = (HeadNode *)malloc(sizeof(HeadNode));    //헤드 노드 할당
    list->head = NULL;       //공백 리스트이므로 NULL 설정

    return list;
}

// 리스트 전체 메모리 해제 연산
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

//리스트의 마지막 노드 삽입 연산
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

// 리스트의 노드 순서를 역순으로 바꾸는 연산
void reverse(HeadNode *list)
{
    //Node *p;
    //Node *q;
    //Node *r;

    //p = list->head;
    //q = NULL;
    //r = NULL;

    //// 노드의 연결을 반대로 바꾸기
    //while(p != NULL) {
    //    r = q;
    //    q = p;
    //    p = p->link;
    //    q->link = r;
    //}

    //list->head = q;
}

// 리스트의 마지막 노드 삭제 연산
void deleteLastNode(HeadNode *list)
{
    //Node *prev;
    //Node *current;

    //// 공백 리스트인 경우, 삭제 연산 중단
    //if(list->head == NULL)
    //    return;

    //// 리스트에 노드가 한 개만 있는 경우
    //if(list->head->link == NULL) {
    //    free(list->head);  // 첫 번째 노드의 메모리를 해제
    //    list->head = NULL; // 리스트 시작 포인터를 null로 설정

    //    return;
    //}
    //else {  // 리스트에 노드가 여러 개 있는 경우
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

// 노드 순서대로 리스트를 출력하는 연산
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
