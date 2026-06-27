#ifndef SENSORS_H
#define SENSORS_H

#include "../types.h"

t_sensor *createNewSensor(t_sector *sector_selected_pointer);
void insertNewSensorAtDatabase(t_sensor **list_sensors, t_sensor *new_sensor);
void deleteSensorAtDatabase(t_sensor **list_sensors, string sensor_id);
void listAllSensors(t_sensor *list_sensors);
void selectSensor(t_sensor *sensor, t_sensor **sensor_selected_pointer);
t_sensor *findSensorById(t_sensor *list_sensor, string sensor_id);
t_sensor *findSensorByIdx(t_sensor *list_sensor, int idx);
t_sensor *promptAndFindSensorByIdx(t_sensor *list_sensors);
t_sensor_template getSensorTemplate(t_sensor_types sensor_type);
int countTotalSensors(t_sensor *list_sensors);

#endif