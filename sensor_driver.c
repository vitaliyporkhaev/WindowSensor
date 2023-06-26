#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sensor_driver.h"

int curr_state = 0;

int start() {
    usleep(500);
    curr_state = 1;
    return 0;
}

int stop() {
    curr_state = 0;
    return 0;
}

int status() {
    printf("Oтправка запроса на считывание состояния окна\n");
    usleep(500);
    int state = rand() % 2;
    printf("Cчитывание состояния окна завершено\n");
    return state;
}


float temperatureIS() {
    printf("Oтправка запроса на считывание температуры\n");
    usleep(500);
    float temperature = (float)(rand() % 30);
    printf("Cчитывание температуры завершено\n");
    return temperature;
}


float humidityIS() {
    printf("Oтправка запроса на считывание влажности\n");
    usleep(500); 
    float humidity = (float)(rand() % 100);
    printf("Cчитывание влажности завершено\n");
    return humidity;
}
