#ifndef SECTORS_H
#define SECTORS_H

#include "../types.h"
#include "../helpers.h" 
#include "sensors.h"

t_sector *createNewSector(t_location *location_selected_pointer);
void insertNewSectorAtDatabase(t_sector **list_sectors, t_sector *new_sector);
void deleteSectorAtDatabase(t_sector **list_sectors, string sector_id);
void listAllSectors(t_sector *list_sectors);
void selectSector(t_sector *sector, t_sector **sector_selected_pointer);
t_sector *findSectorById(t_sector *list_sectors, string sector_id);
t_sector *findSectorByIdx(t_sector *list_sectors, int idx);
t_sector *promptAndFindSectorByIdx(t_sector *list_sectors);
int countTotalSectors(t_sector *list_sectors);

#endif