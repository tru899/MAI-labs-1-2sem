#include "student.h"
#include<string.h>

void usage() {
    printf("Usage: program_name filename [-f | -p <user_parameter>]\n");
}

void table_header() {
    printf("%-15s|%-4s| %-4s|%-6s|%-5s|%-5s|%-5s|%-3s|%-3s |%-4s|\n", 
           "Surname", "Init", "Sex", "School", "Medal", "Zachet", 
           "Matan", "Infa", "Rus", "Summary");
    printf("------------------------------------------------------------------------\n");
}

void student_print(Student *s) {
    printf("%-15s| %-3s|  %-3c| %-5d|  %-3c|   %-3c|  %-3d| %-3d| %-3d|  %-5d|\n",
            s->surname, s->init, s->sex, s->school_num, 
            s->medal, s->zachet, s->matan, s->infa, 
            s->rus, s->summary);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        usage();
        return 1;
    }
    
    Student s;
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Error opening input file");
        return 2;
    }

    FILE *out = fopen("temp.bin", "w");
    if (!out) {
        perror("Error opening output file");
        fclose(in);
        return 3;
    }

    int p_value = 0;
    int flag_found = 0;

    if (strcmp(argv[2], "-f") == 0) {
        table_header();
        while (fread(&s, sizeof(s), 1, in) == 1) {
            student_print(&s);
            fwrite(&s, sizeof(s), 1, out);
        }
    }
    else if (argc == 4 && strcmp(argv[2], "-p") == 0) {
        p_value = atoi(argv[3]);
        table_header();
        while (fread(&s, sizeof(s), 1, in) == 1) {
            if (s.sex == 'M' && s.medal == 'Y' && (s.matan + s.infa + s.rus) < p_value) {
                student_print(&s);
                flag_found = 1;
            }
        }
        
        if (!flag_found) {
            printf("No students with medal and summary < %d\n", p_value);
            }

    } else {
        usage();
    }

    fclose(in);
    fclose(out);
    return 0;
}
