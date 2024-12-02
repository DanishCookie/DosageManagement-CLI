#include "login.h"
#include "patient information.h"
#include "dosage.h"
#include "cpr.h"
#include "encryption.h"

int main() {
    if (login() == 1) {
        EnterCPR();
    }
    return 0;
}