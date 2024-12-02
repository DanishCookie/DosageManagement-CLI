# Project-P1: Patient Health Data Management System

## Overview
Project-P1 is a command-line program designed to provide healthcare professionals with a manageable overview of patient health data. The system focuses on secure data handling and practical healthcare information management, including medication tracking and patient notes.

## Key Features
- Secure login system
- Patient information lookup via CPR number
- Medication administration tracking
- Patient notes management
- Dosage calculation assistance
- Data encryption for user information

## Technical Specifications
The program is developed in C and utilizes the following:
- Command-line interface (No GUI required)
- cJSON library for JSON data handling
- Standard C libraries
- Local JSON file storage for patient data

## Important Notes
- All patient data in the system is fabricated and intended for testing purposes only
- Patient information includes mock data for:
  - Age
  - CPR number
  - Diagnosis
  - Medicine
  - Dosage
- The cJSON library functions are used as-is, with no custom modifications

## Setup and Access
1. No pre-run setup is required
2. User authentication is mandatory for program access
3. New user credentials can be added via the pass.json file

## Program Flow
When executing main.c, the program follows this sequence:

1. **Login Process**
   - Users must provide valid username and password
   - Authentication is required before accessing any features
   - New logins can be added through the pass.json file

2. **Patient Lookup**
   - After successful login, users enter a patient's CPR number
   - System searches the JSON database for matching records
   - If found, patient information is displayed via the print_patient function

3. **Data Security**
   - Encryption and decryption functions process users.json file data
   - Security measures are implemented specifically for user data protection

4. **Patient Information Management**
   - The print_patient function serves as a hub for various patient-related operations
   - Includes access to dosage calculation assistance when needed

5. **Medication Tracking**
   - Users input the number of medications administered
   - System maintains a medication administration record
   - Zero medications can be recorded without timestamp creation

6. **Medication Selection**
   - Users specify which medications from the patient's list have been administered
   - System updates medication records accordingly

7. **Patient Notes**
   - Option to add notes to patient records
   - Notes are stored in a new JSON file when created

8. **Session Management**
   - Users can choose to:
     - Process another patient (program restarts from patient lookup)
     - Log out of the system

## Error Handling
The program implements comprehensive fail-safe mechanisms:
- Input validation at every user prompt
- Error checking for all critical operations
- Secure data handling procedures

## Project Maintenance
Please note that this project will not receive updates or maintenance after completion.

## Data Privacy Notice
All patient information in this program is fictional and created solely for testing purposes. No real patient data is used or stored in this system.
