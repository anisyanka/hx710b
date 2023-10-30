#include "hx710b.h"

#define HX710B_ADC_BITS (24U)
#define HX710B_CLOCK_PULSE_US (20U)

void hx710b_power_on(hx710b_dev_t *dev)
{
    dev->rate = HX710B_RATE_10Hz;
    dev->clk_pin_reset();
    dev->delay_us(100);
}

void hx710b_power_off(hx710b_dev_t *dev)
{
    dev->clk_pin_set();
    dev->delay_us(100);
}

void hx710b_set_rate(hx710b_dev_t *dev, hx710b_rate_t rate)
{
    dev->rate = rate;
}

int hx710b_is_new_data_available(hx710b_dev_t *dev)
{
    if (!dev->dout_pin_read()) {
        dev->delay_us(10);
        return 1;
    }

    return 0;
}

static void pulse(hx710b_dev_t *dev)
{
    dev->clk_pin_set();
    dev->delay_us(HX710B_CLOCK_PULSE_US);
    dev->clk_pin_reset();
    dev->delay_us(HX710B_CLOCK_PULSE_US);
}

uint32_t hx710b_read_raw_data(hx710b_dev_t *dev)
{
    uint32_t hx710b_data = 0;
    uint32_t pin_val = 0;

    for (int i = 0; i < HX710B_ADC_BITS; ++i) {
        dev->clk_pin_set();
        dev->delay_us(HX710B_CLOCK_PULSE_US);
        pin_val = dev->dout_pin_read();
        hx710b_data |= pin_val << (HX710B_ADC_BITS - i - 1);
        dev->clk_pin_reset();
        dev->delay_us(HX710B_CLOCK_PULSE_US);
    }

    if (dev->rate == HX710B_RATE_10Hz) {
        pulse(dev);
    } else {
        pulse(dev);
        pulse(dev);
        pulse(dev);
    }

    return hx710b_data;
}
