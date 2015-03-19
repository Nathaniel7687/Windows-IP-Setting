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

// �ܼ� ���� ����Ʈ�� ��� ���� ����
typedef struct ListNode {
    Data    data;
    struct ListNode *link;
} Node;

//����Ʈ�� ��� ����� ���� ����
typedef struct {
    Node *head;
} HeadNode;

HeadNode *createHeadNode(void); //�Լ� ���� ����
void freeHeadNode(HeadNode *);
void addLastNode(HeadNode *, Data);
void reverse(HeadNode *);
void deleteLastNode(HeadNode *);
void printList(HeadNode *);
