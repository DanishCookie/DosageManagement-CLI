#include "timestamp.h"
/**
 * @brief This function is used to add a timestamp to a field in a JSON object
 *
 * @param userObject The JSON object to add the timestamp to
 * @param fieldName The name of the field to add the timestamp to
 */
// Function to add timestamp to an arbitrary field in a JSON object
void addTimestampToField(cJSON *userObject, const char *fieldName) {
    // Locate the specified field in the cJSON object
    cJSON *fieldObj = cJSON_GetObjectItemCaseSensitive(userObject, fieldName);

    if (cJSON_IsString(fieldObj)) {
        // Retrieve the existing string value
        char *existingValue = cJSON_GetStringValue(fieldObj);

        // Append the timestamp to the existing string between the quotes
        time_t t;
        time(&t);
        char timestamp[100];
        sprintf(timestamp, " : Time of administration: %s", ctime(&t));

        char *newValue = (char *) malloc(strlen(existingValue) + strlen(timestamp) + 1);
        strcpy(newValue, existingValue);
        strcat(newValue, timestamp);
        newValue[strcspn(newValue, "\n")] = '\0';

        // Replace the existing string with the new value
        cJSON_ReplaceItemInObjectCaseSensitive(userObject, fieldName, cJSON_CreateString(newValue));

        // Free the allocated memory
        free(newValue);
    }
}