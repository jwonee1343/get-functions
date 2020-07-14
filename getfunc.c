#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define print_error(...)		fprintf(stderr, __VA_ARGS__)

int main(int argc, char *argv[])
{
	FILE *fp;

	char buf[BUFSIZ];

	char *space;
	char *alpa;
	char *br_open;
	char *br_close;

	if (argc < 2) {
		print_error("Usage: %s {file_path}\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (!fp) {
		print_error("Can't open the file (file: %s)\n", argv[1]);
		exit(1);
	}

	if (feof(fp)) {
		print_error("The file is empty (file: %s)\n", argv[1]);
		fclose(fp);
		exit(1);
	}

	while (fgets(buf, BUFSIZ, fp) > 0) {
		if ((buf[0] >= 'a' && buf[0] <= 'z')
				|| (buf[0] >= 'A' && buf[0] <= 'Z')) {
			space = strstr(buf, " ");
			br_open = strstr(buf, "(");
			br_close = strstr(buf, ")");
			if (!space || !br_open || !br_close)
				continue;

			if (space > br_open || br_open > br_close)
				continue;

			printf("%s\n", buf);
		}
	}

	fclose(fp);
	exit(0);
}
