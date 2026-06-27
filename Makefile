CC = gcc
SRC = src/main.c src/helpers.c src/entities/locations.c src/entities/sectors.c src/entities/sensors.c src/entities/inspections.c src/utils/exports.c src/utils/menu.c src/utils/persistence.c src/utils/reports.c src/utils/search.c
OUT = exec

all:
	$(CC) $(SRC) -o $(OUT)

run: all
	./$(OUT)