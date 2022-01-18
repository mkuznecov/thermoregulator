#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "stm32f0xx.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_adc.h"
#include "stm32f0xx_hal_i2c.h"

#include "constants.h"
#include "tmp117.h"

namespace thermoregulator {
class OperatingMode {
  public:
    explicit OperatingMode(I2C_HandleTypeDef* hi2c);
    void change_mode();
    void blink_leds() const;
    void reset_leds() const;
    OperatingModeParams current_mode() const;
    void enable_heating();
    void disable_heating();
  private:
    OperatingModeParams params_;
    tmp117 sensor1_;
    tmp117 sensor2_;
};

enum class Color {Red, Green, Blue, Orange, Yellow};
Color get_color_by_battery_level(float bat_level);
void set_addr_led_color(Color);

enum class ButtonPressType {SHORT_PRESS, LONG_PRESS, NO_PRESS};
ButtonPressType check_button_press(GPIO_TypeDef* port, uint16_t pin,
                                   uint32_t time_ms_short, uint32_t time_ms_long);

enum class DeviceStatus {DEVICE_WORKING, DEVICE_CHARGING, DEVICE_CHARGED, UNKNOWN};
DeviceStatus device_status();
void change_addr_led_behaviour(DeviceStatus dev_state, Color = Color::Red);

float get_battery_voltage(ADC_HandleTypeDef* hadc);
void poweroff();
}
#endif // AUXILIRY_H
