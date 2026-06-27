#include "sensors.h"
#include "../global_config.h"
#include "inspections.h"

t_sensor *createNewSensor(t_sector *sector_selected_pointer)
{
    printf("Digite o número correspondente ao tipo de sensor: \n");
    printf("0. TEMPERATURA - °C \n");
    printf("1. VIBRAÇÃO - mm/s \n");
    printf("2. PRESSÃO - PSI \n");
    printf("3. CORRENTE - A\n");
    printf("4. UMIDADE - %% \n");
    int number_typed;
    scanf("%i", &number_typed);
    getchar();

    if (number_typed < 0 || number_typed > 4)
    {
        printf("Erro: você não digitou um número válido para o tipo do sensor. "
               "\n");
        return NULL;
    }

    t_sensor_template template = getSensorTemplate(number_typed);

    t_sensor *new_sensor = (t_sensor *)malloc(sizeof(t_sensor));
    string unique_id;
    generateUniqueId(unique_id, SENSOR);
    strcpy(new_sensor->id, unique_id);
    strcpy(new_sensor->name, template.name);
    strcpy(new_sensor->sector_id, sector_selected_pointer->id);

    new_sensor->sensor_type = number_typed;
    new_sensor->range_min = template.range_min;
    new_sensor->range_max = template.range_max;
    new_sensor->inspections = NULL;

    printf("Sensor '%s' vinculado ao setor com sucesso. \n", new_sensor->name);

    return new_sensor;
};
void insertNewSensorAtDatabase(t_sensor **list_sensors, t_sensor *new_sensor)
{
    if (list_sensors == NULL)
    {
        new_sensor->next = NULL;
    }
    else
    {
        new_sensor->next = *list_sensors;
    }
    *list_sensors = new_sensor;
    printf("Novo sensor foi inserido com sucesso.\n-> ID: %s, Nome: %s. \n", new_sensor->id, new_sensor->name);
}
void deleteSensorAtDatabase(t_sensor **list_sensors, string sensor_id)
{
    if (*list_sensors == NULL)
    {
        printf("Não existem sensores. \n");
        return;
    }

    t_sensor *current_location = *list_sensors;
    t_sensor *temp;

    t_sensor *sensor_to_delete = findSensorById(*list_sensors, sensor_id);

    if (sensor_to_delete == NULL)
    {
        printf("Erro ao deletar sensor -> Sensor não encontrado. \n");
        return;
    }

    // primeiro nó
    if (current_location == sensor_to_delete)
    {
        *list_sensors = current_location->next;
        free(current_location);
        printf("Sensor deletado com sucesso. \n");
        return;
    }

    // nao é o primero nó, encontra o anterior
    while (current_location->next != NULL && current_location->next != sensor_to_delete)
    {
        current_location = current_location->next;
    }

    if (current_location->next != NULL)
    {
        temp = current_location->next;
        current_location->next = temp->next;
        free(temp);
    }
    printf("Sensor deletado com sucesso. \n");
};
void listAllSensors(t_sensor *list_sensors)
{
    int initial_idx = 1;
    int counter = 0;
    while (list_sensors != NULL)
    {
        printf("[IDX:  %i] -> [ID: %s, Nome: %s, Total de inspeções: %i]. \n", initial_idx, list_sensors->id,
               list_sensors->name, countTotalInspections(list_sensors->inspections));

        list_sensors = list_sensors->next;
        counter++, initial_idx++;
    }
    printf("Total de sensores: %i.\n\n", counter);
}
void selectSensor(t_sensor *sensor, t_sensor **sensor_selected_pointer)
{
    *sensor_selected_pointer = sensor;
};
t_sensor *findSensorById(t_sensor *list_sensors, string sensor_id)
{
    t_sensor *copy_list_sensors = list_sensors;

    while (copy_list_sensors != NULL && strcmp(copy_list_sensors->id, sensor_id) != 0)
    {
        copy_list_sensors = copy_list_sensors->next;
    }
    return copy_list_sensors;
}
t_sensor *findSensorByIdx(t_sensor *list_sensors, int idx)
{
    t_sensor *copy_list_sensors = list_sensors;

    int initial_idx = 1;
    while (copy_list_sensors != NULL)
    {
        if (initial_idx == idx)
            return copy_list_sensors;
        copy_list_sensors = copy_list_sensors->next;
        initial_idx++;
    }
    return NULL;
}
t_sensor *promptAndFindSensorByIdx(t_sensor *list_sensors)
{
    t_sensor *sensor_found = NULL;
    int total_sensors = countTotalSensors(list_sensors);
    if (total_sensors < 1)
    {
        printf("Sem sensores existentes. \n");
        return sensor_found;
    }
    listAllSensors(list_sensors);
    int sensor_idx;
    printf("Digite o índice do sensor: \n");
    printf(":: \n");
    scanf("%i", &sensor_idx);
    sensor_found = findSensorByIdx(list_sensors, sensor_idx);
    if (sensor_found == NULL)
    {
        printf("Erro ao encontrar sensor. \n");
    }
    return sensor_found;
}
t_sensor_template getSensorTemplate(t_sensor_types sensor_type)
{
    t_sensor_template SENSOR_TEMPLATES[] = {
        [TEMPERATURE] = {"SENSOR DE TEMPERATURA", -20.0, 80.0}, [VIBRATION] = {"SENSOR DE VIBRACAO", 0.0, 50.0},
        [PRESSURE] = {"SENSOR DE PRESSAO", 0.0, 200.0},         [CURRENT] = {"SENSOR DE CORRENTE", 0.0, 100.0},
        [HUMIDITY] = {"SENSOR DE UMIDADE", 0.0, 100.0},
    };
    t_sensor_template template = SENSOR_TEMPLATES[sensor_type];
    return template;
}
int countTotalSensors(t_sensor *list_sensors)
{
    t_sensor *current_sensor = list_sensors;
    int counter = 0;
    while (current_sensor != NULL)
    {
        counter++;
        current_sensor = current_sensor->next;
    }
    return counter;
}
