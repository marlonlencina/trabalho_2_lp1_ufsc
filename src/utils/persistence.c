#include "../types.h"
#include "../helpers.h"
#include "../entities/inspections.h"
#include "../entities/sensors.h"
#include "../entities/sectors.h"
#include "../entities/locations.h"

void loadLocationsFromFile(t_app_state *app_state, string filepath)
{
    FILE *file = NULL;
    file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("[LOCATIONS] Primeira incialização ou erro de permissão. \n");
        return;
    }
    t_location record_location;
    while (fread(&record_location, sizeof(t_location), 1, file) == 1)
    {
        t_location *new_location = (t_location *)malloc(sizeof(t_location));
        if (new_location)
        {
            *new_location = record_location;
            insertNewLocationAtDatabase(&app_state->database, new_location);
        }
    }
    fclose(file);
};
void loadSectorsFromFile(t_app_state *app_state, string filepath)
{
    FILE *file = NULL;
    file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("[SECTORS] Primeira incialização ou erro de permissão. \n");
        return;
    }

    t_sector record_sector;
    while (fread(&record_sector, sizeof(t_sector), 1, file) == 1)
    {
        t_sector *new_sector = (t_sector *)malloc(sizeof(t_sector));
        if (new_sector)
        {
            *new_sector = record_sector;
            t_location *matching_location = findLocationById(app_state->database, new_sector->location_id);
            if (matching_location)
            {
                insertNewSectorAtDatabase(&matching_location->sectors, new_sector);
            }
            else
            {
                free(new_sector);
            }
        }
    }
    fclose(file);
}
void loadSensorsFromFile(t_app_state *app_state, string filepath)
{
    FILE *file = NULL;
    file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("[SENSORS] Primeira incialização ou erro de permissão. \n");
        return;
    }

    t_sensor record_sensor;
    while (fread(&record_sensor, sizeof(t_sensor), 1, file) == 1)
    {
        t_sensor *new_sensor = (t_sensor *)malloc(sizeof(t_sensor));
        if (new_sensor)
        {
            *new_sensor = record_sensor;
            t_location *current_location = app_state->database;
            int has_already_inserted = 0;
            while (current_location != NULL && !has_already_inserted)
            {
                t_sector *matching_sector = findSectorById(current_location->sectors, new_sensor->sector_id);
                if (matching_sector)
                {
                    insertNewSensorAtDatabase(&matching_sector->sensors, new_sensor);
                    has_already_inserted = 1;
                }

                current_location = current_location->next;
            }
            if (!has_already_inserted)
                free(new_sensor);
        }
    }
    fclose(file);
};
void loadInspectionsFromFile(t_app_state *app_state, string filepath)
{
    FILE *file = NULL;
    file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("[INSPECTIONS] Primeira incialização ou erro de permissão. \n");
        return;
    }

    t_inspection record_inspection;
    while (fread(&record_inspection, sizeof(t_inspection), 1, file) == 1)
    {
        int has_already_inserted = 0;
        t_inspection *new_inspection = (t_inspection *)malloc(sizeof(t_inspection));
        if (new_inspection)
        {
            *new_inspection = record_inspection;
            t_location *current_location = app_state->database;
            while (current_location != NULL && !has_already_inserted)
            {
                t_sector *current_sector = current_location->sectors;
                while (current_sector != NULL && !has_already_inserted)
                {
                    t_sensor *matching_sensor = findSensorById(current_sector->sensors, new_inspection->sensor_id);
                    if (matching_sensor)
                    {
                        insertNewInspectionAtDatabase(&matching_sensor->inspections, new_inspection);
                        has_already_inserted = 1;
                    }
                    current_sector = current_sector->next;
                }

                current_location = current_location->next;
            }
        }
        if (!has_already_inserted)
        {
            free(new_inspection);
        }
    }
    fclose(file);
}
void saveAllUserDataOnBinaryFile(t_app_state *app_state)
{
    printf("Iniciando persistência de dados... \n");

    t_string filepath_locations = getFilepathMatchEntity(LOCATION, app_state->default_binary_filename,
                                                         app_state->default_filepath_to_output_folder);
    t_string filepath_sectors = getFilepathMatchEntity(SECTOR, app_state->default_binary_filename,
                                                       app_state->default_filepath_to_output_folder);
    t_string filepath_sensors = getFilepathMatchEntity(SENSOR, app_state->default_binary_filename,
                                                       app_state->default_filepath_to_output_folder);
    t_string filepath_inspections = getFilepathMatchEntity(INSPECTION, app_state->default_binary_filename,
                                                           app_state->default_filepath_to_output_folder);

    FILE *file_locations;
    file_locations = fopen(filepath_locations.response, "wb");
    FILE *file_sectors;
    file_sectors = fopen(filepath_sectors.response, "wb");
    FILE *file_sensors;
    file_sensors = fopen(filepath_sensors.response, "wb");
    FILE *file_inspections;
    file_inspections = fopen(filepath_inspections.response, "wb");

    t_location *current_location = app_state->database;
    while (current_location != NULL)
    {
        t_location copy_current_location = *current_location;
        copy_current_location.sectors = NULL;
        copy_current_location.next = NULL;
        fwrite(&copy_current_location, sizeof(t_location), 1, file_locations);
        t_sector *current_sector = current_location->sectors;
        while (current_sector != NULL)
        {
            t_sector copy_current_sector = *current_sector;
            copy_current_sector.sensors = NULL;
            copy_current_sector.next = NULL;
            fwrite(&copy_current_sector, sizeof(t_sector), 1, file_sectors);
            t_sensor *current_sensor = current_sector->sensors;
            while (current_sensor != NULL)
            {
                t_sensor copy_current_sensor = *current_sensor;
                copy_current_sensor.inspections = NULL;
                copy_current_sensor.next = NULL;
                fwrite(&copy_current_sensor, sizeof(t_sensor), 1, file_sensors);
                t_inspection *current_inspection = current_sensor->inspections;
                while (current_inspection != NULL)
                {
                    t_inspection copy_current_inspection = *current_inspection;
                    copy_current_inspection.next = NULL;
                    fwrite(&copy_current_inspection, sizeof(t_inspection), 1, file_inspections);
                    current_inspection = current_inspection->next;
                }
                current_sensor = current_sensor->next;
            }
            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }

    fclose(file_locations);
    fclose(file_sectors);
    fclose(file_sensors);
    fclose(file_inspections);

    printf("Dados salvos. \n");
}
void handlerLoadAllEntitiesData(t_app_state *app_state)
{
    printf("Iniciando carregamento de dados... \n");
    printf("Recuperando locations... \n");
    loadLocationsFromFile(app_state, getFilepathMatchEntity(LOCATION, app_state->default_binary_filename,
                                                            app_state->default_filepath_to_output_folder)
                                         .response);
    printf("Recuperando sectors... \n");
    loadSectorsFromFile(app_state, getFilepathMatchEntity(SECTOR, app_state->default_binary_filename,
                                                          app_state->default_filepath_to_output_folder)
                                       .response);
    printf("Recuperando sensors... \n");
    loadSensorsFromFile(app_state, getFilepathMatchEntity(SENSOR, app_state->default_binary_filename,
                                                          app_state->default_filepath_to_output_folder)
                                       .response);
    printf("Recuperando inspections... \n");
    loadInspectionsFromFile(app_state, getFilepathMatchEntity(INSPECTION, app_state->default_binary_filename,
                                                              app_state->default_filepath_to_output_folder)
                                           .response);
    printf("Dados salvos carregados. \n");

    confirmAndClear();
};
