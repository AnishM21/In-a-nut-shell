#include "prompt.h"

extern char cur_dir[1000];
// char *prevDir = (char *)malloc(1000 * sizeof(char));
extern char prevDir[1000];
// char *pseudo_dir = malloc(1000 * sizeof(char));
extern char pseudo_dir[1000];
extern struct utsname check;
extern char* buffer;
char sys_name[256];

char *host_name()
{
    char *bufer = malloc(256 * sizeof(char));
    int hostname = getlogin_r(bufer, 256);

    if (hostname == -1)
    {
        printf("Error!\n");
        exit(1);
    }
    else
    {
        return bufer;
    }
}

void prompt()
{
    getcwd(cur_dir, 1000);
    gethostname(sys_name, 256);
    // printf("Previous directory-%s Current Directory-%s\n", prevDir, cur_dir);

    if (strcmp(cur_dir, pseudo_dir) == 0)
    {
        printf("<%s@%s:~>", buffer, sys_name);
    }
    else
    {
        bool finish = true;
        for (int i = 0; i < strlen(pseudo_dir); i++)
        {
            if (cur_dir[i] != pseudo_dir[i])
            {
                finish = false;
                break;
            }
        }
        if (!finish)
        {
            printf("<%s@%s:%s>", buffer, sys_name, cur_dir);
        }
        else
        {
            char copy[100];
            int u = 1;
            strcpy(copy, "~");
            for (int i = strlen(pseudo_dir); i < strlen(cur_dir); i++)
            {
                copy[u] = cur_dir[i];
                u++;
            }
            printf("<%s@%s:%s>", buffer, sys_name, copy);
        }
    }
}
