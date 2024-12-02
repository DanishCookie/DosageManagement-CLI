#include <stdlib.h>
#include <stdio.h>
#include "dosage.h"
#include "smaller functions.h"

#define LIQUID_DOSAGE 2
#define WEIGHT_BASED_DOSAGE 1
/**
 * @brief This function is used to calculate the dosage of a medicine based on the patient's weight
 *
 */
void dosageCalculator() {
    int unitChoice2;
    double* dosage = (double*)malloc(sizeof(double));

    do {
        printf("Press 1 for weight-based dosage calculator, press 2 for liquid dosage calculator.\n>");
        scanf("%d", &unitChoice2);

        // Validate unit choice
        if (unitChoice2 != WEIGHT_BASED_DOSAGE && unitChoice2 != LIQUID_DOSAGE) {
            printf("Invalid choice. Exiting...\n");
            free(dosage);
            return;  // Return without value as the function is void
        }

        // Call the corresponding function based on the user's choice
        if (unitChoice2 == LIQUID_DOSAGE) {
            liquidDosage(unitChoice2);
        } else if (unitChoice2 == WEIGHT_BASED_DOSAGE) {
            weightBasedDosage();
        }
        // Free allocated dosage memory
        free(dosage);
    } while (unitChoice2 != WEIGHT_BASED_DOSAGE && unitChoice2 != LIQUID_DOSAGE);
}