#ifndef _MORSE_H_
#define _MORSE_H_

#include <stdlib.h>

typedef enum morse_char
{
    SHORT,
    LONG,
    END,
    CHAR_SPACE,
    WORD_SPACE,
} morse_char;

typedef struct morse_decoding_tree_node
{
    char letter;
    struct morse_decoding_tree_node *short_child;
    struct morse_decoding_tree_node *long_child;
} morse_decoding_tree_node;

static const char ROOT_LETTER = '?';

static morse_decoding_tree_node morse_h = {'H', NULL, NULL};
static morse_decoding_tree_node morse_v = {'V', NULL, NULL};
static morse_decoding_tree_node morse_f = {'F', NULL, NULL};
static morse_decoding_tree_node morse_l = {'L', NULL, NULL};
static morse_decoding_tree_node morse_p = {'P', NULL, NULL};
static morse_decoding_tree_node morse_j = {'J', NULL, NULL};
static morse_decoding_tree_node morse_b = {'B', NULL, NULL};
static morse_decoding_tree_node morse_x = {'X', NULL, NULL};
static morse_decoding_tree_node morse_c = {'C', NULL, NULL};
static morse_decoding_tree_node morse_y = {'Y', NULL, NULL};
static morse_decoding_tree_node morse_z = {'Z', NULL, NULL};
static morse_decoding_tree_node morse_q = {'Q', NULL, NULL};
static morse_decoding_tree_node morse_s = {'S', &morse_h, &morse_v};
static morse_decoding_tree_node morse_u = {'U', &morse_f, NULL};
static morse_decoding_tree_node morse_r = {'R', &morse_l, NULL};
static morse_decoding_tree_node morse_w = {'W', &morse_p, &morse_j};
static morse_decoding_tree_node morse_d = {'D', &morse_b, &morse_x};
static morse_decoding_tree_node morse_k = {'K', &morse_c, &morse_y};
static morse_decoding_tree_node morse_g = {'G', &morse_z, &morse_q};
static morse_decoding_tree_node morse_o = {'O', NULL, NULL};
static morse_decoding_tree_node morse_i = {'I', &morse_s, &morse_u};
static morse_decoding_tree_node morse_a = {'A', &morse_r, &morse_w};
static morse_decoding_tree_node morse_n = {'N', &morse_d, &morse_k};
static morse_decoding_tree_node morse_m = {'M', &morse_g, &morse_o};
static morse_decoding_tree_node morse_e = {'E', &morse_i, &morse_a};
static morse_decoding_tree_node morse_t = {'T', &morse_n, &morse_m};
static morse_decoding_tree_node morse_root = {ROOT_LETTER, &morse_e, &morse_t};

const morse_char MORSE_A[] = {SHORT, LONG, END};
const morse_char MORSE_B[] = {LONG, SHORT, SHORT, SHORT, END};
const morse_char MORSE_C[] = {LONG, SHORT, LONG, SHORT, END};
const morse_char MORSE_D[] = {LONG, SHORT, SHORT, END};
const morse_char MORSE_E[] = {SHORT, END};
const morse_char MORSE_F[] = {SHORT, SHORT, LONG, SHORT, END};
const morse_char MORSE_G[] = {LONG, LONG, SHORT, END};
const morse_char MORSE_H[] = {SHORT, SHORT, SHORT, SHORT, END};
const morse_char MORSE_I[] = {SHORT, SHORT, END};
const morse_char MORSE_J[] = {SHORT, LONG, LONG, LONG, END};
const morse_char MORSE_K[] = {LONG, SHORT, LONG, END};
const morse_char MORSE_L[] = {SHORT, LONG, SHORT, SHORT, END};
const morse_char MORSE_M[] = {LONG, LONG, END};
const morse_char MORSE_N[] = {LONG, SHORT, END};
const morse_char MORSE_O[] = {LONG, LONG, LONG, END};
const morse_char MORSE_P[] = {SHORT, LONG, LONG, SHORT, END};
const morse_char MORSE_Q[] = {LONG, LONG, SHORT, LONG, END};
const morse_char MORSE_R[] = {SHORT, LONG, SHORT, END};
const morse_char MORSE_S[] = {SHORT, SHORT, SHORT, END};
const morse_char MORSE_T[] = {LONG, END};
const morse_char MORSE_U[] = {SHORT, SHORT, LONG, END};
const morse_char MORSE_V[] = {SHORT, SHORT, SHORT, LONG, END};
const morse_char MORSE_W[] = {SHORT, LONG, LONG, END};
const morse_char MORSE_X[] = {LONG, SHORT, SHORT, LONG, END};
const morse_char MORSE_Y[] = {LONG, SHORT, LONG, LONG, END};
const morse_char MORSE_Z[] = {LONG, LONG, SHORT, SHORT, END};

#endif // _MORSE_H_
