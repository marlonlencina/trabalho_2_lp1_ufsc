#ifndef INSPECTIONS_H
#define INSPECTIONS_H

#include "../types.h"
#include "../helpers.h"

t_inspection *createNewInspection(t_sensor *sensor_selected_pointer);
void insertNewInspectionAtDatabase(t_inspection **list_inspections, t_inspection *new_inspection);
void deleteInspectionAtDatabase(t_inspection **list_inspections, string inspection_id);
void listAllInspections(t_inspection *list_inspections);
void selectInspection(t_inspection *inspection, t_inspection **inspection_selected_pointer);
t_inspection *findInspectionById(t_inspection *list_inspections, string inspection_id);
t_inspection *findInspectionByIdx(t_inspection *list_inspections, int idx);
t_inspection *promptAndFindInspectionByIdx(t_inspection *list_inspections);
int countTotalInspections(t_inspection *list_inspection);
void updateSensorRange(t_sensor *sensor_selected_pointer);

#endif