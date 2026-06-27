#include "./locations.h"
#include "../global_config.h"
#include "./sectors.h"

t_location *createNewLocation()
{
    t_location *new_location = NULL;
    new_location = (t_location *)malloc(sizeof(t_location));
    string unique_id;
    generateUniqueId(unique_id, LOCATION);
    strcpy(new_location->id, unique_id);

    printf("Digite o nome: \n");
    fgets(new_location->name, MAX_STRING_SIZE, stdin);
    formatStringToSystemPattern(new_location->name);

    printf("Nova planta foi cadastrada com sucesso. \n");
    return new_location;
};
void insertNewLocationAtDatabase(t_location **list_locations, t_location *new_location)
{
    if (list_locations == NULL)
    {
        new_location->next = NULL;
    }
    else
    {
        new_location->next = *list_locations;
    }
    *list_locations = new_location;
    printf("Nova planta foi inserida com sucesso\n-> ID: %s, Nome: %s. \n", new_location->id, new_location->name);
}
void deleteLocationAtDatabase(t_location **list_locations, string location_id)
{
    if (*list_locations == NULL)
    {
        printf("Não existem plantas. \n");
        return;
    }

    t_location *current_location = *list_locations;
    t_location *temp;

    t_location *location_to_delete = findLocationById(*list_locations, location_id);

    if (location_to_delete == NULL)
    {
        printf("Erro ao deletar planta -> Planta não encontrada. \n");
        return;
    }

    // primeiro nó
    if (current_location == location_to_delete)
    {
        *list_locations = current_location->next;
        free(current_location);
        printf("Planta deletada com sucesso. \n");
        return;
    }

    // nao é o primero nó, encontra o anterior
    while (current_location->next != NULL && current_location->next != location_to_delete)
    {
        current_location = current_location->next;
    }

    if (current_location->next != NULL)
    {
        temp = current_location->next;
        current_location->next = temp->next;
        free(temp);
    }

    printf("Planta deletada com sucesso. \n");
};
void listAllLocations(t_location *list_locations)
{
    int initial_idx = 1;
    int counter = 0;
    printf("\n\n");
    while (list_locations != NULL)
    {
        printf("[IDX:  %i] -> [ID: %s, Nome: %s, Total de setores: %i]. \n", initial_idx, list_locations->id,
               list_locations->name, countTotalSectors(list_locations->sectors));

        list_locations = list_locations->next;
        counter++, initial_idx++;
    }
    printf("\n\nTotal de plantas encontradas no sistema: %i.\n\n", counter);
}
void selectLocation(t_location *location, t_location **location_selected_pointer)
{
    *location_selected_pointer = location;
};
t_location *findLocationById(t_location *list_locations, string location_id)
{
    t_location *copy_list_location = list_locations;
    while (copy_list_location != NULL && strcmp(copy_list_location->id, location_id) != 0)
    {
        copy_list_location = copy_list_location->next;
    }
    return copy_list_location ? copy_list_location : NULL;
    ;
}
t_location *findLocationByIdx(t_location *list_locations, int idx)
{
    int initial_idx = 1;
    while (list_locations != NULL)
    {
        if (initial_idx == idx)
            return list_locations;
        list_locations = list_locations->next;
        initial_idx++;
    }
    return NULL;
}
t_location *promptAndFindLocationByIdx(t_location *list_locations)
{
    t_location *location_found = NULL;
    int total_location = countTotalLocations(list_locations);
    if (total_location < 1)
    {
        printf("Sem plantas existentes. \n");
        return location_found;
    }
    listAllLocations(list_locations);
    int location_idx;
    printf("Digite o índice da planta: \n");
    printf(":: \n");
    scanf("%i", &location_idx);
    location_found = findLocationByIdx(list_locations, location_idx);
    if (location_found == NULL)
    {
        printf("Erro ao encontrar planta. \n");
    }
    return location_found;
}
int countTotalLocations(t_location *list_locations)
{
    t_location *current_location = list_locations;
    int counter = 0;
    while (current_location != NULL)
    {
        counter++;
        current_location = current_location->next;
    }
    return counter;
}
