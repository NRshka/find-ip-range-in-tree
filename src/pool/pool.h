#ifndef _POOL_H_
#define _POOL_H_

#define uchar unsigned char


struct IPv4 {
    uchar oct[4];
};

struct IPRange {
    struct IPv4 left;
    struct IPv4 right;
};


char compare_ipv4(struct IPv4* first, struct IPv4* second);
char compare_ranges(struct IPRange* first, struct IPRange* second);
struct IPv4 create_ipv4_from_string(char* string);
struct IPRange create_ipv4_range(struct IPv4* left, struct IPv4* right);
char is_addr_in_range(struct IPv4* addr, struct IPRange* pool);

#endif