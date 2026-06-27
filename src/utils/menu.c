#include "../types.h"
#include "../helpers.h"
#include "./persistence.h"
#include "./menu.h"
#include "../utils/exports.h"
#include "../utils/search.h"
#include "../utils/reports.h"

#include "../entities/locations.h"
#include "../entities/sectors.h"
#include "../entities/sensors.h"
#include "../entities/inspections.h"

void menuLocations(t_app_state *app_state)
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
    printf("6. Exportar dados\n");
    printf("0. Fechar (Sair do programa):. \n");
    printf(":: \n");
    scanf("%i", &option);
    getchar();
    if (option == 0)
    {
        // saveUserDataOnBinaryFile(app_state);
        saveAllUserDataOnBinaryFile(app_state);
        shutdownProgram();
        return;
    }
    actionMenuLocations(option, app_state);
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
    printf("Range Mínimo e Máximo: [%2.f %s \\ %2.f %s]. \n", app_state->sensor_selected_pointer->range_min,
           mapSensorTypeUnitToString(app_state->sensor_selected_pointer->sensor_type).response,
           app_state->sensor_selected_pointer->range_max,
           mapSensorTypeUnitToString(app_state->sensor_selected_pointer->sensor_type).response);
    listAllInspections(app_state->sensor_selected_pointer->inspections);
    printf("Escolha uma opção: \n");
    printf("1. Gerar leitura no sensor. \n");
    printf("2. Listar leituras do sensor. \n");
    printf("3. Alterar range (Mín-Máx) de leitura do sensor. \n");
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
        if (new_location == NULL)
            return;
        insertNewLocationAtDatabase(&app_state->database, new_location);
        confirmAndClear();
        break;
    }
    case 2: {
        t_location *location_found = promptAndFindLocationByIdx(app_state->database);
        if (location_found == NULL)
            return;
        selectLocation(location_found, &app_state->location_selected_pointer);
        break;
    }
    case 3: {
        t_location *location_found = promptAndFindLocationByIdx(app_state->database);
        if (location_found == NULL)
            return;
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
    case 6:
        handleExportDataOfSystem(app_state);
        break;
    default:
        break;
    }
}
void actionMenuSectors(int option, t_app_state *app_state)
{
    switch (option)
    {
    case 1: {
        t_sector *new_sector = createNewSector(app_state->location_selected_pointer);
        if (new_sector == NULL)
            return;
        insertNewSectorAtDatabase(&app_state->location_selected_pointer->sectors, new_sector);
        confirmAndClear();
    }
    break;
    case 2: {
        t_sector *sector_found = promptAndFindSectorByIdx(app_state->location_selected_pointer->sectors);
        if (sector_found == NULL)
            return;
        selectSector(sector_found, &app_state->sector_selected_pointer);
        break;
    }
    case 3: {
        t_sector *sector_found = promptAndFindSectorByIdx(app_state->location_selected_pointer->sectors);
        if (sector_found == NULL)
            return;
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
    case 1: {
        t_sensor *new_sensor = createNewSensor(app_state->sector_selected_pointer);
        if (new_sensor == NULL)
            return;
        insertNewSensorAtDatabase(&app_state->sector_selected_pointer->sensors, new_sensor);
        confirmAndClear();
        break;
    }
    case 2: {
        t_sensor *sensor_found = promptAndFindSensorByIdx(app_state->sector_selected_pointer->sensors);
        if (sensor_found == NULL)
            return;
        selectSensor(sensor_found, &app_state->sensor_selected_pointer);
        break;
    }
    case 3: {
        t_sensor *sensor_found = promptAndFindSensorByIdx(app_state->sector_selected_pointer->sensors);
        if (sensor_found == NULL)
            return;
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
    case 1: {
        t_inspection *new_inspection = createNewInspection(app_state->sensor_selected_pointer);
        if (new_inspection == NULL)
            return;
        insertNewInspectionAtDatabase(&app_state->sensor_selected_pointer->inspections, new_inspection);
        confirmAndClear();
        break;
    }
    case 2:
        listAllInspections(app_state->sensor_selected_pointer->inspections);
        break;
    case 3:
        updateSensorRange(app_state->sensor_selected_pointer);
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
    int option = 1;
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
        printf(":: \n");

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
    int option = 1;
    while (option != 0)
    {
        printf("\033[1m[Realizar Busca]\033[0m\n");
        printf("Escolha uma opção de pesquisa: \n");
        printf("1. Descrição setor. \n");
        printf("2. Tipo de sensor. \n");
        printf("0. Voltar. \n");
        printf(":: \n");

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
void handleExportDataOfSystem(t_app_state *app_state)
{
    int opcao;
    do
    {

        printf("Escolha uma opção: \n");
        printf("1. Exportar como .csv\n");
        printf("2. Exportar como .html\n");
        printf("0. Voltar \n");
        printf(":: \n");

        scanf("%i", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            generateCsvFile(app_state);
            break;
        case 2:
            generateHtmlFile(app_state);
            break;
        }
    } while (opcao != 0);
}
