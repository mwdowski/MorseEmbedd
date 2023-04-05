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

morse_decoding_tree_node morse_h = {'H', NULL, NULL};
morse_decoding_tree_node morse_v = {'V', NULL, NULL};
morse_decoding_tree_node morse_f = {'F', NULL, NULL};
morse_decoding_tree_node morse_l = {'L', NULL, NULL};
morse_decoding_tree_node morse_p = {'P', NULL, NULL};
morse_decoding_tree_node morse_j = {'J', NULL, NULL};
morse_decoding_tree_node morse_b = {'B', NULL, NULL};
morse_decoding_tree_node morse_x = {'X', NULL, NULL};
morse_decoding_tree_node morse_c = {'C', NULL, NULL};
morse_decoding_tree_node morse_y = {'Y', NULL, NULL};
morse_decoding_tree_node morse_z = {'Z', NULL, NULL};
morse_decoding_tree_node morse_q = {'Q', NULL, NULL};
morse_decoding_tree_node morse_s = {'S', &morse_h, &morse_v};
morse_decoding_tree_node morse_u = {'U', &morse_f, NULL};
morse_decoding_tree_node morse_r = {'R', &morse_l, NULL};
morse_decoding_tree_node morse_w = {'W', &morse_p, &morse_j};
morse_decoding_tree_node morse_d = {'D', &morse_b, &morse_x};
morse_decoding_tree_node morse_k = {'K', &morse_c, &morse_y};
morse_decoding_tree_node morse_g = {'G', &morse_z, &morse_q};
morse_decoding_tree_node morse_o = {'O', NULL, NULL};
morse_decoding_tree_node morse_i = {'I', &morse_s, &morse_u};
morse_decoding_tree_node morse_a = {'A', &morse_r, &morse_w};
morse_decoding_tree_node morse_n = {'N', &morse_d, &morse_k};
morse_decoding_tree_node morse_m = {'M', &morse_g, &morse_o};
morse_decoding_tree_node morse_e = {'E', &morse_i, &morse_a};
morse_decoding_tree_node morse_t = {'T', &morse_n, &morse_m};
morse_decoding_tree_node morse_root = {ROOT_LETTER, &morse_e, &morse_t};

#endif // _MORSE_H_
