/*
 * simple fortune(1) implementation with added option to choose a
 * field separator.
 * Author: Ben O'Neill <ben@oneill.sh>
 * License: MIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_SEPARATOR '\n'
#define FORTUNE_FILE "/lib/fortunes"
#define FORTUNE_LEN 2048

void fortune(FILE *, char);
void usage(const char *);

int main(int argc, char *argv[])
{
	FILE *fp;
	char sep = DEFAULT_SEPARATOR;

	switch (argc) {
		case 1:
			fp = fopen(FORTUNE_FILE, "r");
			break;
		case 3:
			sep = argv[2][0];
		case 2:
			fp = fopen(argv[1], "r");
			break;
		default:
			usage(argv[0]);
			return EXIT_FAILURE;
	}

	if (!fp) {
		fprintf(stderr, "File could not be opened\n");
		return EXIT_FAILURE;
	}

	fortune(fp, sep);
	fclose(fp);
	return EXIT_SUCCESS;
}

void fortune(FILE *ffile, char sep) {
	int fnum = 0, buflen = FORTUNE_LEN, cur = 0, resfortune;
	char linebuf[buflen];

	srand(time(NULL));

	/* get number of fields in line */
	while (fgets(linebuf, buflen, ffile)) {
		if (sep == '\n') {
			fnum++;
		} else if (linebuf[0] == sep && strlen(linebuf) == 2) {
			fnum++;
		}
	}

	/* pull random fortune */
	resfortune = rand() % fnum;

	rewind(ffile);
	while (fgets(linebuf, buflen, ffile)) {
		if (sep == '\n' || (linebuf[0] == sep && strlen(linebuf) == 2))
			cur++;

		if (cur == resfortune) {
			if (sep == '\n') {
				printf("%s", linebuf);
				return;
			}
			while (fgets(linebuf, buflen, ffile)) {
				if (linebuf[0] == sep && strlen(linebuf) == 2)
					return;
				printf("%s", linebuf);
			}
		}
	}
}

void usage(const char *argv0) {
	fprintf(stderr, "Usage: %s [file] [separator]\n", argv0);
}
