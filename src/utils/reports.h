#ifndef REPORTS_H
#define REPORTS_H

void generateReportOfInspections(t_location *locations);
void generateReportsOfSectors(t_location *locations);
void generateReportOfSensors(t_location *locations);
void generateReportOfInspectionsAverage(t_location *locations);
void generateReportOfInspectionsVariation(t_location *locations);

#endif