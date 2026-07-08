#include "sectors.h"
#include "../global_config.h"

t_sector *createNewSector(t_location *location_selected_pointer)
{
    t_sector *new_sector = NULL;
    new_sector = (t_sector *)malloc(sizeof(t_sector));
    string unique_id;
    generateUniqueId(unique_id, SECTOR);
    strcpy(new_sector->id, unique_id);

    printf("Digite o nome: \n");
    fgets(new_sector->name, MAX_STRING_SIZE, stdin);
    formatStringToSystemPattern(new_sector->name);

    printf("Digite a descrição: \n");
    fgets(new_sector->description, MAX_STRING_SIZE, stdin);
    formatStringToSystemPattern(new_sector->description);

    strcpy(new_sector->location_id, location_selected_pointer->id);

    new_sector->next = NULL;
    new_sector->sensors = NULL;

    printf("Novo setor foi cadastrado com sucesso. \n");

    return new_sector;
};
void insertNewSectorAtDatabase(t_sector **list_sectors, t_sector *new_sector)
{
    if (list_sectors == NULL)
    {
        new_sector->next = NULL;
    }
    else
    {
        new_sector->next = *list_sectors;
    }
    *list_sectors = new_sector;
    printf("Novo setor foi inserido com sucesso.\n-> ID: %s, Nome: %s.\n", new_sector->id, new_sector->name);
}
void deleteSectorAtDatabase(t_sector **list_sectors, string sector_id)
{
    if (*list_sectors == NULL)
    {
        printf("Não existem setores. \n");
        return;
    }

    t_sector *current_location = *list_sectors;
    t_sector *temp;

    t_sector *sector_to_delete = findSectorById(*list_sectors, sector_id);

    if (sector_to_delete == NULL)
    {
        printf("Erro ao deletar setor -> Setor não encontrado. \n");
        return;
    }

    // primeiro nó
    if (current_location == sector_to_delete)
    {
        *list_sectors = current_location->next;
        free(current_location);
        printf("Setor deletad0 com sucesso. \n");
        return;
    }

    // nao é o primero nó, encontra o anterior
    while (current_location->next != NULL && current_location->next != sector_to_delete)
    {
        current_location = current_location->next;
    }

    if (current_location->next != NULL)
    {
        temp = current_location->next;
        current_location->next = temp->next;
        free(temp);
    }

    printf("Setor deletado com sucesso. \n");
};
void listAllSectors(t_sector *list_sectors)
{
    int initial_idx = 1;
    int counter = 0;
    while (list_sectors != NULL)
    {
        printf("[IDX:  %i] -> [ID: %s, Nome: %s, Total de sensores: %i]. \n", initial_idx, list_sectors->id,
               list_sectors->name, countTotalSensors(list_sectors->sensors));

        list_sectors = list_sectors->next;
        counter++, initial_idx++;
    }
    printf("Total de setores: %i.\n", counter);
}
void selectSector(t_sector *sector, t_sector **sector_selected_pointer)
{
    *sector_selected_pointer = sector;
};
t_sector *findSectorById(t_sector *list_sectors, string sector_id)
{
    t_sector *copy_list_sensors = list_sectors;

    while (copy_list_sensors != NULL && strcmp(copy_list_sensors->id, sector_id) != 0)
    {
        copy_list_sensors = copy_list_sensors->next;
    }
    return copy_list_sensors;
}
t_sector *findSectorByIdx(t_sector *list_sectors, int idx)
{
    t_sector *copy_list_sectors = list_sectors;

    int initial_idx = 1;
    while (copy_list_sectors != NULL)
    {
        if (initial_idx == idx)
            return copy_list_sectors;
        copy_list_sectors = copy_list_sectors->next;
        initial_idx++;
    }
    return NULL;
}
t_sector *promptAndFindSectorByIdx(t_sector *list_sectors)
{
    t_sector *sector_found = NULL;
    int total_sectors = countTotalSectors(list_sectors);
    if (total_sectors < 1)
    {
        printf("Sem setores existentes. \n");
        return sector_found;
    }
    listAllSectors(list_sectors);
    int sector_idx;
    printf("Digite o índice do setor: \n");
    printf(":: \n");
    scanf("%i", &sector_idx);
    getchar();
    sector_found = findSectorByIdx(list_sectors, sector_idx);
    if (sector_found == NULL)
    {
        printf("Erro ao encontrar setor. \n");
    }
    return sector_found;
}
int countTotalSectors(t_sector *list_sectors)
{
    t_sector *current_sector = list_sectors;
    int counter = 0;
    while (current_sector != NULL)
    {
        counter++;
        current_sector = current_sector->next;
    }
    return counter;
}
