#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 
#define MAX_STRING_SIZE 100
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
    int id;
    int sensor_id;
    float value;
    time_t date_inspection;
    t_inspection *next;
};

typedef struct sensor t_sensor;
struct sensor {
    int id;
    int sector_id;
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
    int id;
    int location_id;
    string name;
    string description;
    t_sensor *sensors;
    int sensors_quantity;
    t_sector *next;
};

typedef struct location t_location;
struct location {
    int id;
    string name;
    t_sector *sectors;
    int sectors_quantity;
    t_location *next;
};

typedef struct mapSensorTypeToStringResponse {
    string response;
} t_mapSensorTypeToStringResponse;

typedef struct mapSensorTypeUnitToStringResponse {
    string response;
} t_mapSensorTypeUnitToStringResponse;

void menuLocations(void);
void menuSectors(void);
void menuSensors(void);
void actionMenuLocations(int option);
void actionMenuSectors(int option);
void actionMenuSensors(int option);
void actionMenuSensorsInspection(int option);

t_mapSensorTypeToStringResponse mapSensorTypeToString(int sensor_type_enum){
    t_mapSensorTypeToStringResponse object;
    string SENSOR_TYPES_STRING_MAPPED[] = {"TEMPERATURE", "VIBRATION", "PRESSURE", "CURRENT", "HUMIDITY"};
    strcpy(object.response, SENSOR_TYPES_STRING_MAPPED[sensor_type_enum]);
    return object;
}

t_mapSensorTypeUnitToStringResponse mapSensorTypeUnitToString(int sensor_type_unit_enum){
    t_mapSensorTypeUnitToStringResponse object;
    string SENSOR_TYPES_UNIT_STRING_MAPPED[] = {"°C", "mm/s", "PSI", "A", "%"};    
    strcpy(object.response, SENSOR_TYPES_UNIT_STRING_MAPPED[sensor_type_unit_enum]);
    return object;
}

int main(){
    bool is_program_running = true;
    int *location_selected_idx = NULL;
    int *sector_selected_idx = NULL;
    int *sensor_selected_idx = NULL;
    int *inspection_selected_idx = NULL;
    srand(time(NULL));
    for(;;){
        if(!is_program_running){
            return 0;
        }
        if(
            location_selected_idx != NULL &&
            sector_selected_idx != NULL
        ){
            menuSensors();
        } else if(
            location_selected_idx != NULL
        ){
            menuSectors(); 
        } else {
            menuLocations();
        }   
    }
    return 0;
}

void menuLocations(){
        int option;
        printf("Escolha uma opção: \n");
        printf("1. Criar planta: \n");
        printf("2. Listar todas plantas: \n");
        printf("3. Selecionar planta: \n");
        printf("4. Gerar relatorio de sensores\n");
        printf("5. Gerar relatório de leituras\n");
        printf("6. Gerar relatório de setores\n");
        printf("7. Pesquisar sensor por tipo\n");
        printf("8. Pesquisar setor por descrição\n");
        printf("9. Relatório de médias de leitura por sensor\n");
        printf("10. Relatório de variação de leitura\n");
        printf("0. Fechar (Sair do programa):. \n");
        scanf("%i", &option);
        getchar();
        if(option == 0){
            //is_program_running = false;
            return;
        }
        actionMenuLocations(option);
}
void menuSectors(){
        int option;
        printf("Escolha uma opção: \n");
        printf("1. Criar setor. \n");
        printf("2. Listar todos Setores. \n");
        printf("3. Selecionar setor. \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        actionMenuSectors(option);
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
        actionMenuSensorsInspection(option);
}

void actionMenuLocations(int option){
    switch(option){
            case 1: 
                break;
            case 2: 
                break;
            case 3:
                break;
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
void actionMenuSectors(int option){
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
void actionMenuSensorsInspection(int option){
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
 