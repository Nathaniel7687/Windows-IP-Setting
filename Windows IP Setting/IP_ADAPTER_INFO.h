#pragma once
#include <iostream>
#include <winsock2.h>
#include <iphlpapi.h>
#include "Singly Linked List.h"
using namespace std;

#pragma comment(lib, "IPHLPAPI.lib")    // GetAdapterAddress

int getAdapterInfo(HeadNode *);
