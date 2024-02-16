#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/pwm.h>

#include <zephyr/bluetooth/services/bas.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(rumbler, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/ble.h>
#include <zmk/event_manager.h>
#include <zmk/events/ble_active_profile_changed.h>

#define RUMBLE_NODE DT_ALIAS(rumble)

static const struct pwm_dt_spec pwm = PWM_DT_SPEC_GET(RUMBLE_NODE);

void _on()
{
    pwm_set_dt(&pwm, 0, 0);
}

void _off()
{
    pwm_set_dt(&pwm, 100, 100);
}


void rumble(const int count)
{
    if (!device_is_ready(pwm.dev)) {
		LOG_ERR("Error: PWM device %s is not ready\n", pwm.dev->name);
		return;
	}
    for (int i = 0; i < count; i++) {
        LOG_DBG("  Rumble %d ", i);
        
        _on();
        k_sleep(K_MSEC(250));
        _off();
        k_sleep(K_MSEC(100));
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
