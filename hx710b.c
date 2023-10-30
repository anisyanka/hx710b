#include "hx710b.h"

#define HX710B_ADC_BITS (24U)

void hx710b_power_on(hx710b_dev_t *dev)
{
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

uint32_t hx710b_read_raw_data(hx710b_dev_t *dev)
{
    uint32_t adc_data = 0;
    return adc_data;
}
