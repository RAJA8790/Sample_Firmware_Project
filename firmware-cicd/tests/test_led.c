/*
 * Unit Tests — LED Module
 * Framework: Unity (minimal embedded version)
 * Run: make test
 */

#include "../unity/unity.h"
#include "../src/led.h"

/* ── Test cases ─────────────────────────────────────────────────────────────*/

void test_led_init_all_off(void)
{
    TEST_BEGIN("led_init sets all LEDs to OFF");
    led_init();
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_GREEN));
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_RED));
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_BLUE));
}

void test_led_set_on(void)
{
    TEST_BEGIN("led_set turns LED ON correctly");
    led_init();
    led_set(LED_GREEN, LED_ON);
    TEST_ASSERT_EQUAL_INT(LED_ON, led_get(LED_GREEN));
}

void test_led_set_off(void)
{
    TEST_BEGIN("led_set turns LED OFF correctly");
    led_init();
    led_set(LED_RED, LED_ON);
    led_set(LED_RED, LED_OFF);
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_RED));
}

void test_led_toggle(void)
{
    TEST_BEGIN("led_toggle flips LED state OFF->ON");
    led_init();
    led_toggle(LED_BLUE);
    TEST_ASSERT_EQUAL_INT(LED_ON, led_get(LED_BLUE));
}

void test_led_toggle_twice(void)
{
    TEST_BEGIN("led_toggle flips LED state ON->OFF->ON");
    led_init();
    led_toggle(LED_GREEN);
    led_toggle(LED_GREEN);
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_GREEN));
}

void test_led_all_off(void)
{
    TEST_BEGIN("led_all_off turns all LEDs off");
    led_init();
    led_set(LED_GREEN, LED_ON);
    led_set(LED_RED,   LED_ON);
    led_set(LED_BLUE,  LED_ON);
    led_all_off();
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_GREEN));
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_RED));
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_BLUE));
}

void test_led_independent(void)
{
    TEST_BEGIN("LEDs operate independently");
    led_init();
    led_set(LED_GREEN, LED_ON);
    led_set(LED_RED,   LED_OFF);
    TEST_ASSERT_EQUAL_INT(LED_ON,  led_get(LED_GREEN));
    TEST_ASSERT_EQUAL_INT(LED_OFF, led_get(LED_RED));
}

void test_led_invalid_id_no_crash(void)
{
    TEST_BEGIN("Invalid LED id does not crash");
    led_init();
    led_set((led_id_t)99, LED_ON);   /* should be ignored */
    TEST_ASSERT_TRUE(1);             /* if we get here, no crash */
}

/* ── Main ───────────────────────────────────────────────────────────────────*/

int main(void)
{
    printf("\n=== LED Module Unit Tests ===\n\n");

    test_led_init_all_off();
    test_led_set_on();
    test_led_set_off();
    test_led_toggle();
    test_led_toggle_twice();
    test_led_all_off();
    test_led_independent();
    test_led_invalid_id_no_crash();

    UNITY_SUMMARY();
    return 0;
}
