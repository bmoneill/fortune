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

#define DEFAULT_SEPARATOR '%'
#define FORTUNE_FILE "/lib/fortunes"
#define FORTUNE_LEN 2048

#define USE(x,y) y ? y : x

void fortune(FILE *ffile, char sep);

int main(int argc, char *argv[])
{
	char *ffile = USE(FORTUNE_FILE, argv[1]);
	FILE *fp = fopen(ffile, "r");

	if (!fp) {
		fprintf(stderr, "%s not found\n", ffile);
		return EXIT_FAILURE;
	}

	if (argc > 3) {
		fprintf(stderr, "usage: fortune [file] [separator]\n");
		return EXIT_FAILURE;
	}

	fortune(fp, USE(*argv[2], DEFAULT_SEPARATOR));
	fclose(fp);

	return EXIT_SUCCESS;
}

void fortune(FILE *ffile, char sep)
{
	int fnum = 0, buflen = FORTUNE_LEN, cur = 0, resfortune;
	char linebuf[buflen];

	srand(time(NULL));

	/* get number of fields in character */
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
