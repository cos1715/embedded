#include <Arduino.h>
#include "esp_partition.h"
#include <esp_flash.h>
#include <esp_flash_partitions.h>
#include "tasks/task2_star.h"

void task2StarSetup()
{
  constexpr size_t PARTITION_TABLE_READ_SIZE = 192;
  uint8_t partitionTable[PARTITION_TABLE_READ_SIZE];

  esp_err_t result = esp_flash_read(
      esp_flash_default_chip,
      partitionTable,
      ESP_PARTITION_TABLE_OFFSET,
      PARTITION_TABLE_READ_SIZE);

  if (result == ESP_OK)
  {
    Serial.println("OK");
  }
  else
  {
    Serial.print(result);
  }

  for (size_t i = 0; i < PARTITION_TABLE_READ_SIZE; i++)
  {
    Serial.printf("%02X ", static_cast<unsigned>(partitionTable[i]));
  }

  Serial.println();
}