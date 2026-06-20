#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_SIZE 1000
#define MAX_LOCATIONS 5
#define MAX_SECTORS 5
#define MAX_SENSORS 3
#define MAX_INSPECTIONS 5
#define MAX_SENSORS_TYPES 5
#define MAX_INSPECTIONS_ON_SAME_DAY 2
#define END 0
#define NOT_FOUND 0
#define NOT_SELECTED -1

typedef char string[MAX_STRING_SIZE];

typedef enum entities
{
    LOCATION,
    SECTOR,
    SENSOR,
    INSPECTION
} t_entities;

typedef enum sensor_types
{
    TEMPERATURE,
    VIBRATION,
    PRESSURE,
    CURRENT,
    HUMIDITY
} t_sensor_types;

typedef struct datetime
{
    string date;
} t_date_string;

typedef struct inspection t_inspection;
struct inspection
{
    string id;
    string sensor_id;
    float value;
    time_t date_inspection;
    t_inspection *next;
};

typedef struct sensor t_sensor;
struct sensor
{
    string id;
    string sector_id;
    string name;
    t_sensor_types sensor_type;
    t_inspection *inspections;
    float range_min;
    float range_max;
    int inspections_quantity;
    t_sensor *next;
};

typedef struct sector t_sector;
struct sector
{
    string id;
    string location_id;
    string name;
    string description;
    t_sensor *sensors;
    int sensors_quantity;
    t_sector *next;
};

typedef struct location t_location;
struct location
{
    string id;
    string name;
    t_sector *sectors;
    int sectors_quantity;
    t_location *next;
};

typedef struct stringAsStructResponse
{
    string response;
} t_string;

typedef struct sensorTemplate
{
    string name;
    float range_min;
    float range_max;
} t_sensor_template;

typedef struct appState
{
    t_location *database;
    t_location *location_selected_pointer;
    t_sector *sector_selected_pointer;
    t_sensor *sensor_selected_pointer;
    t_inspection *inspection_selected_pointer;
} t_app_state;

void menuLocations(t_app_state *app_state);
void menuSectors(t_app_state *app_state);
void menuSensors(t_app_state *app_state);
void menuInspections(t_app_state *app_state);
void actionMenuLocations(int option, t_app_state *app_state);
void actionMenuSectors(int option, t_app_state *app_state);
void actionMenuSensors(int option, t_app_state *app_state);
void actionMenuInspections(int option, t_app_state *app_state);
void resetStateOfMenuSelectedPointers(t_entities entity_type, t_app_state *state);
void shutdownProgram();

t_location *createNewLocation();
void insertNewLocationAtDatabase(t_location **list_locations, t_location *new_location);
void deleteLocationAtDatabase(t_location **list_locations, string location_id);
void listAllLocations(t_location *list_locations);
void selectLocation(t_location *location, t_location **location_selected);
t_location *findLocationById(t_location **list_locations, string location_id);
t_location *findLocationByIdx(t_location *list, int idx);
t_location *promptAndFindLocationByIdx(t_location *list_locations);

t_sector *createNewSector(t_location *location_selected_pointer);
void insertNewSectorAtDatabase(t_sector **list_sectors, t_sector *new_sector);
void deleteSectorAtDatabase(t_sector **list_sectors, string sector_id);
void listAllSectors(t_sector *list_sectors);
void selectSector(t_sector *sector, t_sector **sector_selected_pointer);
t_sector *findSectorById(t_sector *list_sectors, string sector_id);
t_sector *findSectorByIdx(t_sector *list_sectors, int idx);
t_sector *promptAndFindSectorByIdx(t_sector *list_sectors);

t_sensor *createNewSensor(t_sector *sector_selected_pointer);
void insertNewSensorAtDatabase(t_sensor **list_sensors, t_sensor *new_sensor);
void deleteSensorAtDatabase(t_sensor **list_sensors, string sensor_id);
void listAllSensors(t_sensor *list_sensors);
void selectSensor(t_sensor *sensor, t_sensor **sensor_selected_pointer);
t_sensor *findSensorById(t_sensor *list_sensor, string sensor_id);
t_sensor *findSensorByIdx(t_sensor *list_sensor, int idx);
t_sensor *promptAndFindSensorByIdx(t_sensor *list_sensors);
t_sensor_template getSensorTemplate(t_sensor_types sensor_type);

t_inspection *createNewInspection(t_sensor *sensor_selected_pointer);
void insertNewInspectionAtDatabase(t_inspection **list_inspections, t_inspection *new_inspection);
void deleteInspectionAtDatabase(t_inspection **list_inspections, string inspection_id);
void listAllInspections(t_inspection *list_inspections);
void selectInspection(t_inspection *inspection, t_inspection **inspection_selected_pointer);
t_inspection *findInspectionById(t_inspection *list_inspections, string inspection_id);
t_inspection *findInspectionByIdx(t_inspection *list_inspections, int idx);
t_inspection *promptAndFindInspectionByIdx(t_inspection *list_inspections);

void confirmAndClear();
bool checkIfIsTheSameDay(time_t firstTimestamp, time_t secondTimestamp);
void generateUniqueId(char *buffer, t_entities entity_type);
void formatStringRemoveEnter(string str);
void formatStringToUppercase(string str);
void formatStringToSystemPattern(string str);
t_string mapSensorTypeToString(int sensor_type_enum);
t_string mapSensorTypeUnitToString(int sensor_type_unit_enum);
t_string mapEntityToString(int entity);
t_string mapTimestampToString(time_t timestamp, bool enable_hours);

void handleGenerateSystemReport(t_app_state *app_state);
void handleSearchInSystem(t_app_state *app_state);
void generateReportOfInspections(t_location *locations);
void generateReportsOfSectors(t_location *locations);
void generateReportOfSensors(t_location *locations);
void generateReportOfInspectionsAverage(t_location *locations);
void generateReportOfInspectionsVariation(t_location *locations);
void searchForSectorDescription(t_location *locations);
void searchForSensorType(t_location *locations);

int main()
{
    srand(time(NULL));
    t_app_state app_state = {0};
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

void menuLocations(t_app_state *appState)
{
    int option;
    printf("\033[1m[Menu Inicial]\033[0m\n");
    printf("Bem-vindo 👋. \n");
    printf("Escolha uma opção: \n");
    printf("1. Criar Planta \n");
    printf("2. Selecionar Planta \n");
    printf("3. Deletar Planta \n");
    printf("4. Realizar Busca (Planta, Setor, Sensor) \n");
    printf("5. Relatórios \n");
    printf("0. Fechar (Sair do programa):. \n");
    printf(":: \n");
    scanf("%i", &option);
    getchar();
    if (option == 0)
    {
        shutdownProgram();
        return;
    }
    actionMenuLocations(option, appState);
}
void menuSectors(t_app_state *app_state)
{
    int option;
    printf("\033[1m[Menu de Setores]\033[0m\n");
    printf("Vendo a planta: %s. \n", app_state->location_selected_pointer->name);
    listAllSectors(app_state->location_selected_pointer->sectors);
    printf("Escolha uma opção: \n");
    printf("1. Criar Setor. \n");
    printf("2. Selecionar Setor. \n");
    printf("3. Deletar Setor. \n");

    printf("0. Voltar. \n");
    scanf("%i", &option);
    getchar();
    actionMenuSectors(option, app_state);
}
void menuSensors(t_app_state *app_state)
{
    int option;
    printf("\033[1m[Menu de Sensores]\033[0m\n");
    printf("Vendo a planta: %s. \n", app_state->location_selected_pointer->name);
    printf("Vendo o setor: %s. \n", app_state->sector_selected_pointer->name);
    listAllSensors(app_state->sector_selected_pointer->sensors);
    printf("Escolha uma opção: \n");
    printf("1. Linkar Sensor. \n");
    printf("2. Selecionar Sensor. \n");
    printf("3. Deletar Sensor. \n");
    printf("0. Voltar. \n");
    scanf("%i", &option);
    getchar();
    actionMenuSensors(option, app_state);
}
void menuInspections(t_app_state *app_state)
{
    int option;
    printf("\033[1m[Menu de Leituras]\033[0m\n");
    printf("Vendo a planta: %s. \n", app_state->location_selected_pointer->name);
    printf("Vendo o setor: %s. \n", app_state->sector_selected_pointer->name);
    printf("Vendo o Sensor: %s. \n", app_state->sensor_selected_pointer->name);
    listAllInspections(app_state->sensor_selected_pointer->inspections);
    printf("Escolha uma opção: \n");
    printf("1. Gerar leitura no sensor. \n");
    printf("2. Listar leituras do sensor. \n");
    printf("0. Voltar. \n");
    scanf("%i", &option);
    getchar();
    actionMenuInspections(option, app_state);
}
void actionMenuLocations(int option, t_app_state *app_state)
{
    switch (option)
    {
    case 1: {
        t_location *new_location = createNewLocation();
        insertNewLocationAtDatabase(&app_state->database, new_location);
        confirmAndClear();
        break;
    }
    case 2: {
        t_location *location_found = promptAndFindLocationByIdx(app_state->database);
        selectLocation(location_found, &app_state->location_selected_pointer);
        break;
    }
    case 3: {
        t_location *location_found = promptAndFindLocationByIdx(app_state->database);
        deleteLocationAtDatabase(&app_state->database, location_found->id);
        confirmAndClear();
        break;
    }
    case 4: {
        handleSearchInSystem(app_state);
        break;
    }
    case 5: {
        handleGenerateSystemReport(app_state);
        break;
    }
    default:
        break;
    }
}
void actionMenuSectors(int option, t_app_state *app_state)
{
    switch (option)
    {
    case 1:
        t_sector *new_sector = createNewSector(app_state->location_selected_pointer);
        insertNewSectorAtDatabase(&app_state->location_selected_pointer->sectors, new_sector);
        confirmAndClear();
        break;
    case 2: {
        t_sector *sector_found = promptAndFindSectorByIdx(app_state->location_selected_pointer->sectors);
        selectSector(sector_found, &app_state->sector_selected_pointer);
        break;
    }
    case 3: {
        t_sector *sector_found = promptAndFindSectorByIdx(app_state->location_selected_pointer->sectors);
        deleteSectorAtDatabase(&app_state->location_selected_pointer->sectors, sector_found->id);
        confirmAndClear();
        break;
    }
    case 0:
        resetStateOfMenuSelectedPointers(LOCATION, app_state);
        break;
    default:
        break;
    }
}
void actionMenuSensors(int option, t_app_state *app_state)
{
    switch (option)
    {
    case 1:
        t_sensor *new_sensor = createNewSensor(app_state->sector_selected_pointer);
        insertNewSensorAtDatabase(&app_state->sector_selected_pointer->sensors, new_sensor);
        confirmAndClear();
        break;
    case 2: {
        t_sensor *sensor_found = promptAndFindSensorByIdx(app_state->sector_selected_pointer->sensors);
        selectSensor(sensor_found, &app_state->sensor_selected_pointer);
        break;
    }
    case 3: {
        t_sensor *sensor_found = promptAndFindSensorByIdx(app_state->sector_selected_pointer->sensors);
        deleteSensorAtDatabase(&app_state->sector_selected_pointer->sensors, sensor_found->id);
        confirmAndClear();
        break;
    }
    case 0:
        resetStateOfMenuSelectedPointers(SECTOR, app_state);
        break;
    default:
        break;
    }
}
void actionMenuInspections(int option, t_app_state *app_state)
{
    switch (option)
    {
    case 1:
        t_inspection *new_inspection = createNewInspection(app_state->sensor_selected_pointer);
        if (new_inspection == NULL)
            return;
        insertNewInspectionAtDatabase(&app_state->sensor_selected_pointer->inspections, new_inspection);
        confirmAndClear();
        break;
    case 2:
        listAllInspections(app_state->sensor_selected_pointer->inspections);
        break;
    case 0:
        resetStateOfMenuSelectedPointers(SENSOR, app_state);
        break;
    default:
        break;
    }
}

void handleGenerateSystemReport(t_app_state *app_state)
{
    int option;
    while (option != 0)
    {
        printf("\033[1m[Relatórios]\033[0m\n");
        printf("Escolha uma opção: \n");
        printf("1. Setores. \n");
        printf("2. Sensores. \n");
        printf("3. Leituras. \n");
        printf("4. Leituras (Variação). \n");
        printf("5. Leituras (Média). \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        switch (option)
        {
        case 1:
            generateReportsOfSectors(app_state->database);
            break;
        case 2:
            generateReportOfSensors(app_state->database);
            break;
        case 3:
            generateReportOfInspections(app_state->database);
            break;
        case 4:
            generateReportOfInspectionsVariation(app_state->database);
            break;
        case 5:
            generateReportOfInspectionsAverage(app_state->database);
            break;
        case 0:
            break;
        }
    }
};
void handleSearchInSystem(t_app_state *app_state)
{
    int option;
    while (option != 0)
    {
        printf("\033[1m[Realizar Busca]\033[0m\n");
        printf("Escolha uma opção de pesquisa: \n");
        printf("1. Descrição setor. \n");
        printf("2. Tipo de sensor. \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        switch (option)
        {
        case 1:
            searchForSectorDescription(app_state->database);
            break;
        case 2:
            searchForSensorType(app_state->database);
            break;
        case 0:
            break;
        }
    }
};

void resetStateOfMenuSelectedPointers(t_entities entity_type, t_app_state *state)
{
    switch (entity_type)
    {
    case LOCATION: {
        state->location_selected_pointer = NULL;
        state->sector_selected_pointer = NULL;
        state->sensor_selected_pointer = NULL;
        state->inspection_selected_pointer = NULL;
        break;
    }
    case SECTOR: {
        state->sector_selected_pointer = NULL;
        state->sensor_selected_pointer = NULL;
        state->inspection_selected_pointer = NULL;
        break;
    }
    case SENSOR: {
        state->sensor_selected_pointer = NULL;
        state->inspection_selected_pointer = NULL;
        break;
    }
    case INSPECTION: {
        state->inspection_selected_pointer = NULL;
        break;
    }
    }
};
void shutdownProgram()
{
    printf("Encerrando operação. Até logo 👋\n ");
    exit(0);
}

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

    new_location->sectors_quantity = 0;

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
    printf("Nova planta foi inserida com sucesso. \n");
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

    t_location *location_to_delete = findLocationById(list_locations, location_id);

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
               list_locations->name, list_locations->sectors_quantity);

        list_locations = list_locations->next;
        counter++, initial_idx++;
    }
    printf("\n\nTotal de plantas encontradas no sistema: %i.\n\n", counter);
}
void selectLocation(t_location *location, t_location **location_selected_pointer)
{
    *location_selected_pointer = location;
};
t_location *findLocationById(t_location **list_locations, string location_id)
{
    t_location *copy_list_location = *list_locations;
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
    listAllLocations(list_locations);
    int location_idx;
    printf("Digite o índice da planta: \n");
    printf(":: \n");
    scanf("%i", &location_idx);
    t_location *location_found = findLocationByIdx(list_locations, location_idx);
    if (location_found == NULL)
    {
        printf("Erro ao encontrar planta. \n");
    }
    return location_found;
}

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

    new_sector->sensors_quantity = 0;
    strcpy(new_sector->location_id, location_selected_pointer->id);

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
    printf("Novo setor foi inserido com sucesso. \n");
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
               list_sectors->name, list_sectors->sensors_quantity);

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
    while (list_sectors != NULL)
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
    listAllSectors(list_sectors);
    int sector_idx;
    printf("Digite o índice do setor: \n");
    printf(":: \n");
    scanf("%i", &sector_idx);
    t_sector *sector_found = findSectorByIdx(list_sectors, sector_idx);
    if (sector_found == NULL)
    {
        printf("Erro ao encontrar setor. \n");
    }
    return sector_found;
}

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
    new_sensor->inspections_quantity = 0;

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
    printf("Novo sensor foi inserido com sucesso. \n");
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
               list_sensors->name, list_sensors->inspections_quantity);

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
    listAllSensors(list_sensors);
    int sensor_idx;
    printf("Digite o índice do sensor: \n");
    printf(":: \n");
    scanf("%i", &sensor_idx);
    t_sensor *sensor_found = findSensorByIdx(list_sensors, sensor_idx);
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

t_inspection *createNewInspection(t_sensor *sensor_selected_pointer)
{
    t_inspection *new_inspection = NULL;
    new_inspection = (t_inspection *)malloc(sizeof(t_inspection));
    string unique_id;
    generateUniqueId(unique_id, SENSOR);
    strcpy(new_inspection->id, unique_id);

    time_t date;
    time(&date);
    new_inspection->date_inspection = date;

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
    printf("Nova leitura foi inserido com sucesso. \n");
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
    listAllInspections(list_inspections);
    int inspection_idx;
    printf("Digite o índice da leitura: \n");
    printf(":: \n");
    scanf("%i", &inspection_idx);
    t_inspection *inspection_found = findInspectionByIdx(list_inspections, inspection_idx);
    if (inspection_found == NULL)
    {
        printf("Erro ao encontrar leitura. \n");
    }
    return inspection_found;
}

void generateUniqueId(char *buffer, t_entities entity_type)
{
    t_string struct_sensor_type_string = mapEntityToString(entity_type);
    snprintf(buffer, 1000, "%.5s_%li_%i", struct_sensor_type_string.response, time(NULL), rand());
}
void formatStringRemoveEnter(string str)
{
    if (strlen(str) < 1)
        return;
    str[strlen(str) - 1] = '\0';
}
void formatStringToUppercase(string str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}
void formatStringToSystemPattern(string str)
{
    formatStringRemoveEnter(str);
    formatStringToUppercase(str);
}
void confirmAndClear()
{
    printf("Pressione ENTER para continuar...");
    getchar();
    system("clear");
}
bool checkIfIsTheSameDay(time_t firstTimestamp, time_t secondTimestamp)
{
    struct tm *date_a = localtime(&firstTimestamp);
    struct tm date_a_copy = *date_a;
    struct tm *date_b = localtime(&secondTimestamp);

    return date_a_copy.tm_mday == date_b->tm_mday && date_a_copy.tm_mon == date_b->tm_mon &&
           date_a_copy.tm_year == date_b->tm_year;
}
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
                printf("ID: %s\nNome: %s \nDescrição: %s \nQuantidade de "
                       "sensores: %i\n",
                       current_sector->id, current_sector->name, current_sector->description,
                       current_sector->sensors_quantity);
                printf("\n");
            }
            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }
}
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
                           current_sensor->range_max, current_sensor->inspections_quantity);
                    printf("\n");
                }
                current_sensor = current_sensor->next;
            }
            current_sector = current_sector->next;
        }
        current_location = current_location->next;
    }
}
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
                   current_sector->name, current_sector->description, current_sector->sensors_quantity);
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
                           current_sensor->id, current_sensor->name, mapSensorTypeToString(current_sensor->sensor_type).response,
                           current_sensor->range_min, current_sensor->range_max, current_sensor->inspections_quantity);
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
                               current_sensor->range_max, current_sensor->inspections_quantity);
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
            float counter_sum_values = 0.0;

            while (current_sensor != NULL)
            {
                t_inspection *current_inspection = current_sensor->inspections;
                while (current_inspection != NULL)
                {
                    counter_sum_values = counter_sum_values + current_inspection->value;
                    if (current_sensor->inspections_quantity > 0)
                    {
                        printf("\n");
                        printf("Planta: %s \n", current_location->name);
                        printf("  Setor: %s\n", current_sector->name);
                        printf("    Sensor: %s\n", current_sensor->name);
                        printf("       Média: %.4f %s. \n",
                               counter_sum_values / (float)current_sensor->inspections_quantity,
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

t_string mapSensorTypeToString(int sensor_type_enum)
{
    t_string object;
    string SENSOR_TYPES_STRING_MAPPED[] = {"TEMPERATURE", "VIBRATION", "PRESSURE", "CURRENT", "HUMIDITY"};
    strcpy(object.response, SENSOR_TYPES_STRING_MAPPED[sensor_type_enum]);
    return object;
}
t_string mapSensorTypeUnitToString(int sensor_type_unit_enum)
{
    t_string object;
    string SENSOR_TYPES_UNIT_STRING_MAPPED[] = {"°C", "mm/s", "PSI", "A", "%"};
    strcpy(object.response, SENSOR_TYPES_UNIT_STRING_MAPPED[sensor_type_unit_enum]);
    return object;
}
t_string mapEntityToString(int entity)
{
    t_string object;
    string ENTITIES_TYPES[] = {"LOCATION", "SECTOR", "SENSOR", "INSPECTION"};
    strcpy(object.response, ENTITIES_TYPES[entity]);
    return object;
}
t_string mapTimestampToString(time_t timestamp, bool enable_hours)
{
    t_string object;
    struct tm *tm_info = localtime(&timestamp);
    char date_str[50];
    if (enable_hours)
    {
        strftime(date_str, sizeof(date_str), "%d/%m/%Y %H:%M:%S", tm_info);
    }
    else
    {
        strftime(date_str, sizeof(date_str), "%d/%m/%Y", tm_info);
    }
    strcpy(object.response, date_str);
    return object;
}