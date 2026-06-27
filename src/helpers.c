#include "helpers.h"

t_string getFilepathMatchEntity(t_entities entity, string base_filepath, string base_filefolder)
{
    t_string object = {.response = ""};
    strcat(object.response, base_filefolder);
    switch (entity)
    {
    case LOCATION:
        strcat(object.response, "/locations/");
        break;
    case SECTOR:
        strcat(object.response, "/sectors/");
        break;
    case SENSOR:
        strcat(object.response, "/sensors/");
        break;
    case INSPECTION:
        strcat(object.response, "/inspections/");
        break;
    default:
        strcat(object.response, "/");
        break;
    }
    strcat(object.response, base_filepath);

    return object;
}
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
