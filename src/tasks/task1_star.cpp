#include <Arduino.h>
#include "esp_partition.h"
#include "tasks/task1_star.h"

void task1StarSetup () {

  esp_partition_iterator_t iterator = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);

  while (iterator != NULL){
    const esp_partition_t* partition = esp_partition_get(iterator);

    Serial.print("label: ");
    Serial.println(partition->label);

    Serial.print("type: ");
    Serial.println(partition->type);

    Serial.print("subtype: ");
    Serial.println(partition->subtype);

    Serial.print("size: ");
    Serial.println(partition->size);

    Serial.print("address: ");
    Serial.println(partition->address);
    Serial.println();
    Serial.println();
    Serial.println();

    iterator = esp_partition_next(iterator);
  }

  esp_partition_iterator_release(iterator);
}