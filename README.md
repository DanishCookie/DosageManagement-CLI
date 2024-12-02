# Project-P1.
This program is designed to give a manageable overview of healthdata associated with a patient/person.

You do not need to add anything before running the program. After you the program is ran, the program will prompt you for a login before using the program. Only users with a viable login gets accsses to the program.

A user login can be added in the pass.json file if one does not have a login already.

The entirity of the program runs in the command line and no GUI or other software is needed.

The program makes use of standard libraries in C and also makes use of a cJSON library to work with the users.json file where all the patients informations currently are stored. We will emphasize that we have NOT programmed/written any of the functions in the cJSON library ourselves, but we use them for handling our JSON data.

The patient information in this program is all fabricated information designed only for testing purposes. The information such as Age, CPR number, Diagnosis, Medicine, Dosage etc. is not real data.


# Project maintenance and upkeeping.
The code will not be updated or maintained after the project has finished. 

# How does the program run?
You run the program på executing the main.c file and then the following will happen:
- The user will be prompted for a login. A correct login is needed, both username and password, before you gain access. (Read above how to add a login if needed). 
- After correct login is input, the user is prompted for a CPR number on a "patient". If a "patient" with a corrosponding CPR is found from the JSON file containing all the "patients", said patient is printed by the print_patient funcion.
- Whenever the information and data from the users.json file is processed or accessed, the encryption and decryption functions are called appropiatly. (The only data being encrypted and decrypted is the information from the users.json file. This is due to the scope of the project). 
- Inside the print_patient function the program have many of the remaining functions called. After the "patient" is printed, the user is prompted for answer if they need help calculating dosage or move on with the program.
If the user needs help, the dosageCalculator function runs.
- Then the user is prompted to input how many medications has been administered to the "patient". This is to ensure a record of medication administered is being kept. If they user for some reason does not administer medicaiton, the user can input 0 medications administered, and the program will move on without placing a timestamp.
- After the user has input the amount of medication administered, the user is prompted to specify which medication from the "patients" medicaion list, has been administered.
- At the end of the "patient", the user of the program is prompted to input whether they want to add a note to the  "patient" or not. If yes is selected, a new JSON files i made where the user can enter a note.
- At the end the user is prompted for either choosing to enter a new "patient" or logout. If the first choice is selected the entire program will run again, other than login. If the answer selected is no, the user is logged out.

**Fail safe**
Each step we found it appropiate to implement a check for a correct input, this has been implemented. As an example, everytime a user is prompted for an input.
