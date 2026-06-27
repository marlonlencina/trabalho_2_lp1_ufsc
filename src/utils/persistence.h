#ifndef PERSISTENCE_H
#define PERSISTENCE_H

void handlerLoadAllEntitiesData(t_app_state *app_state);
void saveAllUserDataOnBinaryFile(t_app_state *app_state);
void loadLocationsFromFile(t_app_state *app_state, string filepath);
void loadSectorsFromFile(t_app_state *app_state, string filepath);
void loadSensorsFromFile(t_app_state *app_state, string filepath);
void loadInspectionsFromFile(t_app_state *app_state, string filepath);

#endif