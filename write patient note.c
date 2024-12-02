#include "write patient note.h"
#include "smaller functions.h"
/**
 * @brief This function is used to write a note to a patient's file
 *
 */
void write_note(const char InputCPR[11]) {
    //instead of using atof multiple times further down, simply creating a double with the atof of inputCPR to refer to instead
    double PatientCPR = atof(InputCPR);

    // open the JSON file
    FILE *fp = fopen("patient_notes.json", "r");
    //If file read is empty, run error
    check_file_opening(fp);

    long file_size = size_of_file(fp);

    //create buffer
    char* buffer = (char *)malloc(file_size * 1);
    check_buffer(buffer);

    int len = fread(buffer, 1, file_size, fp);
    buffer[len] = '\0'; // Null-terminate the buffer
    fclose(fp);

    // parse the JSON data into 'json'
    cJSON *json = cJSON_Parse(buffer);
    // if 'json' is empty, run error
    if (json == NULL) {
        // get error message if possible
        const char *error_ptr = cJSON_GetErrorPtr();
        // if we get an error message, print it
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return;
    }

    //create variables to 'extract' from file
        //Patient_object is extracting which object (if any) has the InputCPR
    int patient_object;
        //If the CPR is in the file, sets bool to 1, allows for different operations based on
        // if it needs to add item to an existing object or create a new to add to
    bool patient_in_system = 0;

    //To check if the patient is registered in the notes system, check if the given CPR can be read in the file
    cJSON *patients = cJSON_GetObjectItemCaseSensitive(json, "Patients");
    //makes sure the item is an array, else print error message
    if (cJSON_IsArray(patients)) {
        //loops through each object in the array
        for (int i = 0; i < cJSON_GetArraySize(patients); i++) {
            //extracts "CPR" item from the current object
            cJSON *patient = cJSON_GetArrayItem(patients, i);
            cJSON *cpr = cJSON_GetObjectItemCaseSensitive(patient, "CPR");

            //check if the extracted "CPR" item == Input CPR
            if (cJSON_IsNumber(cpr) && (cpr->valuedouble == PatientCPR)) {
                //If they match, reflect TRUE and index in the variables
                patient_in_system = 1;
                patient_object = i;
                //Stop the loop with break
                break;
            }
        }
    } else {
        printf("Error: 'Patients' is not an array in the JSON.\n");
    }

    //Scan for patient note (limited to 100, may change if needed)
    char Note[100];
    printf("Please type error or note:\n");
    //scans user input until it meets a new line, allows it to scan full sentences (but not paragraphs)
    scanf(" %[^\n]", Note);

    //Get current timestamp
    char *timestamp = getTimestamp();

    char PatientNote[120] = "";

    strcat(PatientNote, timestamp);
    strcat(PatientNote, Note);


    //If the patient CPR is not in system, it needs to add a new object and note to the new object
    if (patient_in_system == 0) {
        //Creates new object "NewPatient"
        cJSON *NewPatient = cJSON_CreateObject();
        //Adds both CPR number and the patient note to the new object
        cJSON_AddNumberToObject(NewPatient, "CPR", PatientCPR);
        cJSON_AddStringToObject(NewPatient, "NOTE", PatientNote);

        //adds the new object to the array
        cJSON_AddItemToArray(patients, NewPatient);

        printf("Patient not already in file.\nCreating file for new patient.\nAdding note to patient file.\n");

    //if patient is in system, need only add new item to it
    } else if (patient_in_system == 1) {
        //Finds the object from the array and the object index extracted from loop earlier
        cJSON *patient = cJSON_GetArrayItem(patients, patient_object);
        //Adds patient note to the existing object
        cJSON_AddStringToObject(patient, "NOTE", PatientNote);

        printf("Adding note to patient file.\n");
    //If somehow neither is true, prints error message
    } else {
        printf("ERROR: couldn't add note to file");
    }

    //Makes a string to put it in file
    char *json_str = cJSON_Print(json);

    // Open the file (using w only updates after program stopped, r+ can do it live for some reason)
    fp = fopen("patient_notes.json", "r+");
    check_file_opening(fopen);

    //when using r+ set file pointer to start of file, when writing to file it overwrites existing file
    fseek(fp, 0, SEEK_SET);

    fputs(json_str, fp);
    fclose(fp);

    // free the buffer, timestamp, JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);
    free(timestamp);
    free(buffer);
    return;
}



