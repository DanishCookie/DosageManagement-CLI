cmake_minimum_required(VERSION 3.26)
project(Project_P1_Final C)

set(CMAKE_C_STANDARD 11)

add_executable(Project_P1_Final
        main.c
        "patient information.c"
        "patient information.h"
        login.c
        login.h
        encryption.c
        encryption.h
        dosage.c
        dosage.h
        cpr.c
        cpr.h
        cJSON.c
        cJSON.h
        timestamp.c
        timestamp.h
        "write patient note.c"
        "write patient note.h"
        "smaller functions.c"
        "smaller functions.h"
)