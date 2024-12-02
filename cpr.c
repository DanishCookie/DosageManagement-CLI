#include "cpr.h"
#include "patient information.h"
/**
 * @brief This function is used to enter a CPR number and print the patient information
 *
 */
void EnterCPR() {
    char CPRnr[11];  // Make room for 10 digits and the null terminator

    // Input and scan for CPR-number
    printf("Please enter patients CPR-number:\n>");
    scanf("%s", CPRnr);

    // Check if the input matches what a CPR number would be
    int CPRnrInputLength = strlen(CPRnr);
    bool IsDigit = true;

    //runs through every character in the input and checks if it is a digit
    //If one of them is not it sets IsDigit to false and breaks the loop
    for (int i = 0; i < CPRnrInputLength; i++) {
        if (!isdigit(CPRnr[i])) {
            IsDigit = false;
            break;
        }
    }

    //If the IsDigit was set to false or the input is not 10 digits long
    // it posts an error message and runs EnterCPR from the top
    //This avoids having to open the json file to check for the input on patient information.c
    if (!(IsDigit == true && CPRnrInputLength == 10)) {
        printf("Invalid CPR-number\n");
        return EnterCPR();  // Re-enter CPR number
    }
    //Prints patient information
    print_patient(CPRnr);
}