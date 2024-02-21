#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/bluetooth/services/bas.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(rumble, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/ble.h>    
#include <zmk/event_manager.h>
#include <zmk/events/ble_active_profile_changed.h>


/* The devicetree node identifier for the "rumble" alias. */
#define RUMBLE_NODE	DT_ALIAS(rumble)
#if !DT_NODE_HAS_STATUS(RUMBLE_NODE, okay)
#error "Unsupported board: rumbler devicetree alias is not defined or not okay"
#endif

static const struct gpio_dt_spec rmbl = GPIO_DT_SPEC_GET(RUMBLE_NODE, gpios);

void brr()
{
    gpio_pin_toggle_dt(&rmbl);
    k_msleep(250);
    gpio_pin_toggle_dt(&rmbl);
    k_msleep(50);
}

void rumble(const int count)
{
    if (!gpio_is_ready_dt(&rmbl)) {
		LOG_ERR("Error: rumble device %d is not ready\n", rmbl.pin);
		return;
	}

	if (gpio_pin_configure_dt(&rmbl, GPIO_OUTPUT_ACTIVE) < 0) {
        LOG_ERR("Error: Couldn't activate rumble device %d\n", rmbl.pin);
		return;
	}

    for (int i = 0; i < count; i++) {
        LOG_DBG("  Rumble %d ", i);
        brr();
    }
    LOG_DBG("DONE rumbling %d times!", count);
}


int ble_active_profile_change_listener(const zmk_event_t *eh)
{
    const struct zmk_ble_active_profile_changed *profile_ev = NULL;
    if ((profile_ev = as_zmk_ble_active_profile_changed(eh)) == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }
    const int count = profile_ev->index + 1;
    LOG_WRN("Bluetooth profile [%d] is active -> rumbling [%d] times!", profile_ev->index, count);
    rumble(count);
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(ble_active_profile_change_status, ble_active_profile_change_listener)
#if defined(CONFIG_ZMK_BLE)
    ZMK_SUBSCRIPTION(ble_active_profile_change_status, zmk_ble_active_profile_changed);
#endif
