#ifdef TEST

#include "unity.h"

#include "bar-graph.h"
#include "mock_led.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_bar_graph_0_percent_all_off(void)
{
    led_turn_off_Expect(0);
    led_turn_off_ExpectAndReturn(1);
    led_turn_off_Expect(2);
    led_turn_off_Expect(3);

    bar_graph_set_percent(0);
}
void test_bar_graph_100_percent_all_on(void)
{
    led_turn_on_Expect(0);
    led_turn_on_Expect(1);
    led_turn_on_Expect(2);
    led_turn_on_Expect(3);

    bar_graph_set_percent(100);
}
#endif // TEST
