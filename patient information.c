#include "patient information.h"
#include "write patient note.h"
#include "encryption.h"

/**
 * @brief This function is used to enter a CPR number and print the patient information
 *
 */

void print_patient(const char *cpr_to_find) {
    // This code attempts to open the file "users.json" for reading.
    // If it fails to open the file (e.g., due to a file not found), it prints an error message and returns from the function.
    enryptionAndDecryption("users.json");
    FILE *fp = fopen("decrypted_output.json", "r");
    check_file_opening(fp);

    size_of_file(fp);

    // Dynamically allocate the buffer based on the file size
    char *buffer = (char *) malloc(size_of_file(fp) + 1);
    check_buffer(buffer);

    // Read the contents of the file into the buffer
    size_t len = fread(buffer, 1, size_of_file(fp), fp);
    buffer[len] = '\0'; // Null-terminate the buffer
    fclose(fp);

    // This part of the code extracts the "Users" array from the parsed JSON data.
    // If "Users" is an array, it proceeds to iterate through its elements using a for loop.
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return;
    }

    // Find the JSON object with the specified "CPR"
    cJSON *users = cJSON_GetObjectItemCaseSensitive(json, "Users");
    if (cJSON_IsArray(users)) {
        bool HasPrinted = 0;
        for (int i = 0; i < cJSON_GetArraySize(users); i++) {
            cJSON *patient = cJSON_GetArrayItem(users, i);
            cJSON *cpr = cJSON_GetObjectItemCaseSensitive(patient, "CPR");

            //The atof funktion converts the array of chars (String) into a float
            if (cJSON_IsNumber(cpr) && (cpr->valuedouble == atof(cpr_to_find))) {
                cJSON *name = cJSON_GetObjectItemCaseSensitive(patient, "Name");
                cJSON *age = cJSON_GetObjectItemCaseSensitive(patient, "Age");
                cJSON *gender = cJSON_GetObjectItemCaseSensitive(patient, "Gender");
                cJSON *diagnosis = cJSON_GetObjectItemCaseSensitive(patient, "Diagnosis");

                //int which is used as a counter for the amount of medication that a patient can be given
                int medicineCounter = 0;
                //If the medicine is not NULL, the counter is increased by 1

                if (cJSON_IsString(name) && (name->valuestring != NULL)) {
                    printf("Name: %s\n", name->valuestring);
                    //If the CPR number has an assosiated name (as in it has information) the program prints data
                    // and sets the bool to TRUE to reflect that
                    HasPrinted = 1;
                }

                if (cJSON_IsNumber(age)) {
                    printf("Age: %d\n", age->valueint);
                }
                if (cJSON_IsString(gender) && (gender->valuestring != NULL)) {
                    printf("Gender: %s\n", gender->valuestring);
                }
                if (cJSON_IsString(diagnosis) && (diagnosis->valuestring != NULL)) {
                    printf("Diagnosis: %s\n", diagnosis->valuestring);
                }

                //Prints the medicine and dosage for the patient
                for (int i = 1; i <= 8; i++) {
                    char medicineKey[15], dosageKey[15];

                    sprintf(medicineKey, "Medicine%d", i);
                    sprintf(dosageKey, "Dosage%d", i);

                    cJSON *medicine = cJSON_GetObjectItemCaseSensitive(patient, medicineKey);
                    cJSON *dosage = cJSON_GetObjectItemCaseSensitive(patient, dosageKey);

                    printMedicineDosage(medicine, dosage, i, &medicineCounter);
                }

                //Asks the user if they need help calculating the dosage
                printf("\n\n\nDo you need help calculating the dosage?\n");
                printf("Type [Y]es or [N]o\n>");
                char help;
                scanf(" %c", &help);
                if (help == 'Y' || help == 'y') {
                    dosageCalculator();
                }

                //Asks the user how many different medications they have administered
                int valg = 0;
                printf("\n\nHow many different medications have you administered?\n>");
                scanf("%d", &valg);
                if(medicineCounter < valg){
                    printf("You have entered a number that is higher than the amount of medicine the patient can be given\n");
                    printf("Please enter a number between 0 and %d\n", medicineCounter);
                    scanf("%d", &valg);
                }

                if(valg>0){
                    FILE *outputFile = fopen("decrypted_output.json", "w");
                    check_file_opening(outputFile);
                    //For loop that runs the amount of times the user has entered in the previous scanf
                    for (int j = 0; j < valg; ++j) {
                        char medicine[100];
                        printf("Please enter the medicine you have administered\n>");
                        scanf("%s", medicine);
                        medicine[0] = toupper(medicine[0]);

                        //Adds a timestamp to the medicine
                        addTimestampToField(patient, medicine);
                        printf("Timestamp added to %s\n\n", medicine);
                        update_json(json, outputFile);

                    }
                    fclose(outputFile);
                    enncrypt_function_with_key();
                    cJSON_Delete(patient);
                    break;  // Exit the loop once the desired "CPR" is found
                }}
        }
        //If the CPR number does not have information to print, the program prompts the user to reenter CPR.number
        // so we can insert an error message and run EnterCPR again
        if (HasPrinted == 0) {
            printf("CPR-number not in system\n");
            EnterCPR();
        }
    } else {
        //If no "Users" is found in the JSON file, prints error message.
        printf("Error: 'Users' is not an array in the JSON.\n");
    }

    //Makes a space between the patients printed info and the printf below.
    for (int t = 0; t < 2; t++) {
        printf("\n");
    }
    //Asks the user if they want to add a note to the patient file
    char NoteChoice;
    printf("Do you want to add a note to the patient file? [Y/N]\n>");

    do {
        scanf(" %c", &NoteChoice);

        if (NoteChoice == 'Y' || NoteChoice == 'y') {
            write_note(cpr_to_find);
            break;
        } else if (NoteChoice == 'N' || NoteChoice == 'n') {
            break;
        }
        else {
            printf("You have not chosen a valid option. Please choose a valid option [Y/N].\n");
        }
    } while (NoteChoice != "Y" || NoteChoice != "N" || NoteChoice != "y" || NoteChoice != "n");


    int valg;
    printf("Do you want to find a new person or log out?\nType 1 for new person or 2 for log out\n>");

    do {
        //Scans the user input based on the previous printed message and acts on the input in the switch case,
        // either continuing to the next patient 1 or log out 2
        scanf(" %d", &valg);
        char CPRnr[11];
        //Switch case, if input is 1, it runs EnterCPR
        switch (valg) {
            case 1:
                //Makes free lines between the previous and the current patient information.
                for (int t = 0; t < 8; t++) {
                    printf("\n");
                }
                EnterCPR();
                break;
                //if 2 moves user to log-in screen and forward to EnterCPR when user has logged in again succesfully
            case 2:
                printf("You are being logged out \n");
                login();
                EnterCPR();
                break;
                //If user types something that is not 1 or 2, runs an error message
            default:
                printf("You have not chosen a valid option. Please choose 1 or 2.\n");
        }
        //Because it is in a do while function, if it was not broken (runs case 1 or 2)
        // , the while is still true and runs again
    } while (valg != 1 && valg != 2);

    // Delete the JSON object
    cJSON_Delete(json);
    //Free the memory for the buffer
    free(buffer);
}