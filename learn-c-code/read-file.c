#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("a.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        char name[31];
        int id1;
        int id2;
        int operation;

      if(sscanf(line, "%30c%9d%9d%d", name, &id1, &id2, &operation) == 4) {
        printf("%s (%d)\n", name, strlen(name));
        printf("id1 => %d\n", id1);
        printf("id2 =>%d\n", id2);
        printf("operation => %d\n", operation);
      }
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}