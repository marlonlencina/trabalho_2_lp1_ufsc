#include "global_config.h"
#include "types.h"
#include "main.h"
#include "helpers.h"

#include "./utils/menu.h"
#include "./utils/persistence.h"
#include "./utils/exports.h"
#include "./utils/reports.h"
#include "./utils/search.h"

#include "./entities/locations.h"
#include "./entities/sectors.h"
#include "./entities/sensors.h"
#include "./entities/inspections.h"

int main()
{
    srand(time(NULL));

    t_app_state app_state = {0, .default_binary_filename = "datasave.txt", .filepath_csv = "spreadsheet.csv",
                             .filepath_html = "index.html", .default_filepath_to_output_folder = "./output"};

    string filepath_to_locations_folder = "";
    string filepath_to_sectors_folder = "";
    string filepath_to_sensors_folder = "";
    string filepath_to_inspections_folder = "";

    strcat(filepath_to_locations_folder, app_state.default_filepath_to_output_folder);
    strcat(filepath_to_locations_folder, "/locations");

    strcat(filepath_to_sectors_folder, app_state.default_filepath_to_output_folder);
    strcat(filepath_to_sectors_folder, "/sectors");

    strcat(filepath_to_sensors_folder, app_state.default_filepath_to_output_folder);
    strcat(filepath_to_sensors_folder, "/sensors");

    strcat(filepath_to_inspections_folder, app_state.default_filepath_to_output_folder);
    strcat(filepath_to_inspections_folder, "/inspections");

    string command_to_create_folder_to_locations = "";
    string command_to_create_folder_to_sectors = "";
    string command_to_create_folder_to_sensors = "";
    string command_to_create_folder_to_inspections = "";

    strcat(command_to_create_folder_to_locations, "mkdir -p ");
    strcat(command_to_create_folder_to_locations, filepath_to_locations_folder);

    strcat(command_to_create_folder_to_sectors, "mkdir -p ");
    strcat(command_to_create_folder_to_sectors, filepath_to_sectors_folder);

    strcat(command_to_create_folder_to_sensors, "mkdir -p ");
    strcat(command_to_create_folder_to_sensors, filepath_to_sensors_folder);

    strcat(command_to_create_folder_to_inspections, "mkdir -p ");
    strcat(command_to_create_folder_to_inspections, filepath_to_inspections_folder);

    system(command_to_create_folder_to_locations);
    system(command_to_create_folder_to_sectors);
    system(command_to_create_folder_to_sensors);
    system(command_to_create_folder_to_inspections);

    handlerLoadAllEntitiesData(&app_state);

    for (;;)
    {
        if (app_state.location_selected_pointer != NULL && app_state.sector_selected_pointer != NULL &&
            app_state.sensor_selected_pointer != NULL)
        {
            menuInspections(&app_state);
        }
        else if (app_state.location_selected_pointer != NULL && app_state.sector_selected_pointer != NULL)
        {
            menuSensors(&app_state);
        }
        else if (app_state.location_selected_pointer != NULL)
        {
            menuSectors(&app_state);
        }
        else
        {
            menuLocations(&app_state);
        }
    }
    return 0;
}
