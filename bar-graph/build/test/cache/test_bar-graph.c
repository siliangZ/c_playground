#include "mock_led.h"
#include "src/bar-graph.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






void setUp(void)

{

}



void tearDown(void)

{

}



void test_bar_graph_0_percent_all_off(void)

{

    led_turn_off_CMockExpect(17, 0);

    led_turn_off_CMockExpect(18, 1);

    led_turn_off_CMockExpect(19, 2);

    led_turn_off_CMockExpect(20, 3);



    bar_graph_set_percent(0);

}

void test_bar_graph_100_percent_all_on(void)

{

    led_turn_on_CMockExpect(26, 0);

    led_turn_on_CMockExpect(27, 1);

    led_turn_on_CMockExpect(28, 2);

    led_turn_on_CMockExpect(29, 3);



    bar_graph_set_percent(0);

}
