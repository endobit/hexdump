#ifndef __hexdump_h
#define __hexdump_h

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void hexdump(const char *label, const void *data, int bytes);
void hexdump_to_file(FILE *fout, const char *label, const void *data, int bytes);
char *hexdump_to_string(const char *label, const void *data, int bytes);

#ifdef __cplusplus
}
#endif

#endif // __hexdump_h
