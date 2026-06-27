#include "../types.h"
#include "../helpers.h"
#include "./reports.h"
#include "../entities/sensors.h"
#include "../entities/sectors.h"
#include "../entities/locations.h"
#include "../entities/inspections.h"


void generateReportsOfSectors(t_location *locations)
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
                    if (countTotalInspections(current_sensor->inspections) > 0)
                    {
                        printf("\n");
                        printf("Planta: %s \n", current_location->name);
                        printf("  Setor: %s\n", current_sector->name);
                        printf("    Sensor: %s\n", current_sensor->name);
                        printf("       Média: %.4f %s. \n",
                               counter_sum_values / (float)countTotalInspections(current_sensor->inspections),
                               mapSensorTypeUnitToString(current_sensor->sensor_type).response);
                        printf("\n");
                    }
                    else
                    {
                        printf("- O sensor: %s ainda não possui leituras.\n", current_sensor->name);
                    }
                    current_inspection = current_inspection->next;
                }
                current_sensor = current_sensor->next;
            }
            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }
};
void generateReportOfInspectionsVariation(t_location *locations)
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
    }
    printf("Planta: %s \n", location_found->name);
    t_sector *sector_found = promptAndFindSectorByIdx(location_found->sectors);
    if (!sector_found)
    {
        printf("Não foi possível encontrar seu setor. \n");
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
                    printf("\n");
                }
                inspection_found_next = inspection_found_next->next;
            }
            inspection_found = inspection_found->next;
        }
    }
};