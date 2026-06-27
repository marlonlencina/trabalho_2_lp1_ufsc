#ifndef LOCATIONS_H
#define LOCATIONS_H

#include "../types.h"
#include "../helpers.h" 

t_location *createNewLocation();
void insertNewLocationAtDatabase(t_location **list_locations, t_location *new_location);
void deleteLocationAtDatabase(t_location **list_locations, string location_id);
void listAllLocations(t_location *list_locations);
void selectLocation(t_location *location, t_location **location_selected);
t_location *findLocationById(t_location *list_locations, string location_id);
t_location *findLocationByIdx(t_location *list, int idx);
t_location *promptAndFindLocationByIdx(t_location *list_locations);
int countTotalLocations(t_location *list_locations);

#endif