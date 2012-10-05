#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "idcheck.h"

#define NC          "\033[0m"

#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"

/**
 * Check the codes and output the result.
 */
void check_result(struct idcheck_t *idcheck) {
    if (idcheck_check_codes(idcheck)) {
        // success
        if (!idcheck_check_cards(idcheck)) {
            printf(YELLOW "FOUND" NC "\n");
        } else {
            printf(GREEN "success" NC "\n");
        }
    } else {
        // error
        printf(RED "error" NC "\n");
    }
    idcheck_reset_codes(idcheck);
}

/**
 * Check & handle input.
 */
void check_input(struct idcheck_t *idcheck, char* input) {
    if (idcheck_magnet_is_set(idcheck)) {
        if (idcheck_chip_is_set(idcheck)) {
            check_result(idcheck);
        } else {
            idcheck_add_chip_code(idcheck, input);
            check_result(idcheck);
        }
    } else {
        idcheck_add_magnet_code(idcheck, input);
    }
}


int main() {
    struct idcheck_t idcheck;
    char in[ID_LENGTH];
    int ch; // used to flush stdin

    idcheck_init(&idcheck);

    while (1) {
        /* read a line */
        fgets(in,ID_LENGTH,stdin); 

        /* exit on "quit" */
        if (!strcmp(in,"quit\n")) {
            exit(0);
        }
        
        if (strlen(in)+1 >= ID_LENGTH) {

            check_input(&idcheck, in);

            // flush stdin
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
    return EXIT_SUCCESS;
}
