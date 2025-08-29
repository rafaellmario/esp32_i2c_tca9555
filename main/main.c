
/*
 * User defined I2C Communication library (ESP32)
 * Made with ESP IDF V5.4
 * Author: Rafael M. Silva 
 * email: rafaellmario@unifei.edu.br
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"
#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "user_i2c.h"
#include "tca9555.h"

#include "esp_eth.h"


static const char* TAG = "MAIN";

void app_main(void)
{
    
 // i2c configuration
 ESP_LOGI(TAG,"Setting-up I2C ...");
 i2c_master_bus_handle_t i2c0BusHandler = NULL;
 ESP_ERROR_CHECK(i2c_bus_init(I2C0_PORT,I2C0_SCL_IO,I2C0_SDA_IO,&i2c0BusHandler));

 i2c_master_dev_handle_t i2c0TCA9555 = NULL;
 ESP_ERROR_CHECK(i2c_attach_device(TCA9555_ADDR,i2c0BusHandler,&i2c0TCA9555));
 
 if(i2c_master_probe(i2c0BusHandler,TCA9555_ADDR,10) == ESP_OK)
 {
    ESP_LOGI(TAG,"Device at address 0x%x  was detected.",TCA9555_ADDR);
    tca_config_mode(i2c0TCA9555, 0x0000); // set all pins as outputs
 }
 else 
    ESP_LOGW(TAG,"!!!! Failure to initialize I2C bus device!!!!");
 ESP_LOGI(TAG,"Done.");

 

 // 
 while(true)
 {
    tca_set_outputs(i2c0TCA9555,TCA_P0B0|TCA_P0B2|TCA_P0B4|TCA_P0B6);
    tca_clear_outputs(i2c0TCA9555,TCA_P0B1|TCA_P0B3|TCA_P0B5|TCA_P0B7);
    vTaskDelay(pdMS_TO_TICKS(2000));

    tca_clear_outputs(i2c0TCA9555,TCA_P0B0|TCA_P0B2|TCA_P0B4|TCA_P0B6);
    tca_set_outputs(i2c0TCA9555,TCA_P0B1|TCA_P0B3|TCA_P0B5|TCA_P0B7);
    vTaskDelay(pdMS_TO_TICKS(2000));
 }

}
