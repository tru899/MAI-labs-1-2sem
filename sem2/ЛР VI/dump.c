#include <stdio.h>
#include <stdlib.h>
#include "student.h"

void usage() {
    printf("Usage: program_name filename.txt filename.bin\n");
}

int read_student(Student *s, FILE *in) {
    int result = fscanf(in, "%s %s %c %d %c %c %d %d %d %d", 
                        s->surname, s->init, &s->sex,
                        &s->school_num, &s->medal, &s->zachet,
                        &s->matan, &s->infa, &s->rus, &s->summary);
    return result == 10;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        usage();
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Error opening input file");
        return 2;
    }

    Student s;

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        perror("Error\n");
        fclose(in);
        return 3;
    }
    while (read_student(&s, in)) {
        fwrite(&s, sizeof(s), 1, out);
    }

    fclose(in);
    fclose(out);

    return 0;
}
