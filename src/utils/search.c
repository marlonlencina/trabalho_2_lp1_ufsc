#include "../types.h"
#include "../helpers.h"
#include "./search.h"
#include "../entities/sectors.h"
#include "../entities/sensors.h"
#include "../entities/inspections.h"

void searchForSectorDescription(t_location *locations)
{
    string description;
    printf("Digite uma descrição de um setor:\n");
    fgets(description, MAX_STRING_SIZE, stdin);
    formatStringToSystemPattern(description);

    t_location *current_location = locations;
    while (current_location != NULL)
    {
        t_sector *current_sector = current_location->sectors;
        while (current_sector != NULL)
        {
            if (strcmp(description, current_sector->description) == 0)
            {
                printf("Resultado da busca: \n");
                printf("ID: %s\nID (PLANTA VINCULADA): %s\nNome: %s \nDescrição: %s \nQuantidade de "
                       "sensores: %i\n",
                       current_sector->id, current_sector->location_id, current_sector->name, current_sector->description,
                       countTotalSensors(current_sector->sensors));
                printf("\n");
            }
            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }
}

//Caso base: se o ponteiro for NULL, o elemento não foi encontrado.
//Caso de sucesso: se o nó atual contém o valor procurado, retorna esse nó.
//Passo recursivo: chama a função para o próximo nó da lista.

void searchForSensorType(t_location *locations)
{
    int sensor_type_option;
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
                    printf("Resultado da busca: \n");
                    printf("ID: %s \nNome: %s \nTipo: %s \nMin/Max:[%.3f/%.3f] "
                           "\nTotal "
                           "de leituras: %i\n",
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
