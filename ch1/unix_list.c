/*Standard imports*/
#include <stdio.h>
#include <stdlib.h>
/*Networking imports*/
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

/*
Program Steps:
1. Get linked list of ifaddrs structs with getifaddrs()
2. Start traversing linked list of addresses with address
3. Check adapter type with family and verify it's an INET adapter
4. Print details of adapter
5. Try to get adapter IP address in printable form
6. Point to next adapter in list
7. Free linked list
*/

int main(){
    struct ifaddrs *addresses;
    if(getifaddrs(&addresses) == -1){
        printf("[!] getifaddrs failed!\n");
        return -1;
    }
    struct ifaddrs *address = addresses;
    while(address){

        int family = address->ifa_addr->sa_family;

        if(family == AF_INET || family == AF_INET6){

            printf("%s\t", address->ifa_name);
            printf("%s\t", family == AF_INET ? "IPv4" : "IPv6");

            char ap[100];
            
            const int family_size = family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
            getnameinfo(address->ifa_addr, family_size, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
            
            printf("\t%s\n", ap);

        }

        address = address->ifa_next;

    }

    freeifaddrs(addresses);
    return 0;
}