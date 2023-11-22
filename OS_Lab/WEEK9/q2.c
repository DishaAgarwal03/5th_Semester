#include <stdio.h>

// Define the segment structure
struct Segment {
    int segment_number;
    int start_address;
    int end_address;
};

// Create a segment table
struct Segment segment_table[5] = {
    {0, 1400, 2400},
    {1, 6300, 6700},
    {2, 4300, 4700},
    {3, 3200, 4300},
    {4, 4700, 5700}
};

// Function to convert logical address to physical address
int logicalToPhysical(int segment_number, int logical_address) {
    if (segment_number < 0 || segment_number >= 5) {
        printf("Segment number is out of range.\n");
        return -1;
    }

    if (logical_address < 0 || logical_address > (segment_table[segment_number].end_address - segment_table[segment_number].start_address)) {
        printf("Logical address is out of range for the segment.\n");
        return -1;
    }

    return segment_table[segment_number].start_address + logical_address;
}

int main() {
    int logical_address;

    // (i) 53 bytes of segment 2
    logical_address = 53;
    int physical_address_i = logicalToPhysical(2, logical_address);
    printf("(i) Logical address %d of segment 2 maps to physical address %d.\n", logical_address, physical_address_i);

    // (ii) 852 bytes of segment 3
    logical_address = 852;
    int physical_address_ii = logicalToPhysical(3, logical_address);
    printf("(ii) Logical address %d of segment 3 maps to physical address %d.\n", logical_address, physical_address_ii);

    // (iii) 1222 bytes of segment 0
    logical_address = 1222;
    int physical_address_iii = logicalToPhysical(0, logical_address);
    printf("(iii) Logical address %d of segment 0 maps to physical address %d.\n", logical_address, physical_address_iii);

    return 0;
}
