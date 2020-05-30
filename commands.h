#ifndef COMMANDS_H
#define COMMANDS_H

#define ARRAY_CONCAT(TYPE, A, An, B, Bn) \
(TYPE *)concatArray((const void *)(A), (An), (const void *)(B), (Bn), sizeof(TYPE));

/**
 * Concat two arrays
 * @param a first array
 * @param an size of first array
 * @param b second array
 * @param bn size of second array
 * @param s size of type contained in array
 * @return array concatened
 */
void *concatArray(const void *a, size_t an, const void *b, size_t bn, size_t s) {
  char *p = malloc(s * (an + bn));
  memcpy(p, a, an*s);
  memcpy(p + an*s, b, bn*s);
  return p;
}

// Commands
const int common[] = { 3150, 1700, 300, 500, 300, 500, 300, 1300, 300, 500, 300, 1300, 300, 500, 300, 500, 300, 500, 300, 1300, 300, 1300, 300, 500, 300, 500, 300, 500, 300, 1300, 300, 1300, 300, 500, 300, 450, 350, 500, 300, 500, 300, 500, 300, 500, 300, 500, 350, 450, 350, 500, 300, 500, 300, 500, 300, 500, 300, 500, 350, 1300, 300, 500, 300, 500, 300, 500, 300, 500, 350, 450, 350, 500, 300, 500, 300, 1300, 300, 500, 350, 450, 350, 500, 300 };
const int turn_off_part[] = { 500, 300, 1300, 300, 500, 350, 450, 350, 500, 300, 500, 300, 500, 300, 500, 300 };
const int toggle_airclean_part[] = { 550, 250, 550, 300, 500, 300, 500, 300, 1350, 250, 550,  300, 1300, 300, 1300, 300 };
const int toggle_swing_part[] = { 1300, 300, 500,  300, 1300, 350, 1300, 300, 500, 300, 1300, 350, 1250, 350, 500, 300 };
const int set_wing_part[] = { 500, 300, 500, 350, 1300, 300, 1300, 300, 500, 300, 1300, 350, 1300, 300, 500, 300 };

#endif
