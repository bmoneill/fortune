/*
 * simple fortune(6) implementation with added option to choose a
 * field separator.
 * Author: Ben O'Neill <ben@oneill.sh>
 * License: MIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_SEPARATOR '\n'
#define DEFAULT_FORTUNE_FILE "/lib/fortunes"

static int  file_len(FILE *);
static void fortune(char *, int, int, int);
static char *load_file(const char *, char, int *, int *);
static void usage(const char *);

int main(int argc, char *argv[])
{
    const char *path = DEFAULT_FORTUNE_FILE;
	char sep = DEFAULT_SEPARATOR;
    int len = 0;
    int count = 0;
    int fortuneIndex = 0;

	switch (argc) {
		case 1: break;
		case 3: sep = argv[2][0];
		case 2: path = argv[1]; break;
		default:
			usage(argv[0]);
			return EXIT_FAILURE;
	}

    srand(time(NULL));
    char *buf = load_file(path, sep, &len, &count);
    fortuneIndex = rand() % count;
    fortune(buf, len, count, fortuneIndex);

    free(buf);
	return EXIT_SUCCESS;
}

static int file_len(FILE *ffile) {
    int len = 0;
    char c;

    while ((c = fgetc(ffile)) != EOF) {
        len++;
    }

    rewind(ffile);
    return len;
}

static void fortune(char *buf, int bufLength, int fortuneCount, int index) {
    int cur = 0;
    for (int i = 0; i < bufLength; i++) {
        if (buf[i] == '\0') {
            cur++;
        }

        if (cur == index) {
            int end = i + 1;
            while (buf[end] != '\0' && buf[end] != '\n') {
                end++;
            }

            buf[end] = '\0';
            if (index == 0) {
                printf("%s\n", buf);
            } else {
                printf("%s\n", &(buf[i + 1]));
            }
            return;
        }
    }
}

static char *load_file(const char *path, char sep, int *len, int *count) {
    char *dst;
    FILE *ffile;
    count[0] = 0;

    ffile = fopen(path, "r");
    if (!ffile) {
        fprintf(stderr, "Could not open file: %s\n", path);
        exit(EXIT_FAILURE);
    }

    len[0] = file_len(ffile);

    dst = malloc(*len + 1);
    if (!dst) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(ffile);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *len; i++) {
        char c = fgetc(ffile);
        if (c == EOF) {
            break;
        }

        dst[i] = c;

        if (dst[i] == sep) {
            count[0]++;
            dst[i] = '\0';
        }
    }

    fclose(ffile);
    return dst;
}

static void usage(const char *argv0) {
	fprintf(stderr, "Usage: %s [file] [separator]\n", argv0);
}
