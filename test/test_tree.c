#include "unity.h"
#include "pool/pool.h"
#include "tree.h"
#include <stdlib.h>


void test_sorting(void) {
    char* source11 = "192.168.0.28";
    char* source12 = "192.168.1.186";
    char* source21 = "192.168.1.193";
    char* source22 = "192.168.4.182";
    char* source31 = "192.168.4.6";
    char* source32 = "192.168.5.252";

    struct IPv4 ip11 = create_ipv4_from_string(source11);
    struct IPv4 ip12 = create_ipv4_from_string(source12);
    struct IPv4 ip21 = create_ipv4_from_string(source21);
    struct IPv4 ip22 = create_ipv4_from_string(source22);
    struct IPv4 ip31 = create_ipv4_from_string(source31);
    struct IPv4 ip32 = create_ipv4_from_string(source32);

    struct IPRange range1 = create_ipv4_range(&ip11, &ip12);
    struct IPRange range2 = create_ipv4_range(&ip21, &ip22);
    struct IPRange range3 = create_ipv4_range(&ip31, &ip32);

    struct IPRange* array = malloc(3*sizeof(struct IPRange));
    array[0] = range2;
    array[1] = range3;
    array[2] = range1;

    sort_ranges(array, 3);

    TEST_ASSERT_EQUAL_CHAR_ARRAY(range1.left.oct, array[0].left.oct, 4);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(range1.right.oct, array[0].right.oct, 4);

    TEST_ASSERT_EQUAL_CHAR_ARRAY(range2.left.oct, array[1].left.oct, 4);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(range2.right.oct, array[1].right.oct, 4);

    TEST_ASSERT_EQUAL_CHAR_ARRAY(range3.left.oct, array[2].left.oct, 4);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(range3.right.oct, array[2].right.oct, 4);
}

void test_tree_building(void) {
    char* source11 = "192.168.0.28";
    char* source12 = "192.168.1.186";
    char* source21 = "192.168.1.193";
    char* source22 = "192.168.4.182";
    char* source31 = "192.168.4.6";
    char* source32 = "192.168.5.252";
    char* source41 = "192.168.4.68";
    char* source42 = "192.168.12.214";

    struct IPv4 ip11 = create_ipv4_from_string(source11);
    struct IPv4 ip12 = create_ipv4_from_string(source12);
    struct IPv4 ip21 = create_ipv4_from_string(source21);
    struct IPv4 ip22 = create_ipv4_from_string(source22);
    struct IPv4 ip31 = create_ipv4_from_string(source31);
    struct IPv4 ip32 = create_ipv4_from_string(source32);
    struct IPv4 ip41 = create_ipv4_from_string(source41);
    struct IPv4 ip42 = create_ipv4_from_string(source42);

    struct IPRange range1 = create_ipv4_range(&ip11, &ip12);
    struct IPRange range2 = create_ipv4_range(&ip21, &ip22);
    struct IPRange range3 = create_ipv4_range(&ip31, &ip32);
    struct IPRange range4 = create_ipv4_range(&ip41, &ip42);

    struct IPRange* array = malloc(4*sizeof(struct IPRange));
    array[0] = range2;
    array[1] = range3;
    array[2] = range1;
    array[3] = range4;

    sort_ranges(array, 4);

    struct TreeNode* root = build_tree(array, 4);

    TEST_ASSERT_EQUAL(0, compare_ranges(&range3, (struct IPRange*)root->key));
    TEST_ASSERT_EQUAL(0, compare_ranges(&range2, (struct IPRange*)root->left->key));
    TEST_ASSERT_EQUAL(0, compare_ranges(&range1, (struct IPRange*)root->left->left->key));
    TEST_ASSERT_EQUAL(0, compare_ranges(&range4, (struct IPRange*)root->right->key));
}

void test_search(void) {
    char* source11 = "192.168.0.28";
    char* source12 = "192.168.1.186";
    char* source21 = "192.168.1.193";
    char* source22 = "192.168.4.182";
    char* source31 = "192.168.4.6";
    char* source32 = "192.168.5.252";
    char* source41 = "192.168.4.68";
    char* source42 = "192.168.12.214";

    struct IPv4 ip11 = create_ipv4_from_string(source11);
    struct IPv4 ip12 = create_ipv4_from_string(source12);
    struct IPv4 ip21 = create_ipv4_from_string(source21);
    struct IPv4 ip22 = create_ipv4_from_string(source22);
    struct IPv4 ip31 = create_ipv4_from_string(source31);
    struct IPv4 ip32 = create_ipv4_from_string(source32);
    struct IPv4 ip41 = create_ipv4_from_string(source41);
    struct IPv4 ip42 = create_ipv4_from_string(source42);

    struct IPRange range1 = create_ipv4_range(&ip11, &ip12);
    struct IPRange range2 = create_ipv4_range(&ip21, &ip22);
    struct IPRange range3 = create_ipv4_range(&ip31, &ip32);
    struct IPRange range4 = create_ipv4_range(&ip41, &ip42);

    struct IPRange* array = malloc(4*sizeof(struct IPRange));
    array[0] = range2;
    array[1] = range3;
    array[2] = range1;
    array[3] = range4;

    sort_ranges(array, 4);

    struct TreeNode* root = build_tree(array, 4);

    char* test_source = "192.168.6.0";
    struct IPv4 test_ipv4 = create_ipv4_from_string(test_source);
    struct IPRange* res = find_in_tree(root, &test_ipv4);

    TEST_ASSERT_EQUAL(0, compare_ipv4(&range4.left, &res->left));
    TEST_ASSERT_EQUAL(0, compare_ipv4(&range4.right, &res->right));
}