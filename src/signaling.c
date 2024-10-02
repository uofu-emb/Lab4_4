#include <FreeRTOS.h>
#include <semphr.h>
#include "signaling.h"

void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data){
     xSemaphoreTake(request,portMAX_DELAY);

     //add 5 to the data
     data->output = data->input + 5;

     xSemaphoreGive(response);
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data){

     xSemaphoreGive(request);
     if(xSemaphoreTake(response,1000) == pdTRUE){
          return pdTRUE;
     }
     return pdFALSE;

}