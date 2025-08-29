#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t semaforo_t1;
SemaphoreHandle_t semaforo_t2;
SemaphoreHandle_t semaforo_t3;

const char* nome_aluno = "Victor";

void Tarefa1(void *pvParameters)
{
    while(1)
    {
        xSemaphoreTake(semaforo_t1, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("[Tarefa 1] Executou - %s\n", nome_aluno);
        xSemaphoreGive(semaforo_t2);
    }
}

void Tarefa2(void *pvParameters)
{
    while(1)
    {
        xSemaphoreTake(semaforo_t2, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("[Tarefa 2] Executou - %s\n", nome_aluno);
        xSemaphoreGive(semaforo_t3);
    }
}

void Tarefa3(void *pvParameters)
{
    while(1)
    {
        xSemaphoreTake(semaforo_t3, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("[Tarefa 3] Executou - %s\n", nome_aluno);
        xSemaphoreGive(semaforo_t1);
    }
}

void app_main(void)
{
    semaforo_t1 = xSemaphoreCreateBinary();
    semaforo_t2 = xSemaphoreCreateBinary();
    semaforo_t3 = xSemaphoreCreateBinary();

    xTaskCreate(Tarefa1, "Tarefa 1", 2048, NULL, 5, NULL);
    xTaskCreate(Tarefa2, "Tarefa 2", 2048, NULL, 5, NULL);
    xTaskCreate(Tarefa3, "Tarefa 3", 2048, NULL, 5, NULL);

    xSemaphoreGive(semaforo_t1);
}
