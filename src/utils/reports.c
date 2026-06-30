#include "../types.h"
#include "../helpers.h"
#include "./reports.h"
#include "../entities/sensors.h"
#include "../entities/sectors.h"
#include "../entities/locations.h"
#include "../entities/inspections.h"

void generateReportsOfSectors(t_location *locations)
{
    int option_output_selection = outputSelectionLog();
    if (option_output_selection == -1)
    {
        printf("Opção digitada é inválida, cancelando a operação. \n");
        return;
    }

    option_output_selection == 1 ? generateReportsOfSectorsFile(locations, "./output/sectors/report.txt")
                                 : generateReportsOfSectorsTerminal(locations);
}
void generateReportsOfSectorsFile(t_location *locations, string filepath)
{
    FILE *file;
    file = fopen(filepath, "w");
    t_location *current_location = locations;
    while (current_location != NULL)
    {
        t_sector *current_sector = current_location->sectors;
        while (current_sector != NULL)
        {

            fprintf(file, "ID: %s\nNome: %s \nDescrição: %s \nQuantidade de sensores: %i \n", current_sector->id,
                    current_sector->name, current_sector->description, countTotalSensors(current_sector->sensors));

            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }
    printf("Arquivo de relatório exportado com sucesso. Caminho: %s. \n", filepath);
    fclose(file);
}
void generateReportsOfSectorsTerminal(t_location *locations)
{
    t_location *current_location = locations;
    while (current_location != NULL)
    {
        t_sector *current_sector = current_location->sectors;
        while (current_sector != NULL)
        {

            printf("\n");
            printf("ID: %s\nNome: %s \nDescrição: %s \nQuantidade de sensores: %i \n", current_sector->id,
                   current_sector->name, current_sector->description, countTotalSensors(current_sector->sensors));
            printf("\n");

            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }
}

void generateReportOfSensors(t_location *locations)
{
    int option_output_selection = outputSelectionLog();
    if (option_output_selection == -1)
    {
        printf("Opção digitada é inválida, cancelando a operação. \n");
        return;
    }

    option_output_selection == 1 ? generateReportOfSensorsFile(locations, "./output/sensors/report.txt")
                                 : generateReportOfSensorsTerminal(locations);
}
void generateReportOfSensorsFile(t_location *locations, string filepath)
{
    FILE *file;
    file = fopen(filepath, "w");
    int option;
    int sensor_type_option;
    printf("Escolha um tipo de relatório: \n");
    printf("0. Geral\n");
    printf("1. Por tipo\n");
    printf("Digite a opção: \n");
    scanf("%i", &option);
    getchar();

    int is_option_valid = option == 0 || option == 1;
    if (!is_option_valid)
    {
        printf("Erro: Opção digitada inválida. \n");
        fclose(file);
        return;
    }

    if (option == 0)
    {
        t_location *current_location = locations;
        while (current_location != NULL)
        {
            t_sector *current_sector = current_location->sectors;
            while (current_sector != NULL)
            {
                t_sensor *current_sensor = current_sector->sensors;
                while (current_sensor != NULL)
                {
                    fprintf(file, "ID: %s\nNome: %s \nTipo: %s \nMin/Max: [%.3f/%.3f] \nTotal de leituras: %i\n",
                            current_sensor->id, current_sensor->name,
                            mapSensorTypeToString(current_sensor->sensor_type).response, current_sensor->range_min,
                            current_sensor->range_max, countTotalInspections(current_sensor->inspections));

                    current_sensor = current_sensor->next;
                }
                current_sector = current_sector->next;
            }
            current_location = current_location->next;
        }
    }
    else
    {
        printf("Qual o tipo do sensor:\n");
        printf("0. TEMPERATURA\n");
        printf("1. VIBRAÇÃO\n");
        printf("2. PRESSÃO\n");
        printf("3. CORRENTE\n");
        printf("4. UMIDADE\n");
        printf("Digite a opção: \n");

        scanf("%i", &sensor_type_option);
        getchar();

        t_location *current_location = locations;
        while (current_location != NULL)
        {
            t_sector *current_sector = current_location->sectors;
            while (current_sector != NULL)
            {
                t_sensor *current_sensor = current_sector->sensors;
                while (current_sensor != NULL)
                {
                    if (sensor_type_option == current_sensor->sensor_type)
                    {
                        fprintf(file, "ID: %s\nNome: %s \nTipo: %s \nMin/Max: [%.3f/%.3f] \nTotal de leituras: %i\n",
                                current_sensor->id, current_sensor->name,
                                mapSensorTypeToString(current_sensor->sensor_type).response, current_sensor->range_min,
                                current_sensor->range_max, countTotalInspections(current_sensor->inspections));
                    }

                    current_sensor = current_sensor->next;
                }
                current_sector = current_sector->next;
            }
            current_location = current_location->next;
        }
    }
    fclose(file);
}
void generateReportOfSensorsTerminal(t_location *locations)
{
    int option;
    int sensor_type_option;
    printf("Escolha um tipo de relatório: \n");
    printf("0. Geral\n");
    printf("1. Por tipo\n");
    printf("Digite a opção: \n");
    scanf("%i", &option);
    getchar();

    int is_option_valid = option == 0 || option == 1;
    if (!is_option_valid)
    {
        printf("Erro: Opção digitada inválida. \n");
        return;
    }

    if (option == 0)
    {
        t_location *current_location = locations;
        while (current_location != NULL)
        {
            t_sector *current_sector = current_location->sectors;
            while (current_sector != NULL)
            {
                t_sensor *current_sensor = current_sector->sensors;
                while (current_sensor != NULL)
                {
                    printf("\n");
                    printf("ID: %s\nNome: %s \nTipo: %s \nMin/Max: [%.3f/%.3f] \nTotal de leituras: %i\n",
                           current_sensor->id, current_sensor->name,
                           mapSensorTypeToString(current_sensor->sensor_type).response, current_sensor->range_min,
                           current_sensor->range_max, countTotalInspections(current_sensor->inspections));
                    printf("\n");

                    current_sensor = current_sensor->next;
                }
                current_sector = current_sector->next;
            }
            current_location = current_location->next;
        }
    }
    else
    {
        printf("Qual o tipo do sensor:\n");
        printf("0. TEMPERATURA\n");
        printf("1. VIBRAÇÃO\n");
        printf("2. PRESSÃO\n");
        printf("3. CORRENTE\n");
        printf("4. UMIDADE\n");
        printf("Digite a opção: \n");

        scanf("%i", &sensor_type_option);
        getchar();

        t_location *current_location = locations;
        while (current_location != NULL)
        {
            t_sector *current_sector = current_location->sectors;
            while (current_sector != NULL)
            {
                t_sensor *current_sensor = current_sector->sensors;
                while (current_sensor != NULL)
                {
                    if (sensor_type_option == current_sensor->sensor_type)
                    {
                        printf("\n");
                        printf("ID: %s\nNome: %s \nTipo: %s \nMin/Max: [%.3f/%.3f] \nTotal de leituras: %i\n",
                               current_sensor->id, current_sensor->name,
                               mapSensorTypeToString(current_sensor->sensor_type).response, current_sensor->range_min,
                               current_sensor->range_max, countTotalInspections(current_sensor->inspections));
                        printf("\n");
                    }

                    current_sensor = current_sensor->next;
                }
                current_sector = current_sector->next;
            }
            current_location = current_location->next;
        }
    }
}

void generateReportOfInspections(t_location *locations)
{

    int option_output_selection = outputSelectionLog();
    if (option_output_selection == -1)
    {
        printf("Opção digitada é inválida, cancelando a operação. \n");
        return;
    }

    option_output_selection == 1 ? generateReportOfInspectionsFile(locations, "./output/inspections/report.txt")
                                 : generateReportOfInspectionsTerminal(locations);
}
void generateReportOfInspectionsFile(t_location *locations, string filepath)
{

    FILE *file;
    file = fopen(filepath, "w");

    int option;
    printf("Escolha uma opção: \n");
    printf("0. Por Todos os locais. \n");
    printf("1. Por local. \n");
    printf("Digite a opção: \n");
    scanf("%i", &option);

    int is_option_valid = option == 0 || option == 1;
    if (!is_option_valid)
    {
        printf("Erro: Opção digitada inválida. \n");
        fclose(file);
        return;
    }

    if (option == 0)
    {
        t_location *current_location = locations;
        while (current_location != NULL)
        {
            t_sector *current_sector = current_location->sectors;
            while (current_sector != NULL)
            {
                t_sensor *current_sensor = current_sector->sensors;
                while (current_sensor != NULL)
                {
                    t_inspection *current_inspection = current_sensor->inspections;
                    while (current_inspection != NULL)
                    {
                        fprintf(file,
                                "ID: %s\nPlanta: %s\nSetor: %s\nSensor: %s\nValor da "
                                "leitura: %.2f "
                                "%s\nData: %s. \n",
                                current_inspection->id, current_location->name, current_sector->name,
                                current_sensor->name, current_inspection->value,
                                mapSensorTypeUnitToString(current_sensor->sensor_type).response,
                                mapTimestampToString(current_inspection->date_inspection, true).response);
                        current_inspection = current_inspection->next;
                    }
                    current_sensor = current_sensor->next;
                }
                current_sector = current_sector->next;
            }
            current_location = current_location->next;
        }
    }
    else
    {
        int option_location_idx;
        printf("Escolha um local. \n");
        listAllLocations(locations);
        printf("Digite a opção: \n");
        scanf("%i", &option_location_idx);
        getchar();
        t_location *current_location = locations;
        t_location *location_found = findLocationByIdx(locations, option_location_idx);
        if (location_found == NULL)
        {
            printf("Erro ao realizar relatório. \n");
            fclose(file);
            return;
        }

        while (current_location != NULL)
        {
            if (strcmp(current_location->id, location_found->id) == 0)
            {
                t_sector *current_sector = current_location->sectors;
                while (current_sector != NULL)
                {
                    t_sensor *current_sensor = current_sector->sensors;
                    while (current_sensor != NULL)
                    {
                        t_inspection *current_inspection = current_sensor->inspections;
                        while (current_inspection != NULL)
                        {
                            fprintf(file,
                                    "ID: %s\nPlanta: %s\nSetor: %s\nSensor: %s\nValor da "
                                    "leitura: %.2f "
                                    "%s\nData: %s. \n",
                                    current_inspection->id, current_location->name, current_sector->name,
                                    current_sensor->name, current_inspection->value,
                                    mapSensorTypeUnitToString(current_sensor->sensor_type).response,
                                    mapTimestampToString(current_inspection->date_inspection, true).response);
                            current_inspection = current_inspection->next;
                        }
                        current_sensor = current_sensor->next;
                    }
                    current_sector = current_sector->next;
                }
                break;
            };
            current_location = current_location->next;
        }
    }
    fclose(file);
}
void generateReportOfInspectionsTerminal(t_location *locations)
{

    int option;
    printf("Escolha uma opção: \n");
    printf("0. Por Todos os locais. \n");
    printf("1. Por local. \n");
    printf("Digite a opção: \n");
    scanf("%i", &option);

    int is_option_valid = option == 0 || option == 1;
    if (!is_option_valid)
    {
        printf("Erro: Opção digitada inválida. \n");
        return;
    }

    if (option == 0)
    {
        t_location *current_location = locations;
        while (current_location != NULL)
        {
            t_sector *current_sector = current_location->sectors;
            while (current_sector != NULL)
            {
                t_sensor *current_sensor = current_sector->sensors;
                while (current_sensor != NULL)
                {
                    t_inspection *current_inspection = current_sensor->inspections;
                    while (current_inspection != NULL)
                    {
                        printf("\n");
                        printf("Planta: %s\nSetor: %s\nSensor: %s\nValor da "
                               "leitura: %.2f "
                               "%s\nData: %s. \n",
                               current_location->name, current_sector->name, current_sensor->name,
                               current_inspection->value,
                               mapSensorTypeUnitToString(current_sensor->sensor_type).response,
                               mapTimestampToString(current_inspection->date_inspection, true).response);
                        printf("\n");
                        current_inspection = current_inspection->next;
                    }
                    current_sensor = current_sensor->next;
                }
                current_sector = current_sector->next;
            }
            current_location = current_location->next;
        }
    }
    else
    {
        int option_location_idx;
        printf("Escolha um local. \n");
        listAllLocations(locations);
        printf("Digite a opção: \n");
        scanf("%i", &option_location_idx);
        getchar();
        t_location *current_location = locations;
        t_location *location_found = findLocationByIdx(locations, option_location_idx);
        if (location_found == NULL)
        {
            printf("Erro ao realizar relatório. \n");
            return;
        }

        while (current_location != NULL)
        {
            if (strcmp(current_location->id, location_found->id) == 0)
            {
                t_sector *current_sector = current_location->sectors;
                while (current_sector != NULL)
                {
                    t_sensor *current_sensor = current_sector->sensors;
                    while (current_sensor != NULL)
                    {
                        t_inspection *current_inspection = current_sensor->inspections;
                        while (current_inspection != NULL)
                        {
                            printf("\n");
                            printf("Planta: %s\nSetor: %s\nSensor: %s\nValor da "
                                   "leitura: %.2f "
                                   "%s\nData: %s. \n",
                                   current_location->name, current_sector->name, current_sensor->name,
                                   current_inspection->value,
                                   mapSensorTypeUnitToString(current_sensor->sensor_type).response,
                                   mapTimestampToString(current_inspection->date_inspection, true).response);
                            printf("\n");
                            current_inspection = current_inspection->next;
                        }
                        current_sensor = current_sensor->next;
                    }
                    current_sector = current_sector->next;
                }
                break;
            };
            current_location = current_location->next;
        }
    }
}

void generateReportOfInspectionsAverage(t_location *locations)
{
    int option_output_selection = outputSelectionLog();
    if (option_output_selection == -1)
    {
        printf("Opção digitada é inválida, cancelando a operação. \n");
        return;
    }

    option_output_selection == 1
        ? generateReportOfInspectionsAverageFile(locations, "./output/inspections/report_average.txt")
        : generateReportOfInspectionsAverageTerminal(locations);
};
void generateReportOfInspectionsAverageFile(t_location *locations, string filepath)
{
    FILE *file;
    file = fopen(filepath, "w");

    t_location *current_location = locations;
    while (current_location != NULL)
    {
        t_sector *current_sector = current_location->sectors;
        while (current_sector != NULL)
        {
            t_sensor *current_sensor = current_sector->sensors;

            while (current_sensor != NULL)
            {
                t_inspection *current_inspection = current_sensor->inspections;
                float counter_sum_values = 0.0;

                while (current_inspection != NULL)
                {
                    counter_sum_values = counter_sum_values + current_inspection->value;
                    current_inspection = current_inspection->next;
                }
                if (countTotalInspections(current_sensor->inspections) > 0)
                {
                    fprintf(file, "Planta: %s\nSetor: %s\nSensor: %s\nMédia: %.2f %s.\n", current_location->name,
                            current_sector->name, current_sensor->name,
                            counter_sum_values / (float)countTotalInspections(current_sensor->inspections),
                            mapSensorTypeUnitToString(current_sensor->sensor_type).response);
                }
                current_sensor = current_sensor->next;
            }
            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }

    fclose(file);
}
void generateReportOfInspectionsAverageTerminal(t_location *locations)
{
    t_location *current_location = locations;
    while (current_location != NULL)
    {
        t_sector *current_sector = current_location->sectors;
        while (current_sector != NULL)
        {
            t_sensor *current_sensor = current_sector->sensors;

            while (current_sensor != NULL)
            {
                t_inspection *current_inspection = current_sensor->inspections;
                float counter_sum_values = 0.0;

                while (current_inspection != NULL)
                {
                    counter_sum_values = counter_sum_values + current_inspection->value;
                    current_inspection = current_inspection->next;
                }
                if (countTotalInspections(current_sensor->inspections) > 0)
                {
                    printf("\n");
                    printf("Planta: %s \n", current_location->name);
                    printf("  Setor: %s\n", current_sector->name);
                    printf("    Sensor: %s\n", current_sensor->name);
                    printf("       Média: %.2f %s. \n",
                           counter_sum_values / (float)countTotalInspections(current_sensor->inspections),
                           mapSensorTypeUnitToString(current_sensor->sensor_type).response);
                    printf("\n");
                }
                else
                {
                    printf("- O sensor: %s ainda não possui leituras.\n", current_sensor->name);
                }
                current_sensor = current_sensor->next;
            }
            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }
}

void generateReportOfInspectionsVariation(t_location *locations)
{
    int option_output_selection = outputSelectionLog();
    if (option_output_selection == -1)
    {
        printf("Opção digitada é inválida, cancelando a operação. \n");
        return;
    }

    option_output_selection == 1
        ? generateReportOfInspectionsVariationFile(locations, "./output/inspections/report_variation.txt")
        : generateReportOfInspectionsVariationTerminal(locations);
}
void generateReportOfInspectionsVariationFile(t_location *locations, string filepath)
{
    FILE *file;
    file = fopen(filepath, "w");
    int option;
    printf("Escolha um tipo de relatório: \n");
    printf("0. Por Setor\n");
    printf("1. Por Sensor\n");
    printf("Digite a opção: \n");
    scanf("%i", &option);

    int is_option_valid = option == 0 || option == 1;
    if (!is_option_valid)
    {
        printf("Erro: Opção digitada inválida. \n");
        fclose(file);
        return;
    }

    t_location *location_found = promptAndFindLocationByIdx(locations);
    if (!location_found)
    {
        printf("Não foi possível encontrar sua planta. \n");
        fclose(file);
        return;
    }
    printf("Planta: %s \n", location_found->name);
    t_sector *sector_found = promptAndFindSectorByIdx(location_found->sectors);
    if (!sector_found)
    {
        printf("Não foi possível encontrar seu setor. \n");
        fclose(file);
        return;
    }
    printf("Setor: %s \n", sector_found->name);
    if (option == 0)
    {

        t_sensor *sensor_found = sector_found->sensors;
        while (sensor_found != NULL)
        {
            t_inspection *inspection_found = sensor_found->inspections;
            while (inspection_found != NULL)
            {
                t_inspection *inspection_found_next = inspection_found->next;
                while (inspection_found_next != NULL)
                {
                    if (checkIfIsTheSameDay(inspection_found->date_inspection, inspection_found_next->date_inspection))
                    {
                        t_inspection *first_inspection_of_the_day;
                        t_inspection *second_inspection_of_the_day;
                        t_string object_date = mapTimestampToString(inspection_found->date_inspection, false);

                        if (inspection_found->date_inspection <= inspection_found_next->date_inspection)
                        {
                            first_inspection_of_the_day = inspection_found;
                            second_inspection_of_the_day = inspection_found_next;
                        }
                        else
                        {
                            first_inspection_of_the_day = inspection_found_next;
                            second_inspection_of_the_day = inspection_found;
                        }

                        float variation_between_values =
                            second_inspection_of_the_day->value - first_inspection_of_the_day->value;

                        fprintf(file,
                                "Planta: %s\nSetor: %s\nSensor: %s\nData: %s -> Variação do sensor: %.2f %s.\n"
                                "Primeira leitura do dia: %.2f %s -> última leitura do dia: %.2f %s.\n",
                                location_found->name, sector_found->name, sensor_found->name, object_date.response,
                                variation_between_values, mapSensorTypeUnitToString(sensor_found->sensor_type).response,
                                first_inspection_of_the_day->value,
                                mapSensorTypeUnitToString(sensor_found->sensor_type).response,
                                second_inspection_of_the_day->value,
                                mapSensorTypeUnitToString(sensor_found->sensor_type).response);
                    }
                    inspection_found_next = inspection_found_next->next;
                }
                inspection_found = inspection_found->next;
            }
            sensor_found = sensor_found->next;
        }
    }
    else
    {
        t_sensor *sensor_found = promptAndFindSensorByIdx(sector_found->sensors);
        if (!sensor_found)
        {
            printf("Não foi possível encontrar seu sensor. \n");
            return;
        }
        printf("Sensor: %s \n", sensor_found->name);

        t_inspection *inspection_found = sensor_found->inspections;
        while (inspection_found != NULL)
        {
            t_inspection *inspection_found_next = inspection_found->next;
            while (inspection_found_next != NULL)
            {
                if (checkIfIsTheSameDay(inspection_found->date_inspection, inspection_found_next->date_inspection))
                {
                    t_inspection *first_inspection_of_the_day;
                    t_inspection *second_inspection_of_the_day;
                    t_string object_date = mapTimestampToString(inspection_found->date_inspection, false);

                    if (inspection_found->date_inspection <= inspection_found_next->date_inspection)
                    {
                        first_inspection_of_the_day = inspection_found;
                        second_inspection_of_the_day = inspection_found_next;
                    }
                    else
                    {
                        first_inspection_of_the_day = inspection_found_next;
                        second_inspection_of_the_day = inspection_found;
                    }

                    float variation_between_values =
                        second_inspection_of_the_day->value - first_inspection_of_the_day->value;

                    fprintf(file,
                            "Planta: %s \nSetor: %s \nSensor: %s\n Data: %s -> Variação do sensor: %.2f %s.\n"
                            "Primeira leitura do dia: %.2f %s -> última leitura do dia: %.2f %s.\n",
                            location_found->name, sector_found->name, sensor_found->name, object_date.response,
                            variation_between_values, mapSensorTypeUnitToString(sensor_found->sensor_type).response,
                            first_inspection_of_the_day->value,
                            mapSensorTypeUnitToString(sensor_found->sensor_type).response,
                            second_inspection_of_the_day->value,
                            mapSensorTypeUnitToString(sensor_found->sensor_type).response);
                }
                inspection_found_next = inspection_found_next->next;
            }
            inspection_found = inspection_found->next;
        }
    }
    fclose(file);
}
void generateReportOfInspectionsVariationTerminal(t_location *locations)
{
    int option;
    printf("Escolha um tipo de relatório: \n");
    printf("0. Por Setor\n");
    printf("1. Por Sensor\n");
    printf("Digite a opção: \n");
    scanf("%i", &option);

    int is_option_valid = option == 0 || option == 1;
    if (!is_option_valid)
    {
        printf("Erro: Opção digitada inválida. \n");
        return;
    }

    t_location *location_found = promptAndFindLocationByIdx(locations);
    if (!location_found)
    {
        printf("Não foi possível encontrar sua planta. \n");
        return;
    }
    printf("Planta: %s \n", location_found->name);
    t_sector *sector_found = promptAndFindSectorByIdx(location_found->sectors);
    if (!sector_found)
    {
        printf("Não foi possível encontrar seu setor. \n");
        return;
    }
    printf("Setor: %s \n", sector_found->name);
    if (option == 0)
    {

        t_sensor *sensor_found = sector_found->sensors;
        while (sensor_found != NULL)
        {
            t_inspection *inspection_found = sensor_found->inspections;
            while (inspection_found != NULL)
            {
                t_inspection *inspection_found_next = inspection_found->next;
                while (inspection_found_next != NULL)
                {
                    if (checkIfIsTheSameDay(inspection_found->date_inspection, inspection_found_next->date_inspection))
                    {
                        t_inspection *first_inspection_of_the_day;
                        t_inspection *second_inspection_of_the_day;
                        t_string object_date = mapTimestampToString(inspection_found->date_inspection, false);

                        if (inspection_found->date_inspection <= inspection_found_next->date_inspection)
                        {
                            first_inspection_of_the_day = inspection_found;
                            second_inspection_of_the_day = inspection_found_next;
                        }
                        else
                        {
                            first_inspection_of_the_day = inspection_found_next;
                            second_inspection_of_the_day = inspection_found;
                        }

                        float variation_between_values =
                            second_inspection_of_the_day->value - first_inspection_of_the_day->value;

                        printf("\n");

                        printf("Planta: %s \n", location_found->name);
                        printf("  Setor: %s \n", sector_found->name);
                        printf("    Sensor: %s \n", sensor_found->name);
                        printf("      Data: %s -> Variação do sensor: %.2f %s.\n", object_date.response,
                               variation_between_values, mapSensorTypeUnitToString(sensor_found->sensor_type).response);
                        printf("        Primeira leitura do dia: %.2f %s -> última leitura do dia: %.2f %s.\n",
                               first_inspection_of_the_day->value,
                               mapSensorTypeUnitToString(sensor_found->sensor_type).response,
                               second_inspection_of_the_day->value,
                               mapSensorTypeUnitToString(sensor_found->sensor_type).response);
                        printf("\n");
                    }
                    inspection_found_next = inspection_found_next->next;
                }
                inspection_found = inspection_found->next;
            }
            sensor_found = sensor_found->next;
        }
    }
    else
    {
        t_sensor *sensor_found = promptAndFindSensorByIdx(sector_found->sensors);
        if (!sensor_found)
        {
            printf("Não foi possível encontrar seu sensor. \n");
            return;
        }
        printf("Sensor: %s \n", sensor_found->name);

        t_inspection *inspection_found = sensor_found->inspections;
        while (inspection_found != NULL)
        {
            t_inspection *inspection_found_next = inspection_found->next;
            while (inspection_found_next != NULL)
            {
                if (checkIfIsTheSameDay(inspection_found->date_inspection, inspection_found_next->date_inspection))
                {
                    t_inspection *first_inspection_of_the_day;
                    t_inspection *second_inspection_of_the_day;
                    t_string object_date = mapTimestampToString(inspection_found->date_inspection, false);

                    if (inspection_found->date_inspection <= inspection_found_next->date_inspection)
                    {
                        first_inspection_of_the_day = inspection_found;
                        second_inspection_of_the_day = inspection_found_next;
                    }
                    else
                    {
                        first_inspection_of_the_day = inspection_found_next;
                        second_inspection_of_the_day = inspection_found;
                    }

                    float variation_between_values =
                        second_inspection_of_the_day->value - first_inspection_of_the_day->value;

                    printf("\n");

                    printf("Planta: %s \n", location_found->name);
                    printf("  Setor: %s \n", sector_found->name);
                    printf("    Sensor: %s \n", sensor_found->name);
                    printf("      Data: %s -> Variação do sensor: %.2f %s.\n", object_date.response,
                           variation_between_values, mapSensorTypeUnitToString(sensor_found->sensor_type).response);
                    printf("        Primeira leitura do dia: %.2f %s -> última leitura do dia: %.2f %s.\n",
                           first_inspection_of_the_day->value,
                           mapSensorTypeUnitToString(sensor_found->sensor_type).response,
                           second_inspection_of_the_day->value,
                           mapSensorTypeUnitToString(sensor_found->sensor_type).response);
                    printf("\n");
                }
                inspection_found_next = inspection_found_next->next;
            }
            inspection_found = inspection_found->next;
        }
    }
}

int outputSelectionLog()
{
    int option;
    printf("Digite a opção de saída do relatório: \n");
    printf("1. Exibir em arquivo (Exporta arquivo .txt) \n");
    printf("2. Exibir no terminal (log) \n");
    printf(":: \n");
    scanf("%i", &option);
    if (option == 1 || option == 2)
    {
        return option;
    }
    option = -1;
    return option;
}