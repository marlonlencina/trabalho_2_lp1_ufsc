#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 
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

typedef enum entities{
    LOCATION,
    SECTOR,
    SENSOR,
    INSPECTION
} t_entities;

typedef enum sensor_types{
    TEMPERATURE,
    VIBRATION,
    PRESSURE,
    CURRENT,
    HUMIDITY
} t_sensor_types;

typedef struct datetime {
    string date;
} t_date_string;

typedef struct inspection t_inspection;
struct inspection {
    string id;
    string sensor_id;
    float value;
    time_t date_inspection;
    t_inspection *next;
};

typedef struct sensor t_sensor;
struct sensor {
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
struct sector {
    string id;
    string location_id;
    string name;
    string description;
    t_sensor *sensors;
    int sensors_quantity;
    t_sector *next;
};

typedef struct location t_location;
struct location {
    string id;
    string name;
    t_sector *sectors;
    int sectors_quantity;
    t_location *next;
};

typedef struct stringAsStructResponse {
    string response;
} t_string;

typedef struct appState {
    t_location *database;       
    t_location *location_selected_pointer;
    t_sector   *sector_selected_pointer;
    t_sensor   *sensor_selected_pointer;
    t_inspection *inspection_selected_pointer;
} t_app_state;

void menuLocations(t_app_state *app_state);
void menuSectors(t_app_state *app_state);
void menuSensors(void);
void actionMenuLocations(int option, t_app_state *app_state);
void actionMenuSectors(int option, t_app_state *app_state);
void actionMenuSensors(int option);
void actionMenuInspections(int option);
void resetStateOfMenuSelectedPointers(t_entities entity_type, t_app_state *state);
void shutdownProgram();

void generateUniqueId(char* buffer, t_entities entity_type);
void formatStringRemoveEnter(string str);
void formatStringToUppercase(string str);
void formatStringToSystemPattern(string str);

t_location *createNewLocation();
void listAllLocations(t_location *list_locations);
void insertNewLocationAtDatabase(t_location **list_locations,  t_location *new_location);
void selectLocation(t_location *location, t_location **location_selected);
t_location *findLocationById(t_location **list_locations, string location_id);
void deleteLocationAtDatabase(t_location **list_locations, string location_id);
t_location *findLocationByIdx(t_location *list, int idx);
t_location *promptAndFindLocationByIdx(t_location *list_locations);

int main(){
    srand(time(NULL));
    t_app_state app_state = {0};
    for(;;){
        if(
            app_state.location_selected_pointer != NULL &&
            app_state.sector_selected_pointer != NULL
        ){
            menuSensors();
        } else if(
            app_state.location_selected_pointer != NULL
        ){
            menuSectors(&app_state); 
        } else {
            menuLocations(&app_state);
        }   
    }
    return 0;
}

void menuLocations(t_app_state *appState){
        int option;
        printf("Bem-vindo 👋. \n");
        printf("Escolha uma opção: \n");
        printf("1. Criar Planta \n");
        printf("2. Selecionar Planta \n");
        printf("3. Deletar Planta \n");
        printf("0. Fechar (Sair do programa):. \n");
        printf(":: \n");
        scanf("%i", &option);
        getchar();
        if(option == 0){
            shutdownProgram();
            return;
        }
        actionMenuLocations(option, appState);
}
void menuSectors(t_app_state *app_state){
        int option;
        printf("Escolha uma opção: \n");
        printf("1. Criar setor. \n");
        printf("2. Listar todos Setores. \n");
        printf("3. Selecionar setor. \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        actionMenuSectors(option, app_state);
}
void menuSensors(){
        int option;
        printf(" Escolha uma opção: ");
        printf("1. Criar sensor. \n");
        printf("2. Listar sensores. \n");
        printf("3. Selecionar sensor. \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        actionMenuSensors(option);
}
void menuInspection(){
        int option;
        printf("Escolha uma opção: \n");
        printf("1. Gerar leitura no sensor. \n");
        printf("2. Listar leituras do sensor. \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        actionMenuInspections(option);
}
void actionMenuLocations(int option, t_app_state *app_state){
    switch(option){
            case 1:
                t_location *new_location = createNewLocation();
                insertNewLocationAtDatabase(&app_state->database, new_location);
                break;
            case 2: 
                {
                t_location *location_found = promptAndFindLocationByIdx(app_state->database);
                selectLocation(location_found, &app_state->location_selected_pointer);
                break;
                }
            case 3:
            {
                t_location *location_found = promptAndFindLocationByIdx(app_state->database);
                deleteLocationAtDatabase(&app_state->database, location_found->id);
                break;
                }
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            default: break;
        }
}
void actionMenuSectors(int option, t_app_state *app_state){
        switch (option)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 0:
                resetStateOfMenuSelectedPointers(LOCATION, app_state);
                break;
            default:
                break;
        }
}
void actionMenuSensors(int option){
    switch (option)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 0: 
                break;
            default:
                break;
        }
}
void actionMenuInspections(int option){
    switch (option)
        {  
            case 1:
                break;
            case 2:
                break;
            case 0: 
                break;
            default:
                break;
        }
}
void resetStateOfMenuSelectedPointers(t_entities entity_type, t_app_state *state){
    switch(entity_type){
        case LOCATION:
                {
                state->location_selected_pointer = NULL;
                state->sector_selected_pointer = NULL;
                state->sensor_selected_pointer = NULL;
                state->inspection_selected_pointer = NULL;
                break;
                }
        case SECTOR:
                {
                state->sector_selected_pointer = NULL;
                state->sensor_selected_pointer = NULL;
                state->inspection_selected_pointer = NULL;
                break;
                }
        case SENSOR:
                {
                state->sensor_selected_pointer = NULL;
                state->inspection_selected_pointer = NULL;
                break;
                }
        case INSPECTION:
                {
                state->inspection_selected_pointer = NULL;
                break;
                }
    }
};
void shutdownProgram(){
    printf("Encerrando operação. Até logo 👋\n ");
    exit(0);
}

t_string mapSensorTypeToString(int sensor_type_enum){
    t_string object;
    string SENSOR_TYPES_STRING_MAPPED[] = {"TEMPERATURE", "VIBRATION", "PRESSURE", "CURRENT", "HUMIDITY"};
    strcpy(object.response, SENSOR_TYPES_STRING_MAPPED[sensor_type_enum]);
    return object;
}
t_string mapSensorTypeUnitToString(int sensor_type_unit_enum){
    t_string object;
    string SENSOR_TYPES_UNIT_STRING_MAPPED[] = {"°C", "mm/s", "PSI", "A", "%"};    
    strcpy(object.response, SENSOR_TYPES_UNIT_STRING_MAPPED[sensor_type_unit_enum]);
    return object;
}
t_string mapEntityToString(int entity){
    t_string object;
    string ENTITIES_TYPES[] = {"LOCATION", "SECTOR", "SENSOR", "INSPECTION"};    
    strcpy(object.response, ENTITIES_TYPES[entity]);
    return object;
}

t_location *createNewLocation(){
    t_location *new_location = NULL;
    new_location = (t_location*)malloc(sizeof(t_location));
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
void insertNewLocationAtDatabase(t_location **list_locations,  t_location *new_location){
    if(list_locations == NULL){
        new_location->next = NULL;
    } else {
        new_location->next = *list_locations;
    } 
    *list_locations = new_location;
    printf("Nova planta foi inserida com sucesso. \n");
}
void deleteLocationAtDatabase(t_location **list_locations, string location_id){
    if(*list_locations == NULL){
        printf("Não existem plantas. \n");
        return;
    }

    t_location *current_location = *list_locations;
    t_location *temp;

    t_location *location_to_delete = findLocationById(list_locations, location_id);

    if(location_to_delete == NULL){
        printf("Erro ao deletar planta -> Planta não encontrada. \n");
        return;
    }

    //primeiro nó
    if(current_location == location_to_delete){
        *list_locations = current_location->next;
        free(current_location);
        printf("Planta deletada com sucesso. \n");
        return;
    }
    
    //nao é o primero nó, encontra o anterior
    while(current_location->next != NULL && current_location->next != location_to_delete){
        current_location = current_location->next;
    }

    if(current_location->next != NULL){
        temp = current_location->next;
        current_location->next = temp->next;
        free(temp);
    }

};
void listAllLocations(t_location *list_locations){
    int initial_idx = 1;
    int counter = 0;

    while(list_locations != NULL){
        printf("[IDX: %i] -> [ID: %s, Nome: %s]. \n", initial_idx, list_locations->id, list_locations->name);
        list_locations = list_locations->next;
        counter++, initial_idx++;
    }
    printf("\n\nTotal de plantas encontradas no sistema: %i.\n\n", counter);
}
void selectLocation(t_location *location, t_location **location_selected_pointer){
    *location_selected_pointer = location; 
};
t_location *findLocationById(t_location **list_locations, string location_id){
    t_location *copy_list_location = *list_locations;
    while(copy_list_location != NULL && strcmp(copy_list_location->id, location_id) != 0){
        copy_list_location = copy_list_location->next;
    }
    return copy_list_location ? copy_list_location : NULL;;
}
t_location *findLocationByIdx(t_location *list_locations, int idx){
    int initial_idx = 1;
    while(list_locations != NULL){
        if(initial_idx == idx) return list_locations;
        list_locations = list_locations->next;
        initial_idx++;
    }
    return NULL;
}
t_location *promptAndFindLocationByIdx(t_location *list_locations){
    listAllLocations(list_locations);
    int location_idx;
    printf("Digite o índice da planta: \n");
    printf(":: \n");
    scanf("%i", &location_idx);
    t_location *location_found = findLocationByIdx(list_locations, location_idx);
    if(location_found == NULL){
        printf("Erro ao encontrar planta. \n");
    }
    return location_found;
}

void generateUniqueId(char* buffer, t_entities entity_type){
    t_string struct_sensor_type_string = mapEntityToString(entity_type);
    snprintf(buffer, 1000, "%.5s_%li_%i", struct_sensor_type_string.response, time(NULL), rand());
}
void formatStringRemoveEnter(string str){
    if(strlen(str) < 1) return;
    str[strlen(str) - 1] = '\0';
}
void formatStringToUppercase(string str){
    for(int i = 0; str[i] != '\0'; i++){
        str[i] = toupper(str[i]);
    }
}
void formatStringToSystemPattern(string str){
    formatStringRemoveEnter(str);
    formatStringToUppercase(str);
}