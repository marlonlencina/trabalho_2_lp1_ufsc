#include "../types.h"
#include "../helpers.h"

void generateCsvFile(t_app_state *app_state)
{
    FILE *fp_locations = NULL;
    FILE *fp_sectors = NULL;
    FILE *fp_sensors = NULL;
    FILE *fp_inspections = NULL;

    string filepath_locations;
    strcpy(filepath_locations,
           getFilepathMatchEntity(LOCATION, app_state->filepath_csv, app_state->default_filepath_to_output_folder)
               .response);
    fp_locations = fopen(filepath_locations, "w");
    string filepath_sectors;
    strcpy(
        filepath_sectors,
        getFilepathMatchEntity(SECTOR, app_state->filepath_csv, app_state->default_filepath_to_output_folder).response);
    fp_sectors = fopen(filepath_sectors, "w");
    string filepath_sensors;
    strcpy(
        filepath_sensors,
        getFilepathMatchEntity(SENSOR, app_state->filepath_csv, app_state->default_filepath_to_output_folder).response);
    fp_sensors = fopen(filepath_sensors, "w");
    string filepath_inspections;
    strcpy(filepath_inspections,
           getFilepathMatchEntity(INSPECTION, app_state->filepath_csv, app_state->default_filepath_to_output_folder)
               .response);
    fp_inspections = fopen(filepath_inspections, "w");

    fprintf(fp_locations, "id; nome\n");
    fprintf(fp_sectors, "id; nome; id da planta; descricao\n");
    fprintf(fp_sensors, "id; nome; id do setor; tipo do sensor\n");
    fprintf(fp_inspections, "id; id do sensor; Valor da inpecao; Data da inspecao\n");

    t_location *current_location = app_state->database;
    while (current_location != NULL)
    {
        printf("ID: %s - Exportado para .csv\n", current_location->id);
        fprintf(fp_locations, "%s; %s\n", current_location->id, current_location->name);

        t_sector *current_sector = current_location->sectors;

        while (current_sector != NULL)
        {
            printf("ID: %s - Exportado para .csv\n", current_sector->id);
            fprintf(fp_sectors, "%s; %s; %s; %s\n", current_sector->id, current_sector->name,
                    current_sector->location_id, current_sector->description);
            t_sensor *current_sensor = current_sector->sensors;
            while (current_sensor != NULL)
            {
                printf("ID: %s - Exportado para .csv\n", current_sensor->id);
                fprintf(fp_sensors, "%s; %s; %s; %i\n", current_sensor->id, current_sensor->name,
                        current_sensor->sector_id, current_sensor->sensor_type);
                t_inspection *current_inspection = current_sensor->inspections;
                while (current_inspection != NULL)
                {
                    printf("ID: %s - Exportado para .csv\n", current_inspection->id);
                    fprintf(fp_inspections, "%s; %s; %f; %li\n", current_inspection->id, current_inspection->sensor_id,
                            current_inspection->value, current_inspection->date_inspection);
                    current_inspection = current_inspection->next;
                }
                current_sensor = current_sensor->next;
            }
            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }

    fclose(fp_locations);
    fclose(fp_sectors);
    fclose(fp_sensors);
    fclose(fp_inspections);

    printf("Arquivo (%s) gerado com sucesso. \n", filepath_locations);
    printf("Arquivo (%s) gerado com sucesso. \n", filepath_sectors);
    printf("Arquivo (%s) gerado com sucesso. \n", filepath_sensors);
    printf("Arquivo (%s) gerado com sucesso. \n", filepath_inspections);
}
void generateHtmlFile(t_app_state *app_state)
{
    FILE *fp = NULL;

    string complete_path_for_html = "";
    strcat(complete_path_for_html, app_state->default_filepath_to_output_folder);
    strcat(complete_path_for_html, "/");
    strcat(complete_path_for_html, app_state->filepath_html);

    printf("complete_path_for_html: %s \n", complete_path_for_html);

    fp = fopen(complete_path_for_html, "w");

    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<head><meta charset="
                "UTF-8"
                "></head>\n");
    fprintf(fp, "<body>\n");

    fprintf(fp, "<table>\n");
    fprintf(fp, "<caption>Tabela de Plantas</caption>");

    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr>\n");
    fprintf(fp, "<th>Id</th>\n");
    fprintf(fp, "<th>Nome</th>\n");
    fprintf(fp, "</tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");
    t_location *current_location = app_state->database;

    while (current_location != NULL)
    {
        fprintf(fp, "<tr>");
        fprintf(fp, "<td>%s</td>", current_location->id);
        fprintf(fp, "<td>%s</td>", current_location->name);
        fprintf(fp, "</tr>");

        t_sector *current_sector = current_location->sectors;

        current_location = current_location->next;
    }
    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");
    fprintf(fp, "<br><br><br>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<caption>Tabela de setores</caption>");

    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr>\n");
    fprintf(fp, "<th>Id</th>\n");
    fprintf(fp, "<th>Nome</th>\n");
    fprintf(fp, "<th>Id da Planta</th>\n");
    fprintf(fp, "<th>Descrição</th>\n");
    fprintf(fp, "</tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");

    t_location *current_location_sectors = app_state->database;
    while (current_location_sectors != NULL)
    {
        t_sector *current_sector = current_location_sectors->sectors;

        while (current_sector != NULL)
        {

            fprintf(fp, "<tr>");
            fprintf(fp, "<td>%s</td>", current_sector->id);
            fprintf(fp, "<td>%s</td>", current_sector->name);
            fprintf(fp, "<td>%s</td>", current_sector->location_id);
            fprintf(fp, "<td>%s</td>", current_sector->description);
            fprintf(fp, "</tr>");

            current_sector = current_sector->next;
        }

        current_location_sectors = current_location_sectors->next;
    }

    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");
    fprintf(fp, "<br><br><br>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<caption>Tabela de sensores</caption>");

    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr>\n");
    fprintf(fp, "<th>Id</th>\n");
    fprintf(fp, "<th>Nome</th>\n");
    fprintf(fp, "<th>Id do setor</th>\n");
    fprintf(fp, "<th>Tipo do sensor</th>\n");
    fprintf(fp, "<th>Range mínimo</th>\n");
    fprintf(fp, "<th>Range máximo</th>\n");
    fprintf(fp, "</tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");

    t_location *current_location_sensors = app_state->database;
    while (current_location_sensors != NULL)
    {
        t_sector *current_sectors_sensors = current_location_sensors->sectors;

        while (current_sectors_sensors != NULL)
        {
            t_sensor *current_sensor = current_sectors_sensors->sensors;

            while (current_sensor != NULL)
            {
                fprintf(fp, "<tr>");
                fprintf(fp, "<td>%s</td>", current_sensor->id);
                fprintf(fp, "<td>%s</td>", current_sensor->name);
                fprintf(fp, "<td>%s</td>", current_sensor->sector_id);
                fprintf(fp, "<td>%s</td>", mapSensorTypeToString(current_sensor->sensor_type).response);
                fprintf(fp, "<td>%.2f</td>", current_sensor->range_min);
                fprintf(fp, "<td>%.2f</td>", current_sensor->range_max);
                fprintf(fp, "</tr>");

                current_sensor = current_sensor->next;
            }
            current_sectors_sensors = current_sectors_sensors->next;
        }

        current_location_sensors = current_location_sensors->next;
    }

    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");
    fprintf(fp, "<br><br><br>\n");

    fprintf(fp, "<table>\n");
    fprintf(fp, "<caption>Tabela de leituras</caption>");

    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr>\n");
    fprintf(fp, "<th>Id</th>\n");
    fprintf(fp, "<th>Id do sensor</th>\n");
    fprintf(fp, "<th>Valor da leitura</th>\n");
    fprintf(fp, "<th>Data da leitura</th>\n");
    fprintf(fp, "</tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");

    t_location *current_location_inspections = app_state->database;
    while (current_location_inspections != NULL)
    {
        t_sector *current_sensors_inspections = current_location_inspections->sectors;

        while (current_sensors_inspections != NULL)
        {
            t_sensor *sensor_inspections = current_sensors_inspections->sensors;

            while (sensor_inspections != NULL)
            {
                t_inspection *current_inspection = sensor_inspections->inspections;

                while (current_inspection != NULL)
                {

                    fprintf(fp, "<tr>");
                    fprintf(fp, "<td>%s</td>", current_inspection->id);
                    fprintf(fp, "<td>%s</td>", current_inspection->sensor_id);
                    fprintf(fp, "<td>%.2f</td>", current_inspection->value);
                    fprintf(fp, "<td>%s</td>",
                            mapTimestampToString(current_inspection->date_inspection, true).response);
                    fprintf(fp, "</tr>");

                    current_inspection = current_inspection->next;
                }
                sensor_inspections = sensor_inspections->next;
            }
            current_sensors_inspections = current_sensors_inspections->next;
        }

        current_location_inspections = current_location_inspections->next;
    }

    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");

    fclose(fp);
    printf("Arquivo (%s) gerado com sucesso.\n", complete_path_for_html);
}