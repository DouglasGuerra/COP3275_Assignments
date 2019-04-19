#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define NUM_BYTES_IN_IP_ADDRESS 4
#define NUM_BITS 32
#define NUM_IP_ADDRESS 2

typedef struct{
    uint8_t bytes[NUM_BYTES_IN_IP_ADDRESS];
    uint32_t binary;
} IpAddress_t;

void ConcatIpAddressBytes(IpAddress_t *ipAddress){
    int i;
    ipAddress->binary = 0;
    for(i = 0; i < NUM_BYTES_IN_IP_ADDRESS; i++){
        ipAddress->binary = ipAddress->binary << 8;
        ipAddress->binary |= ipAddress->bytes[i];
    }
}

uint32_t CreatSubnetAddress(int numOfNonZeroBits){
    uint32_t subnetMask = 0;
    int i;
    for(i = 0; i < NUM_BITS; i++){
        subnetMask = subnetMask << 1;
        if(i < numOfNonZeroBits) subnetMask |= 1;
    }
    return subnetMask;
}

bool IsSameSubnet(uint32_t firstIpAddress, uint32_t secondIpAddress, uint32_t subnetMask){
    firstIpAddress = firstIpAddress & subnetMask;
    secondIpAddress = secondIpAddress & subnetMask;
    // printf("%x, %x\n", firstIpAddress, secondIpAddress);

    return ((firstIpAddress == secondIpAddress) ? true : false);
}

void LoadIpAddressFromUser(IpAddress_t *ipAddress){
    scanf("%d.%d.%d.%d",&ipAddress->bytes[0], &ipAddress->bytes[1], &ipAddress->bytes[2], &ipAddress->bytes[3]);
}

int main(){

    int numNonZeroSubnetBits;
    IpAddress_t ipAddress[NUM_IP_ADDRESS];
    LoadIpAddressFromUser(&ipAddress[0]);
    LoadIpAddressFromUser(&ipAddress[1]);
    scanf(" %d", &numNonZeroSubnetBits);

    ConcatIpAddressBytes(&ipAddress[0]);
    ConcatIpAddressBytes(&ipAddress[1]);
    uint32_t subnetMask = CreatSubnetAddress(numNonZeroSubnetBits);

    // printf("%x, %x, %x\n", ipAddress[0].binary, ipAddress[1].binary, subnetMask);

    printf("%d\n", IsSameSubnet(ipAddress[0].binary, ipAddress[1].binary, subnetMask));

    return 0;
}
