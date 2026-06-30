#ifndef REPORTS_H
#define REPORTS_H

void generateReportOfInspections(t_location *locations);
void generateReportOfInspectionsFile(t_location *locations, string filepath);
void generateReportOfInspectionsTerminal(t_location *locations);

void generateReportsOfSectors(t_location *locations);
void generateReportsOfSectorsFile(t_location *locations, string filepath);
void generateReportsOfSectorsTerminal(t_location *locations);

void generateReportOfSensors(t_location *locations);
void generateReportOfSensorsFile(t_location *locations, string filepath);
void generateReportOfSensorsTerminal(t_location *locations);

void generateReportOfInspectionsAverage(t_location *locations);
void generateReportOfInspectionsAverageFile(t_location *locations, string filepath);
void generateReportOfInspectionsAverageTerminal(t_location *locations);

void generateReportOfInspectionsVariation(t_location *locations);
void generateReportOfInspectionsVariationFile(t_location *locations, string filepath);
void generateReportOfInspectionsVariationTerminal(t_location *locations);

int outputSelectionLog();
#endif