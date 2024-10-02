#include <FreeRTOS.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include <stdio.h>
#include <queue.h>

#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id){

     //loop through and calculate
     while(1){
          //create a message struct blank
          struct request_msg msg = {};
          //pull from requests queue and get the message 
          xQueueReceive(requests,&msg,portMAX_DELAY);
          //perform calculation
          msg.output = msg.input + 5;
          msg.handled_by = id;
          //put data into the results queue
          xQueueSendToBack(results, &msg, portMAX_DELAY);
     }
}