#ifndef HELPERS_H
#define HELPERS_H

#include "types.h"
#include "global_config.h"
t_string mapSensorTypeToString(int sensor_type_enum);
t_string mapSensorTypeUnitToString(int sensor_type_unit_enum);
t_string mapEntityToString(int entity);
t_string mapTimestampToString(time_t timestamp, bool enable_hours);
t_string getFilepathMatchEntity(t_entities entity, string base_filepath, string base_filefolder);

void confirmAndClear();
bool checkIfIsTheSameDay(time_t firstTimestamp, time_t secondTimestamp);
void generateUniqueId(char *buffer, t_entities entity_type);
void formatStringRemoveEnter(string str);
void formatStringToUppercase(string str);
void formatStringToSystemPattern(string str);

void resetStateOfMenuSelectedPointers(t_entities entity_type, t_app_state *state);
void shutdownProgram();

#endif
