#include "smaller functions.h"
#define LIQUID_DOSAGE 2
#define WEIGHT_BASED_DOSAGE 1
/**
 * @brief This file contains smaller functions that are used in other files
 *
 */
// If it fails to open the file (e.g., due to a file not found), it prints an error message and returns from the function.
void check_file_opening(FILE *fp) {
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }
}

long size_of_file(FILE *fp) {
// Move the file pointer to the end of the file
    fseek(fp, 0, SEEK_END);

// Get the size of the file
    long file_size = ftell(fp);

// Move the file pointer back to the beginning of the file
    fseek(fp, 0, SEEK_SET);
    return file_size;
}

// Dynamically allocate the buffer based on the file size
void check_buffer(char *buffer) {
    if (buffer == NULL) {
        printf("Error: Unable to allocate memory.\n");
        return;
    }
}

// If it fails to parse the JSON, it prints an error message and returns from the function.
void update_json(cJSON *json, FILE *outputFile) {
    char *updatedJsonText = cJSON_Print(json);
    fprintf(outputFile, "%s", updatedJsonText);
    fclose(outputFile);
    free(updatedJsonText);
}


void weightBasedDosage() {
    double* dosage = (double*)malloc(sizeof(double));
    double patientWeight, maxDosage;
    int unitChoice3;

    printf("Enter the patient's weight in kilograms\n>");
    scanf("%lf", &patientWeight);

    printf("Input medicine dosage per kg\n>");
    scanf("%lf", dosage);

    printf("Choose the unit (1 for g, 2 for mg, 3 for mcg)\n>");
    scanf("%d", &unitChoice3);

    printf("Enter the maximum allowable dosage\n>");
    scanf("%lf", &maxDosage);

    while (*dosage > maxDosage) {
        printf("The dosage is too high, please enter a new dosage.\n>");
        scanf("%lf", dosage);
    }

    if (*dosage < maxDosage) {
        switch (unitChoice3) {
            case 1:
                *dosage *= patientWeight;
                printf("The calculated dosage is: %.2lf g.\n", *dosage);
                break;
            case 2:
                *dosage *= patientWeight * 1000;
                printf("The calculated dosage is: %.2lf mg.\n", *dosage);
                break;
            case 3:
                *dosage *= patientWeight * 1000000;
                printf("The calculated dosage is: %.2lf mcg.\n", *dosage);
                break;
            default:
                printf("Invalid unit choice. Exiting...\n");
                free(dosage);
                return;
        }
    }
    free(dosage);
}
// If the user chooses liquid dosage, it asks for the medicine concentration and the dosage, and then calculates the liquid dosage.
void liquidDosage(int unitChoice2) {
    double* dosage = (double*)malloc(sizeof(double));
    double liquidDose, concentration;
    int unitChoice;

    if (unitChoice2 == LIQUID_DOSAGE) {
        printf("Select the unit of measurement for the liquid dosage.\n");
        printf("1 for ml/L, 2 for mg/L, 3 for mcg/L.\n>");
        scanf("%d", &unitChoice);

        printf("Enter the medicine concentration.\n>");
        scanf("%lf", &concentration);

        printf("Enter the dosage.\n>");
        scanf("%lf", dosage);

        switch (unitChoice) {
            case 1:
                liquidDose = *dosage / concentration;
                printf("The liquid dosage is: %.2lf ml.\n", liquidDose);
                break;
            case 2:
                liquidDose = (*dosage / concentration) * 1000;
                printf("The liquid dosage is: %.2lf ml.\n", liquidDose);
                break;
            case 3:
                liquidDose = (*dosage / concentration) * 1000000;
                printf("The liquid dosage is: %.2lf ml.\n", liquidDose);
                break;
            default:
                printf("Invalid unit choice. Exiting...\n");
                free(dosage);
                return;
        }
    }
    free(dosage);
}
// If the user chooses weight-based dosage, it asks for the patient's weight, the medicine dosage per kg, and the maximum allowable dosage, and then calculates the weight-based dosage.
void printMedicineDosage(cJSON *medicine, cJSON *dosage, int i, int *medicineCounter) {
    if (cJSON_IsString(medicine) && (medicine->valuestring != NULL)) {
        printf("Medicine%d: %s\n", i, medicine->valuestring);
        (*medicineCounter)++;
    }

    if (cJSON_IsString(dosage) && (dosage->valuestring != NULL)) {
        printf("Dosage%d: %s\n", i, dosage->valuestring);
    }
}


char* getTimestamp() {
    time_t RawTime;
    struct tm *timestamp;

    // Use time function to get current time
    time(&RawTime);

    //converts the 'RawTime' using localtime and stores it in 'timestamp'
    timestamp = localtime(&RawTime);

    // Create a char string to store the formatted timestamp
    char *timestampString = (char *) malloc(36); // 36 because the timestamp is 35 characters long

    // Use strftime to format the timestamp string
    strftime(timestampString, 36, "\nDATE: %Y/%m-%d %X\nNOTE: ", timestamp);

    // Return the formatted timestamp
    return timestampString;
}