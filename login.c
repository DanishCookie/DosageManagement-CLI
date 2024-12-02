#include "login.h"
/**
 * This function is used to login to the system.
 * @return 1 if login is successful, 0 if login is unsuccessful, -1 if there is an error.
 */
int login() {
    FILE *fileptr;
    char *buffer;
    long filelen;
    char username[25], password[25];
    int logintrack = 0;

    // loop until login is successful
    while (logintrack != 1) {
        // get username and password from user
        printf("Input login username\n>");
        scanf("%s", username);
        printf("Input login password\n>");
        scanf("%s", password);

        // Open pass.json file and read it (r). If fail then print error.
        fileptr = fopen("pass.json", "r");
        check_file_opening(fileptr);

        // get file length
        fseek(fileptr, 0, SEEK_END);
        filelen = ftell(fileptr);
        rewind(fileptr);

        // allocate memory for file content
        buffer = (char *)malloc((filelen + 1) * sizeof(char));
        if (buffer == NULL) {
            perror("Error allocating memory for file content");
            fclose(fileptr);
            return -1;
        }

        // read file content into buffer (buffer contains the whole file now)
        fread(buffer, filelen, 1, fileptr);
        // close the file
        fclose(fileptr);

        // add null terminator to the end of the buffer
        buffer[filelen] = '\0';

        // parse the json file (convert it to something readable) using cJson_Parse function
        cJSON *json = cJSON_Parse(buffer);
        if (json == NULL) {
            const char *error_ptr = cJSON_GetErrorPtr();
            if (error_ptr != NULL) {
                fprintf(stderr, "Error before: %s\n", error_ptr);
            }
            // free memory
            free(buffer);
            return -1;
        }

        // get the users array from the json file
        int found = 0;
        cJSON *users = cJSON_GetObjectItemCaseSensitive(json, "Users");
        cJSON *user;

        // loop through the users array and check if the username and password matches
        cJSON_ArrayForEach(user, users) {
            cJSON *json_username = cJSON_GetObjectItemCaseSensitive(user, "Username");
            cJSON *json_password = cJSON_GetObjectItemCaseSensitive(user, "Password");
            // check if the username matches
            if (cJSON_IsString(json_username) && (json_username->valuestring != NULL)) {
                if (strcmp(username, json_username->valuestring) == 0) {
                    found = 1;
                    if (cJSON_IsString(json_password) && (json_password->valuestring != NULL)) {
                        if (strcmp(password, json_password->valuestring) == 0) {
                            printf("Login successful.\n\n");
                            logintrack = 1;
                            return 1;
                        } else {
                            printf("Password incorrect.\n");
                        }
                    }
                    break;
                }
            }
        }

        // if username is not found in the json file then print error
        if (!found) {
            printf("Incorrect login.\n");
        }
        // free memory
        cJSON_Delete(json);
        free(buffer);
    }

    return 0;
}