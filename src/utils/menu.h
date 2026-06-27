#ifndef MENU_H
#define MENU_H

void menuLocations(t_app_state *app_state);
void menuSectors(t_app_state *app_state);
void menuSensors(t_app_state *app_state);
void menuInspections(t_app_state *app_state);
void actionMenuLocations(int option, t_app_state *app_state);
void actionMenuSectors(int option, t_app_state *app_state);
void actionMenuSensors(int option, t_app_state *app_state);
void actionMenuInspections(int option, t_app_state *app_state);
void handleGenerateSystemReport(t_app_state *app_state);
void handleSearchInSystem(t_app_state *app_state);
void handleExportDataOfSystem(t_app_state *app_state);

#endif