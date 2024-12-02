#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <time.h>


void check_file_opening(FILE *fp);
long size_of_file(FILE *fp);
void check_buffer(char *buffer);
void update_json(cJSON *json, FILE *outputFile);
void weightBasedDosage();
void liquidDosage(int unitChoice2);
void printMedicineDosage(cJSON *medicine, cJSON *dosage, int i, int *medicineCounter);
char* getTimestamp();