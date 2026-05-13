/* Unity Test Framework - Minimal version for embedded CI/CD demo
 * Full framework: https://github.com/ThrowTheSwitch/Unity
 */
#ifndef UNITY_H
#define UNITY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int unity_pass = 0;
static int unity_fail = 0;
static const char* unity_current_test = "";

#define TEST_BEGIN(name) \
    do { unity_current_test = (name); } while(0)

#define TEST_ASSERT_TRUE(cond) \
    do { \
        if (!(cond)) { \
            printf("  [FAIL] %s — expected TRUE but was FALSE\n", unity_current_test); \
            unity_fail++; \
        } else { \
            printf("  [PASS] %s\n", unity_current_test); \
            unity_pass++; \
        } \
    } while(0)

#define TEST_ASSERT_EQUAL_INT(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("  [FAIL] %s — expected %d but got %d\n", unity_current_test, (int)(expected), (int)(actual)); \
            unity_fail++; \
        } else { \
            printf("  [PASS] %s\n", unity_current_test); \
            unity_pass++; \
        } \
    } while(0)

#define TEST_ASSERT_FALSE(cond) \
    do { \
        if ((cond)) { \
            printf("  [FAIL] %s — expected FALSE but was TRUE\n", unity_current_test); \
            unity_fail++; \
        } else { \
            printf("  [PASS] %s\n", unity_current_test); \
            unity_pass++; \
        } \
    } while(0)

#define UNITY_SUMMARY() \
    do { \
        printf("\n--- Test Summary ---\n"); \
        printf("Passed : %d\n", unity_pass); \
        printf("Failed : %d\n", unity_fail); \
        printf("Total  : %d\n", unity_pass + unity_fail); \
        if (unity_fail > 0) { printf("Result : FAILED\n"); exit(1); } \
        else { printf("Result : PASSED\n"); } \
    } while(0)

#endif /* UNITY_H */
