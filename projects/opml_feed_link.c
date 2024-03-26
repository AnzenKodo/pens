#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 450

int main(int argc, char *argv[]) {
    FILE *output_file = fopen(argv[2], "r+");
    if (output_file == NULL) {
        perror("Error opening output file.");
        return 1;
    }

    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        perror("Error opening temp file.");
        return 1;
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, output_file)) {
        fprintf(temp_file, line);

        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, "## Podcast") == 0) {
            fprintf(temp_file, "\n");
            break;
        }
    }

    FILE *opml_file = fopen(argv[1], "r");
    if (opml_file == NULL) {
        perror("Error opening opml file.");
        return 1;
    }

    printf("Written following line in %s:\n", argv[2]);
    while (fgets(line, MAX_LINE_LENGTH, opml_file) != NULL) {
        for (size_t i = 0; i < strlen(line); i++) {
            if (line[i] == 'x' && line[i+7] == '"' && line[i+8] == 'h') {
                putc('-', temp_file); putc(' ', temp_file);
                printf("- ");

                for (size_t j = i+8; line[j] != '"'; j++) {
                    putc(line[j], temp_file);
                    printf("%c", line[j]);
                }

                putc('\n', temp_file);
                printf("\n");
            }
        }
    }

    rewind(temp_file);
    while (fgets(line, MAX_LINE_LENGTH, temp_file)) {
        fprintf(output_file, line);
    }

    fclose(opml_file);
    fclose(output_file);
    fclose(temp_file);
    return 0;
}
