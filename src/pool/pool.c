#include "pool.h"


char sign_of(int value) {
    if (value == 0)
        return 0;

    return (value > 0) ? 1 : -1;
}


char compare_ipv4(struct IPv4* first, struct IPv4* second) {
    // Return 1 if first is bigger than second, -1 otherwise, return 0 if equal
    char sign;
    for (char i = 0; i < 4; i++) {
        int diff = (int)first->oct[i] - second->oct[i];
        sign = sign_of(diff);

        if (sign)
            return sign;
    }

    return 0;
}

struct IPv4 create_ipv4_from_string(char* string) {
    char i = 0;
    struct IPv4 created;

    uchar oct = 0;
    char oct_num = 0;
    char sym;
    while (sym = string[i++]) {
        if (sym == '.') {
            created.oct[oct_num++] = oct;
            oct = 0;
            continue;
        }

        oct = oct * 10 + (sym - 48);
    }
    created.oct[3] = oct;

    return created;
}

struct IPRange create_ipv4_range(struct IPv4* left, struct IPv4* right) {
    struct IPRange range;

    range.left = *left;
    range.right = *right;

    return range;
}

char is_addr_in_range(struct IPv4* addr, struct IPRange* pool) {
    // return -1 if address lay on the left 1 if right 0 if the addr is in the range
    char is_after_left = compare_ipv4(addr, &pool->left);
    char is_before_right = compare_ipv4(&pool->right, addr);

    // in the range
    if (is_after_left >= 0 && is_before_right >= 0)
        return 0;
    
    // less than left value
    if (is_after_left < 0)
        return -1;

    // bigger than right value
    if (is_before_right < 0)
        return 1;
}

char compare_ranges(struct IPRange* first, struct IPRange* second) {
    return compare_ipv4(&first->left, &second->left);
}