#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "idcheck.h"

static void out_of_memory() {
  printf("Out of memory.\n");
  exit(EXIT_FAILURE);
}

/**
 * Initialize cards.
 */
void idcheck_init_cards(struct idcheck_t *idcheck) {
    if ((idcheck->cards = (char**)malloc(MAX_CARDS*sizeof(char*))) == NULL) {
        out_of_memory();
    }
    for (int i = 0; i<MAX_CARDS; i++) {
        if ((idcheck->cards[i] = (char*)malloc(ID_LENGTH*sizeof(char))) == NULL) {
            out_of_memory();
        }
    }
}

/**
 * Initialize idcheck struct
 */
void idcheck_init(struct idcheck_t *idcheck) {
    idcheck->magnet = NULL;
    idcheck->chip = NULL;
    idcheck_init_cards(idcheck);
}

/**
 * Add magnet code to struct.
 */
void idcheck_add_magnet_code(struct idcheck_t *idcheck, char* code) {
    int len = (int)strlen(code) + 1;

    if (len == ID_LENGTH) {
        if ((idcheck->magnet = (char*)malloc(ID_LENGTH*sizeof(char))) == NULL) {
            out_of_memory();
        }
        strcpy(idcheck->magnet,code);
    }
}

/**
 * Add chip code to struct.
 */
void idcheck_add_chip_code(struct idcheck_t *idcheck, char* code) {
    int len = (int)strlen(code) + 1;

    if (len == ID_LENGTH) {
        if ((idcheck->chip = (char*)malloc(ID_LENGTH*sizeof(char))) == NULL) {
            out_of_memory();
        }
        strcpy(idcheck->chip,code);
    }
}

/**
 * Check if magnet and chip codes matches and return 1 for true 0 for false.
 */
int idcheck_check_codes(struct idcheck_t *idcheck) {
    
    return !strcmp(idcheck->magnet,idcheck->chip);
}

/**
 * Check if magnet code is set.
 */
int idcheck_magnet_is_set(struct idcheck_t *idcheck) {
    if (idcheck->magnet != NULL) {
        return 1;
    }
    return 0;
}

/**
 * Check if chip code is set.
 */
int idcheck_chip_is_set(struct idcheck_t *idcheck) {
    if (idcheck_magnet_is_set(idcheck) && idcheck->chip != NULL) {
        return 1;
    }
    return 0;
}

/**
 * reset idcheck values. Reset value is used for checks
 */
void idcheck_reset_codes(struct idcheck_t *idcheck) {
    free(idcheck->magnet);
    free(idcheck->chip);
    idcheck->magnet = NULL;
    idcheck->chip = NULL;
}

/**
 * Check if string is in array.
 */
int string_in_array(char** array, char* str) {
    for (int i=0; i<MAX_CARDS; i++) {
        if (!strcmp(array[i], str)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Add card to cards array.
 */
void idcheck_add_card(struct idcheck_t *idcheck) {
    int count = 0;
    for (int i=0; i<MAX_CARDS; i++) {
        if (strcmp(idcheck->cards[i],"")) {
            count++;
        }
    }
    strcpy(idcheck->cards[count],idcheck->magnet);
    /* printf("count: %d\n", count); */
}

/**
 * Check if code is already in cards and add it if it isn't.
 * return 1 on success and 0 on error.
 *
 * Assumes that idcheck->magnet has a valid code.
 */
int idcheck_check_cards(struct idcheck_t *idcheck) {
    if (!string_in_array(idcheck->cards, idcheck->magnet)) {
        idcheck_add_card(idcheck);
        return 1;
    }
    return 0;
}
