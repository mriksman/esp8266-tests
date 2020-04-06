#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "esp_app_format.h"
#include "esp_ota_ops.h"
#include "esp_log.h"
#include "esp_image_format.h"
static const char *TAG = "main";

void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_DEBUG);       
    esp_log_level_set("vfs", ESP_LOG_INFO);     
 
    // Initialize NVS.
    #ifdef CONFIG_IDF_TARGET_ESP32
        esp_err_t err = nvs_flash_init();
        if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            err = nvs_flash_init();
        }
        ESP_ERROR_CHECK(err);
    #elif CONFIG_IDF_TARGET_ESP8266
      //  nvs_flash_init() is called in startup.c with assert == ESP_OK. So if you change 
      //  partition size, this will fail. Comment the assert out and then nvs_flash_erase()
    #endif


    const esp_partition_t *next = esp_ota_get_running_partition();
    esp_app_desc_t app_desc;
    esp_ota_get_partition_description(next, &app_desc);
    ESP_LOGI(TAG, "Magic word 0x%8x, App version %s, Proj Name %s, Time %s",
             app_desc.magic_word, app_desc.version, app_desc.project_name, app_desc.time);

    ESP_LOGI(TAG, "esp_image_header_t %d esp_image_segment_header_t %d esp_app_desc_t %d", sizeof(esp_image_header_t), sizeof(esp_image_segment_header_t), sizeof(esp_app_desc_t));

    const esp_app_desc_t *app_desc1;
    app_desc1 = esp_ota_get_app_description();
    ESP_LOGI(TAG, "Magic word 0x%8x, App version %s, Proj Name %s, Time %s",
             app_desc1->magic_word, app_desc1->version, app_desc1->project_name, app_desc1->time);


    esp_image_header_t image_header;
    esp_partition_read(next, 0, &image_header, sizeof(esp_image_header_t));
    ESP_LOGI(TAG, "Magic word 0x%2x, Entry 0x%4x, SPI size %d",
             image_header.magic, image_header.entry_addr - 0x40201000, image_header.spi_size);




}
