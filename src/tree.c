#include "tree.h"
#include <stdlib.h>
#include "pool/pool.h"


struct TreeNode* build_tree(struct IPRange* array, size_t nmemb) {
    if (nmemb == 0)
        return 0;

    if (nmemb == 1) {
        struct TreeNode* node = malloc(sizeof(struct TreeNode));
        
        node->key = (void*)&array[0];
        node->left = 0;
        node->right = 0;
        
        return node;
    }
    
    struct TreeNode* node = malloc(sizeof(struct TreeNode));

    size_t root_index = nmemb / 2;
    struct IPRange* root = array + root_index;
    node->key = (void*)root;

    node->left = build_tree(array, root_index);
    node->right = build_tree(array + root_index + 1, nmemb - root_index - 1);

    return node;
}

int ranges_comparator(const void* first, const void* second) {
    return (int)compare_ranges(
        (struct IPRange*)first,
        (struct IPRange*)second
    );
}

void sort_ranges(struct IPRange* range_array, size_t nmemb) {
    qsort((void*)range_array, nmemb, sizeof(struct IPRange), ranges_comparator);
}

void* find_in_tree(struct TreeNode* root, struct IPv4* ip_addr) {
    if (root != 0) {
        char is_addr_in = is_addr_in_range(ip_addr, root->key);

        if (is_addr_in == 0)
            return root->key;

        if (is_addr_in < 0)
            return find_in_tree(root->left, ip_addr);

        if (is_addr_in > 0)
            return find_in_tree(root->right, ip_addr);
    }

    return 0;
}

struct IPv4 create_random_ipv4() {
    struct IPv4 res;
    for (int i = 0; i < 4; i++) {
        res.oct[i] = rand() % 256;
    }

    return res;
}

struct IPRange create_random_range() {
    struct IPRange range;
    range.left = create_random_ipv4();
    range.right = create_random_ipv4();

    return range;
}

// int main() {
//     char* source11 = "192.168.0.28";
//     char* source12 = "192.168.1.186";
//     char* source21 = "192.168.1.193";
//     char* source22 = "192.168.4.182";
//     char* source31 = "192.168.4.6";
//     char* source32 = "192.168.5.252";
//     char* source41 = "192.168.4.68";
//     char* source42 = "192.168.12.214";

//     struct IPv4 ip11 = create_ipv4_from_string(source11);
//     struct IPv4 ip12 = create_ipv4_from_string(source12);
//     struct IPv4 ip21 = create_ipv4_from_string(source21);
//     struct IPv4 ip22 = create_ipv4_from_string(source22);
//     struct IPv4 ip31 = create_ipv4_from_string(source31);
//     struct IPv4 ip32 = create_ipv4_from_string(source32);
//     struct IPv4 ip41 = create_ipv4_from_string(source41);
//     struct IPv4 ip42 = create_ipv4_from_string(source42);

//     struct IPRange range1 = create_ipv4_range(&ip11, &ip12);
//     struct IPRange range2 = create_ipv4_range(&ip21, &ip22);
//     struct IPRange range3 = create_ipv4_range(&ip31, &ip32);
//     struct IPRange range4 = create_ipv4_range(&ip41, &ip42);

//     struct IPRange* array = malloc(4*sizeof(struct IPRange));
//     array[0] = range2;
//     array[1] = range3;
//     array[2] = range1;
//     array[3] = range4;

//     sort_ranges(array, 4);

//     struct TreeNode* root = build_tree(array, 4);
// }