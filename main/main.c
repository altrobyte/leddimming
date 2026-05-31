#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/dac_oneshot.h"
#include "esp_log.h"

#define TAG "DAC_LED"

void app_main(void)
{
    // Configure DAC on GPIO25
    dac_oneshot_config_t dac_cfg = {
        .chan_id = DAC_CHAN_0
    };

    dac_oneshot_handle_t dac_handle;
    ESP_ERROR_CHECK(dac_oneshot_new_channel(&dac_cfg, &dac_handle));

    ESP_LOGI(TAG, "DAC LED Brightness Demo Started");

    while (1)
    {
        // Fade IN
        for (int value = 0; value <= 255; value++)
        {
            dac_oneshot_output_voltage(dac_handle, value);
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        // Fade OUT
        for (int value = 255; value >= 0; value--)
        {
            dac_oneshot_output_voltage(dac_handle, value);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}