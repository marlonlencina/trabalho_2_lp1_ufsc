#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"

#define MAX_LOCATIONS 5
#define MAX_SECTORS 5
#define MAX_SENSORS 3
#define MAX_INSPECTIONS 5
#define MAX_SENSORS_TYPES 5
#define MAX_INSPECTIONS_ON_SAME_DAY 2
#define END 0
#define NOT_FOUND 0
#define NOT_SELECTED -1

void menuLocations(t_app_state *app_state);
void menuSectors(t_app_state *app_state);
void menuSensors(t_app_state *app_state);
void menuInspections(t_app_state *app_state);
void actionMenuLocations(int option, t_app_state *app_state);
void actionMenuSectors(int option, t_app_state *app_state);
void actionMenuSensors(int option, t_app_state *app_state);
void actionMenuInspections(int option, t_app_state *app_state);
void resetStateOfMenuSelectedPointers(t_entities entity_type, t_app_state *state);
void shutdownProgram();

t_location *createNewLocation();
void insertNewLocationAtDatabase(t_location **list_locations, t_location *new_location);
void deleteLocationAtDatabase(t_location **list_locations, string location_id);
void listAllLocations(t_location *list_locations);
void selectLocation(t_location *location, t_location **location_selected);
t_location *findLocationById(t_location **list_locations, string location_id);
t_location *findLocationByIdx(t_location *list, int idx);
t_location *promptAndFindLocationByIdx(t_location *list_locations);

t_sector *createNewSector(t_location *location_selected_pointer);
void insertNewSectorAtDatabase(t_sector **list_sectors, t_sector *new_sector);
void deleteSectorAtDatabase(t_sector **list_sectors, string sector_id);
void listAllSectors(t_sector *list_sectors);
void selectSector(t_sector *sector, t_sector **sector_selected_pointer);
t_sector *findSectorById(t_sector *list_sectors, string sector_id);
t_sector *findSectorByIdx(t_sector *list_sectors, int idx);
t_sector *promptAndFindSectorByIdx(t_sector *list_sectors);

t_sensor *createNewSensor(t_sector *sector_selected_pointer);
void insertNewSensorAtDatabase(t_sensor **list_sensors, t_sensor *new_sensor);
void deleteSensorAtDatabase(t_sensor **list_sensors, string sensor_id);
void listAllSensors(t_sensor *list_sensors);
void selectSensor(t_sensor *sensor, t_sensor **sensor_selected_pointer);
t_sensor *findSensorById(t_sensor *list_sensor, string sensor_id);
t_sensor *findSensorByIdx(t_sensor *list_sensor, int idx);
t_sensor *promptAndFindSensorByIdx(t_sensor *list_sensors);
t_sensor_template getSensorTemplate(t_sensor_types sensor_type);

t_inspection *createNewInspection(t_sensor *sensor_selected_pointer);
void insertNewInspectionAtDatabase(t_inspection **list_inspections, t_inspection *new_inspection);
void deleteInspectionAtDatabase(t_inspection **list_inspections, string inspection_id);
void listAllInspections(t_inspection *list_inspections);
void selectInspection(t_inspection *inspection, t_inspection **inspection_selected_pointer);
t_inspection *findInspectionById(t_inspection *list_inspections, string inspection_id);
t_inspection *findInspectionByIdx(t_inspection *list_inspections, int idx);
t_inspection *promptAndFindInspectionByIdx(t_inspection *list_inspections);

void confirmAndClear();
bool checkIfIsTheSameDay(time_t firstTimestamp, time_t secondTimestamp);
void generateUniqueId(char *buffer, t_entities entity_type);
void formatStringRemoveEnter(string str);
void formatStringToUppercase(string str);
void formatStringToSystemPattern(string str);
t_string mapSensorTypeToString(int sensor_type_enum);
t_string mapSensorTypeUnitToString(int sensor_type_unit_enum);
t_string mapEntityToString(int entity);
t_string mapTimestampToString(time_t timestamp, bool enable_hours);

void handleGenerateSystemReport(t_app_state *app_state);
void handleSearchInSystem(t_app_state *app_state);
void generateReportOfInspections(t_location *locations);
void generateReportsOfSectors(t_location *locations);
void generateReportOfSensors(t_location *locations);
void generateReportOfInspectionsAverage(t_location *locations);
void generateReportOfInspectionsVariation(t_location *locations);
void searchForSectorDescription(t_location *locations);
void searchForSensorType(t_location *locations);