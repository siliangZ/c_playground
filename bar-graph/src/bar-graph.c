#include "bar-graph.h"
#include "led.h"
void bar_graph_set_percent(uint8_t percent)
{
    led_turn_off(0);
    led_turn_off(1);
    led_turn_off(2);
    led_turn_off(3);
}