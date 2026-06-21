#define MAX_STRING_SIZE 1000

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
