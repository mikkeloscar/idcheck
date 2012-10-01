#ifndef _IDCHECK_H
#define _IDCHECK_H

#define ID_LENGTH 25
#define MAX_CARDS 1000

struct idcheck_t {
    char* magnet;
    char* chip;
    char** cards;
};


/**
 * Initialize idcheck struct
 */
void idcheck_init(struct idcheck_t *idcheck);

/**
 * Add magnet code to struct.
 *
 * Note: magnet and chip just refer to code one and two, they could be switched
 * and it wouldn't matter.
 */
void idcheck_add_magnet_code(struct idcheck_t *idcheck, char* code);

/**
 * Add chip code to struct.
 */
void idcheck_add_chip_code(struct idcheck_t *idcheck, char* code);

/**
 * Check if magnet and chip codes matches and return 1 for true 0 for false.
 */
int idcheck_check_codes(struct idcheck_t *idcheck);

/**
 * Check if magnet code is set.
 */
int idcheck_magnet_is_set(struct idcheck_t *idcheck);

/**
 * Check if chip code is set.
 */
int idcheck_chip_is_set(struct idcheck_t *idcheck);

/**
 * Reset codes.
 */
void idcheck_reset_codes(struct idcheck_t *idcheck);

/**
 * Check if code is already in cards and add it if it isn't.
 * return 1 on success and 0 on error.
 *
 * Assumes that idcheck->magnet has a valid code.
 */
int idcheck_check_cards(struct idcheck_t *idcheck);

#endif
