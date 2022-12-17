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

void fortune(FILE *ffile, char sep);
void print_usage(void);

char sep = DEFAULT_SEPARATOR;

int main(int argc, char *argv[])
{
	FILE *fp;

	if (argc >= 1) {
		fp = fopen(argv[1] ?: FORTUNE_FILE, "r");
		if (!fp) {
			fprintf(stderr, "%s not found\n", argv[1] ?: FORTUNE_FILE);
			print_usage();
			return EXIT_FAILURE;
		}
	}

	if (argc > 3) {
		print_usage();
		return EXIT_FAILURE;
	}

	if (argc > 2)
		sep = *argv[2];

	fortune(fp, sep);
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

void print_usage()
{
	fprintf(stderr, "usage: fortune [file] [separator]\n");
}
