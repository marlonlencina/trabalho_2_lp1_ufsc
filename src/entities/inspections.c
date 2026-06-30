#include "inspections.h"
#include "../global_config.h"
#include "../helpers.h"
#include "sensors.h"

t_inspection *createNewInspection(t_sensor *sensor_selected_pointer)
{
    t_inspection *new_inspection = NULL;
    new_inspection = (t_inspection *)malloc(sizeof(t_inspection));
    string unique_id;
    generateUniqueId(unique_id, INSPECTION);
    strcpy(new_inspection->id, unique_id);

    time_t date;
    time(&date);
    new_inspection->date_inspection = date;

    int quantityOfInspectionsOnThisDay = checkQuantityOfInspectionsOnDate(date, sensor_selected_pointer);
    if (quantityOfInspectionsOnThisDay >= 2)
    {
        printf("\nErro: Você não pode gerar mais de duas leituras no mesmo dia \n\n");
        new_inspection = NULL;
        return new_inspection;
    }

    strcpy(new_inspection->sensor_id, sensor_selected_pointer->id);

    printf("Digite o valor da leitura (%.2f-%.2f): \n", sensor_selected_pointer->range_min,
           sensor_selected_pointer->range_max);
    scanf("%f", &new_inspection->value);
    getchar();

    if (new_inspection->value < sensor_selected_pointer->range_min ||
        new_inspection->value > sensor_selected_pointer->range_max)
    {
        printf("Range mínimo (%.2f) e o Range máximo (%.2f).\n", sensor_selected_pointer->range_min,
               sensor_selected_pointer->range_max);

        printf("Erro: Você precisa gerar um valor entre o Range mínimo e o range máximo \n");
        confirmAndClear();
        new_inspection = NULL;
        return new_inspection;
    }

    printf("Nova leitura foi cadastrada com sucesso. \n");
    return new_inspection;
};
void insertNewInspectionAtDatabase(t_inspection **list_inspections, t_inspection *new_inspection)
{
    if (list_inspections == NULL)
    {
        new_inspection->next = NULL;
    }
    else
    {
        new_inspection->next = *list_inspections;
    }
    *list_inspections = new_inspection;
    printf("Nova leitura foi inserido com sucesso.\n-> ID: %s, Valor: %.2f. \n", new_inspection->id,
           new_inspection->value);
}
void deleteInspectionAtDatabase(t_inspection **list_inspections, string inspection_id)
{
    if (*list_inspections == NULL)
    {
        printf("Não existem leituras. \n");
        return;
    }

    t_inspection *current_location = *list_inspections;
    t_inspection *temp;

    t_inspection *inspection_to_delete = findInspectionById(*list_inspections, inspection_id);

    if (inspection_to_delete == NULL)
    {
        printf("Erro ao deletar leitura -> Leitura não encontrada. \n");
        return;
    }

    // primeiro nó
    if (current_location == inspection_to_delete)
    {
        *list_inspections = current_location->next;
        free(current_location);
        printf("Leitura deletada com sucesso. \n");
        return;
    }

    // nao é o primero nó, encontra o anterior
    while (current_location->next != NULL && current_location->next != inspection_to_delete)
    {
        current_location = current_location->next;
    }

    if (current_location->next != NULL)
    {
        temp = current_location->next;
        current_location->next = temp->next;
        free(temp);
    }

    printf("Leitura deletada com sucesso. \n");
};
void listAllInspections(t_inspection *list_inspections)
{
    int initial_idx = 1;
    int counter = 0;
    while (list_inspections != NULL)
    {
        printf("[IDX:  %i] -> [ID: %s, Valor: %.2f, Data: %s]. \n", initial_idx, list_inspections->id,
               list_inspections->value, mapTimestampToString(list_inspections->date_inspection, true).response);

        list_inspections = list_inspections->next;
        counter++, initial_idx++;
    }
    printf("Total de leituras encontradas: %i.\n\n", counter);
}
void selectInspection(t_inspection *inspection, t_inspection **inspection_selected_pointer)
{
    *inspection_selected_pointer = inspection;
};
t_inspection *findInspectionById(t_inspection *list_inspections, string inspection_id)
{
    t_inspection *copy_list_sensors = list_inspections;

    while (copy_list_sensors != NULL && strcmp(copy_list_sensors->id, inspection_id) != 0)
    {
        copy_list_sensors = copy_list_sensors->next;
    }
    return copy_list_sensors;
}
t_inspection *findInspectionByIdx(t_inspection *list_inspections, int idx)
{
    t_inspection *copy_list_inspections = list_inspections;

    int initial_idx = 1;
    while (copy_list_inspections != NULL)
    {
        if (initial_idx == idx)
            return copy_list_inspections;
        copy_list_inspections = copy_list_inspections->next;
        initial_idx++;
    }
    return NULL;
}
t_inspection *promptAndFindInspectionByIdx(t_inspection *list_inspections)
{
    t_inspection *inspection_found = NULL;
    int total_inspections = countTotalInspections(list_inspections);
    if (total_inspections < 1)
    {
        printf("Sem leituras existentes. \n");
        return inspection_found;
    }
    listAllInspections(list_inspections);
    int inspection_idx;
    printf("Digite o índice da leitura: \n");
    printf(":: \n");
    scanf("%i", &inspection_idx);
    inspection_found = findInspectionByIdx(list_inspections, inspection_idx);
    if (inspection_found == NULL)
    {
        printf("Erro ao encontrar leitura. \n");
    }
    return inspection_found;
}
int countTotalInspections(t_inspection *list_inspections)
{
    t_inspection *current_inspection = list_inspections;
    int counter = 0;
    while (current_inspection != NULL)
    {
        counter++;
        current_inspection = current_inspection->next;
    }
    return counter;
}
void updateSensorRange(t_sensor *sensor_selected_pointer)
{

    float range_min_default = sensor_selected_pointer->range_min;
    float range_max_default = sensor_selected_pointer->range_max;
    printf("Deseja alterar os valores de range do sensor?");
    printf("Range mínimo de leitura do sensor: %2.f. \n", range_min_default);
    printf("Range máximo de leitura do sensor: %2.f. \n", range_max_default);
    printf("Digite: S - Sim, N - Não. \n");
    char user_response;
    scanf("%c", &user_response);
    getchar();

    if (user_response != 'S' && user_response != 's' && user_response != 'N' && user_response != 'n')
    {
        printf("Erro: opção inválida. \n");
        return;
    }

    float new_range_min = 0.0;
    float new_range_max = 0.0;

    printf("Digite o novo range mínimo:");
    scanf("%f", &new_range_min);

    printf("Digite o novo range máximo:");
    scanf("%f", &new_range_max);

    if (new_range_min > new_range_max)
    {
        printf("Erro: range mãximo deve ser maior que o range mínimo. \n");
        return;
    }

    sensor_selected_pointer->range_min = new_range_min;
    sensor_selected_pointer->range_max = new_range_max;

    printf("Range do sensor alterado com sucesso. \n");
};
