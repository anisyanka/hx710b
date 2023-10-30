#ifndef HX710B_H
#define HX710B_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef HX710B_DEVICE_COUNT
# define HX710B_DEVICE_COUNT 1
#endif

typedef enum {
    HX710B_RATE_10Hz,
    HX710B_RATE_40Hz,
} hx710b_rate_t;

typedef struct {
    /* Finctions must be implemented by user. Can't be NULL */
    void (*delay_us)(uint32_t micro_seconds);
    void (*clk_pin_set)(void);
    void (*clk_pin_reset)(void);
    int (*dout_pin_read)(void); // must return 1 if pin set and 0 if reset

    /* current output data rate */
    hx710b_rate_t rate;
} hx710b_dev_t;

void hx710b_power_on(hx710b_dev_t *dev);
void hx710b_power_off(hx710b_dev_t *dev);
void hx710b_set_rate(hx710b_dev_t *dev, hx710b_rate_t rate);

/* returns 1 if data is ready to out */
int hx710b_is_new_data_available(hx710b_dev_t *dev);

/* get the new adc data */
uint32_t hx710b_read_raw_data(hx710b_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif  /* HX710B_H */
