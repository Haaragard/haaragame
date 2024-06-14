#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_cmd(char **cmd, const char *src) {
    char *tempString = { 0 };

    if ((*cmd)) {
        tempString = (char *) malloc(
            (sizeof(char) * strlen(src))
            + (sizeof(char) * strlen(src))
            + 1
        );

        sprintf(tempString, "%s %s", (*cmd), src);
        free((*cmd));
    } else {
        tempString = (char *) malloc(sizeof(char) * strlen(src) + 1);
        sprintf(tempString, "%s", src);
    }

    (*cmd) = tempString;
}

int main(int argc, char *argv[])
{
    char *cmd = { 0 };

    append_cmd(&cmd, "gcc");
    append_cmd(&cmd, "-Wall -Wextra");
    append_cmd(&cmd, "-o haaragame");
    append_cmd(&cmd, "main.c");
    append_cmd(&cmd, "-lraylib");
    append_cmd(&cmd, "&&");
    append_cmd(&cmd, "./haaragame");

    for (int i = 1; i < argc; i++) {
        append_cmd(&cmd, argv[i]);
    }

    system(cmd);

    return EXIT_SUCCESS;
}