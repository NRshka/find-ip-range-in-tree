#ifndef _TREE_H_
#include <stddef.h>
#include "pool/pool.h"

struct TreeNode {
    void* key;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
};

void sort_ranges(struct IPRange* range_array, size_t nmemb);
void* find_in_tree(struct TreeNode* root, struct IPv4* ip_addr);
struct TreeNode* build_tree(struct IPRange* array, size_t nmemb);
void* find_in_tree(struct TreeNode* root, struct IPv4* ip_addr);

#endif