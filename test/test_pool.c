#include "unity.h"
#include "pool/pool.h"
#include "tree.h"
#include <stdlib.h>


void setup (void) {}

void teardown (void) {};

void test_creating_ipv4_from_string(void) {
    unsigned char groud_truth[4] = {192, 168, 0, 28};
    char* source = "192.168.0.28";
    struct IPv4 created = create_ipv4_from_string(source);

    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL_CHAR(groud_truth[i], created.oct[i]);
    }
}

void test_comparing_ipv4(void) {
    char* source1 = "192.168.0.28";
    char* source2 = "192.168.1.13";

    struct IPv4 ip1 = create_ipv4_from_string(source1);
    struct IPv4 ip2 = create_ipv4_from_string(source2);

    char comparing = compare_ipv4(&ip1, &ip2);
    TEST_ASSERT_EQUAL(-1, comparing);

    comparing = compare_ipv4(&ip2, &ip1);
    TEST_ASSERT_EQUAL(1, comparing);

    comparing = compare_ipv4(&ip2, &ip2);
    TEST_ASSERT_EQUAL(0, comparing);
}

void test_is_in_oper(void) {
    char* source1 = "192.168.0.28";
    char* source2 = "192.168.1.186";
    char* source_tp1 = "192.168.0.56";
    char* source_tp2 = "192.168.1.182";
    char* source_fp1 = "192.168.0.6";
    char* source_fp2 = "192.168.1.252";

    struct IPv4 ip1 = create_ipv4_from_string(source1);
    struct IPv4 ip2 = create_ipv4_from_string(source2);

    struct IPv4 ip_tp1 = create_ipv4_from_string(source_tp1);
    struct IPv4 ip_tp2 = create_ipv4_from_string(source_tp2);
    struct IPv4 ip_fp1 = create_ipv4_from_string(source_fp1);
    struct IPv4 ip_fp2 = create_ipv4_from_string(source_fp2);

    struct IPRange ip_range = create_ipv4_range(&ip1, &ip2);

    TEST_ASSERT_EQUAL(0, is_addr_in_range(&ip_tp1, &ip_range));
    TEST_ASSERT_EQUAL(0, is_addr_in_range(&ip_tp2, &ip_range));
    TEST_ASSERT_EQUAL(-1, is_addr_in_range(&ip_fp1, &ip_range));
    TEST_ASSERT_EQUAL(1, is_addr_in_range(&ip_fp2, &ip_range));
}