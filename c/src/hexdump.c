#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//                  1         2         3         4         5         6 7
//        01234567890123456789012345678901234567890123456789012345678901234567890
// label: xx xx xx xx xx xx xx xx - xx xx xx xx xx xx xx xx  ................
//
// 67 characters per line including \n, but not including the label.
// ascii starts at 51

static int
dump_size(const char *label, int bytes)
{
	int prefix = 0;

	if (label) {
		prefix = strlen(label) + strlen(": ");
	}

	return (prefix + 67) * (bytes / 16) + 1;
}

// hexdump_to_string returns a newly allocated string with the dumped
// representation of the data. The caller is responsible for calling free().
char *
hexdump_to_string(const char *label, const void *data, int bytes)
{
	// label is optional
	assert(data);
	assert(bytes);

	int buflen = dump_size(label, bytes);

	char *dump = (char *)malloc(buflen);
	if (!dump) {
		return NULL;
	}

	memset(dump, (int)' ', buflen);

	char *hex = dump, *ascii = NULL;

	for (int i = 0; i < bytes; i += 16) {
		if (i > 0) {
			*hex++ = '\n';
		}
		if (label) {
			hex += sprintf(hex, "%s: ", label);
		}

		ascii = hex + 51;

		for (int j = 0; j < 16 && (j + i) < buflen; j++) {
			unsigned char byte = ((unsigned char *)data)[i + j];

			if (j == 8) {
				hex += sprintf(hex, "- ");
			}

			hex += sprintf(hex, "%02x ", byte);
			if (isprint(byte)) {
				*ascii++ = byte;
			} else {
				*ascii++ = '.';
			}
		}
	}

	*hex = '\0';

	return dump; // caller must free
}

void
hexdump_to_file(FILE *fout, const char *label, const void *data, int bytes)
{
	char *s = hexdump_to_string(label, data, bytes);

	if (s) {
		fprintf(fout, "%s\n", s);
		free(s);
	}
}

void
hexdump(const char *label, const void *data, int bytes)
{
	hexdump_to_file(stdout, label, data, bytes);
}
