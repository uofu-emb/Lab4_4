#include <FreeRTOS.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include <stdio.h>
#include <queue.h>

#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id){
     while(1)
{    struct request_msg msg = {}
     xQueueReceive(requests, &msg, portMAX_DELAY);
}
}