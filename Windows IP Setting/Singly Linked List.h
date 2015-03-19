#pragma once
#include <iostream>
#include <atlstr.h>
using namespace std;

typedef wchar_t WCHAR, *PWCHAR;

typedef struct listData {
    unsigned long    adapIndex;
    CString     adapName;
    char        ipAddress[4 * 4];
    char        ipMask[4 * 4];
    char        ipGateway[4 * 4];
    char        ipDNS[4 * 4];
    int         type;
    int         dhcp;
} Data;

// 단순 연결 리스트의 노드 구조 정의
typedef struct ListNode {
    Data    data;
    struct ListNode *link;
} Node;

//리스트의 헤드 노드의 구조 정의
typedef struct {
    Node *head;
} HeadNode;

HeadNode *createHeadNode(void); //함수 원형 선언
void freeHeadNode(HeadNode *);
void addLastNode(HeadNode *, Data);
void reverse(HeadNode *);
void deleteLastNode(HeadNode *);
void printList(HeadNode *);
