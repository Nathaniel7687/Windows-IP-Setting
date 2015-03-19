#pragma warning(disable: 4996)
#pragma once
#include "IP_ADAPTER_INFO.h"

//#include "Singly Linked List.h"

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#define WORKING_BUFFER_SIZE 15000

int getAdapterInfo(HeadNode *list)
{
    /* Declare and initialize variables */

    // It is possible for an adapter to have multiple
    // IPv4 addresses, gateways, and secondary WINS servers
    // assigned to the adapter. 
    //
    // Note that this sample code only prints out the 
    // first entry for the IP address/mask, and gateway, and
    // the primary and secondary WINS server for each adapter.

    DWORD dwRetVal_Addr = 0;
    DWORD dwRetVal_Adap = 0;

    ULONG ulOutBufLen_Addr = WORKING_BUFFER_SIZE;       // Allocate a 15 KB buffer to start with.
    ULONG ulOutBufLen_Adap = sizeof (IP_ADAPTER_INFO);

    ULONG Iterations = 0;

    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;

    PIP_ADAPTER_INFO pAdapter = NULL;
    PIP_ADAPTER_INFO pCurrAdapter = NULL;

    LPVOID lpMsgBuf = NULL;

    do {
        pAddresses = (IP_ADAPTER_ADDRESSES *) MALLOC(ulOutBufLen_Addr);
        if(pAddresses == NULL) {
            printf
                ("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
            return 1;
        }

        dwRetVal_Addr = GetAdaptersAddresses(AF_INET, 0, NULL, pAddresses, &ulOutBufLen_Addr);

        if(dwRetVal_Addr == ERROR_BUFFER_OVERFLOW) {
            FREE(pAddresses);
            pAddresses = NULL;
        }
        else {
            break;
        }

        Iterations++;
    } while(dwRetVal_Addr == ERROR_BUFFER_OVERFLOW);


    pAdapter = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen_Adap);
    if (pAdapter == NULL) {
        printf("Error allocating memory needed to call GetAdaptersinfo\n");
        return 1;
    }

    if (GetAdaptersInfo(pAdapter, &ulOutBufLen_Adap) == ERROR_BUFFER_OVERFLOW) {
        FREE(pAdapter);
        pAdapter = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen_Adap);
        if (pAdapter == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return 1;
        }
    }

    if(dwRetVal_Addr == NO_ERROR) {
        // If successful, output some information from the data we received
        pCurrAddresses = pAddresses;
        while (pCurrAddresses) {
            // DNS Server 유무 판단
            if(pCurrAddresses->FirstDnsServerAddress) {
                if ((dwRetVal_Adap = GetAdaptersInfo(pAdapter, &ulOutBufLen_Adap)) == NO_ERROR) {
                    pCurrAdapter = pAdapter;

                    while(pCurrAdapter) {

                        // IP_ADAPTER_ADDRESS의 Index와 IP_ADAPTER_INFO의 Index가 동일 한 것만
                        if(pCurrAddresses->IfIndex == pCurrAdapter->Index) {
                            //printf("\tAdapter Mac: ");
                            //for (int i = 0; i < (int)pAdapter->AddressLength; i++) {
                            //    if (i == (pAdapter->AddressLength - 1))
                            //        printf("%.2X\n", (int) pAdapter->Address[i]);
                            //    else
                            //        printf("%.2X-", (int) pAdapter->Address[i]);
                            //}
                            //printf("\tType: \t");
                            //switch (pCurrAdapter->Type) {
                            //case MIB_IF_TYPE_ETHERNET:
                            //    printf("Ethernet\n");
                            //    break;
                            //}
                            //
                            //printf("\tAdapter Index: %d\n", pCurrAddresses->IfIndex);
                            //printf("\tAdapter Name: %wS\n", pCurrAddresses->FriendlyName);
                            //
                            //printf("\tIP Address: \t%s\n", pCurrAdapter->IpAddressList.IpAddress.String);
                            //printf("\tIP Mask: \t%s\n", pCurrAdapter->IpAddressList.IpMask.String);
                            //printf("\tGateway: \t%s\n", pCurrAdapter->GatewayList.IpAddress.String);
                            //
                            //if (pAdapter->DhcpEnabled)
                            //    printf("\tDHCP Enabled: Yes\n");
                            //else
                            //    printf("\tDHCP Enabled: No\n");
                            //printf("\n");
                            
                            Data data;
                            data.adapIndex = pCurrAddresses->IfIndex;
                            
                            // wchar_t to CString
                            CString temp(pCurrAddresses->FriendlyName);
                            data.adapName = temp;
                            
                            strcpy(data.ipAddress, pCurrAdapter->IpAddressList.IpAddress.String);
                            strcpy(data.ipMask, pCurrAdapter->IpAddressList.IpMask.String);
                            strcpy(data.ipGateway, pCurrAdapter->GatewayList.IpAddress.String);
                            //strcpy(data.ipDNS, pCurrAddresses->);
                            // Ref http://msdn.microsoft.com/en-us/library/aa366058(v=vs.85).aspx
                            // 6 == IF_TYPE_ETHERNET_CSMACD
                            if(pCurrAddresses->IfType == IF_TYPE_ETHERNET_CSMACD)
                                data.type = 1;
                            // 71 == IF_TYPE_IEEE80211
                            else if(pCurrAddresses->IfType == IF_TYPE_IEEE80211)
                                data.type = 2;
                            else
                                data.type = 0;

                            data.dhcp = pCurrAdapter->DhcpEnabled;

                            addLastNode(list, data);
                        }
                        pCurrAdapter = pCurrAdapter->Next;
                    }
                }
                else
                    printf("GetAdaptersInfo failed with error: %d\n", dwRetVal_Adap);
            }
            pCurrAddresses = pCurrAddresses->Next;
        }
    }
    else {
        printf("Call to GetAdaptersAddresses failed with error: %d\n", dwRetVal_Addr);
        if(dwRetVal_Addr == ERROR_NO_DATA)
            printf("\tNo addresses were found for the requested parameters\n");
        else {

            if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
                NULL, dwRetVal_Addr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),   
                //Default language
                (LPTSTR) & lpMsgBuf, 0, NULL)) {
                    // printf("\tError: %s", lpMsgBuf);
                    LocalFree(lpMsgBuf);
                    if(pAddresses)
                        FREE(pAddresses);
                    exit(1);
            }
        }
    }

    if(pAddresses)
        FREE(pAddresses);

    if (pAdapter)
        FREE(pAdapter);

    return 0;
}
