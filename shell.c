#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <termios.h>
#include <ctype.h>
#include <unistd.h>
#include "cd.h"
#include "discover.h"
#include "echo.h"
#include "execute.h"
#include "foreground.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "prompt.h"
#include "pwd.h"
#include "redirection.h"
#include "signalHandler.h"
#include "piping.h"

extern int errno;

int shellPID;

char firstInput[1000], input[1000][1000], command[100][1000];
char decoy_pseudo_dir[1000];
int com_count = 0, comm_count = 0;

// char *cur_dir = (char *)malloc(1000 * sizeof(char));
char cur_dir[1000];
// char *prevDir = (char *)malloc(1000 * sizeof(char));
char prevDir[1000];
// char *pseudo_dir = malloc(1000 * sizeof(char));
char pseudo_dir[1000];
struct utsname check;
char *buffer;
// char hist_file_loc[strlen(cur_dir) + 13];
char hist_file_loc[256];

// autocompletion code
void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void autocomplete()
{
    int l = strlen(firstInput);
    l--;
    while (l >= 0 && (firstInput[l] != ' '))
    {
        l--;
    }
    l++;
    int ptr = l;
    char last_part[256] = {'\0'};
    int i = 0;
    while ((l < strlen(firstInput)))
    {
        last_part[i] = firstInput[l];
        i++;
        l++;
    }
    DIR *current_dir = opendir(".");
    if (current_dir == NULL)
    {
        printf("Could not open directory\n");
        return;
    }

    struct dirent *files;
    int count = 0;
    char options[50][256] = {'\0'};
    while ((files = readdir(current_dir)) != NULL)
    {
        if (files->d_name[0] == '.')
        {
            continue;
        }

        if (strncmp(files->d_name, last_part, i) == 0)
        {
            strcpy(options[count], files->d_name);
            count++;
        }
    }

    if (count == 1)
    {
        strcpy(firstInput+ptr, options[0]);
        // while (i < strlen(options[0]))
        // {
        //     firstInput[l] = options[0][i];
        //     printf("%c", firstInput[l]);
        //     l++;
        //     i++;
        // }
    }
    else if (count > 1)
    {
        int mini = 257;

        for (int j = 0; j < count; j++)
        {
            int temp = strlen(options[j]);
            if (temp < mini)
            {
                mini = temp;
            }
            printf("%s\n", options[j]);
        }

        for (int j = i; j < mini; j++)
        {
            int flag = 0;
            for (int k = 1; k < count; k++)
            {
                if (options[k][j] != options[k - 1][j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                break;
            }
            last_part[j] = options[0][j];
        }

        strcpy(firstInput + ptr, last_part);
    }
}

int main()
{
    // Initially checking host name and system name which shall only be run once during the execution
    int total_number_of_commands = 0; // To keep track of total number of commands
    shellPID = getpid();
    // readFromFile();
    // char *historyArray[20];
    // This is to control background and foreground processes count
    // int bg_counter = 0;

    if (uname(&check) == -1)
    {
        printf("Error!!");
        exit(1);
    }
    // char *buffer = (char *)malloc(256 * sizeof(char));
    buffer = host_name();
    getcwd(cur_dir, 1000);
    strcpy(pseudo_dir, cur_dir);
    strcpy(decoy_pseudo_dir, pseudo_dir);

    strcpy(hist_file_loc, cur_dir);
    strcat(hist_file_loc, "/history.txt");

    FILE *fi_pt = fopen(hist_file_loc, "r");
    if (fi_pt == NULL)
    {
        fopen(hist_file_loc, "w");
    }
    fclose(fi_pt);

    readFromFile(hist_file_loc);

    // historyCheck();

    signal(SIGCHLD, bg_signal_handler);
    signal(SIGINT, cntrl_C_handler);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGTSTP, cntrl_Z_handler);

    while (1)
    {
        // getcwd(cur_dir, 1000);
        // // printf("Previous directory-%s Current Directory-%s\n", prevDir, cur_dir);

        // if (strcmp(cur_dir, pseudo_dir) == 0)
        // {
        //     printf("<%s@%s:~>", buffer, check.sysname);
        // }
        // else
        // {
        //     bool finish = true;
        //     for (int i = 0; i < strlen(pseudo_dir); i++)
        //     {
        //         if (cur_dir[i] != pseudo_dir[i])
        //         {
        //             finish = false;
        //             break;
        //         }
        //     }
        //     if (!finish)
        //     {
        //         printf("<%s@%s:%s>", buffer, check.sysname, cur_dir);
        //     }
        //     else
        //     {
        //         char copy[100];
        //         int u = 1;
        //         strcpy(copy, "~");
        //         for (int i = strlen(pseudo_dir); i < strlen(cur_dir); i++)
        //         {
        //             copy[u] = cur_dir[i];
        //             u++;
        //         }
        //         printf("<%s@%s:%s>", buffer, check.sysname, copy);
        //     }
        // }

        int redirection_flag = 0;

        prompt();

        // Taking in input
        // scanf(" %[^\n]s", firstInput);

        // int l = getc(stdin);

        // char *inp = fgets(firstInput, 1000, stdin);

        // TAKING IN INPUT FOR AUTOCOMPLETION
        char c;
        setbuf(stdout, NULL);
        enableRawMode();
        // printf("Prompt>");
        memset(firstInput, '\0', 100);
        int pt = 0;
        while (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (iscntrl(c))
            {
                if (c == 10)
                    break;
                else if (c == 27)
                {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2)
                    { // length of escape code
                        printf("\rarrow key: %s", buf);
                    }
                }
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        if (firstInput[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        firstInput[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                { // TAB character
                    printf("\n");
                    autocomplete();
                    pt = strlen(firstInput);
                    prompt();
                    printf("%s", firstInput);
                }
                else if (c == 4)
                {
                    fflush(stdout);
                    printf("\n");
                    printf("Control D command detected\n");
                    updateToFile(hist_file_loc);
                    exit(0);
                }
            }
            else
            {
                firstInput[pt++] = c;
                printf("%c", c);
            }
        }
        disableRawMode();
        printf("\n");
        // printf("\nInput Read: [%s]\n", firstInput);

        if (firstInput == NULL)
        {
            fflush(stdout);
            printf("\n");
            printf("Control D command detected\n");
            updateToFile(hist_file_loc);
            exit(0);
        }

        int len = strlen(firstInput);
        if (firstInput[len - 1] == '\n')
        {
            firstInput[len - 1] = '\0';
        }

        // else
        // {
        // printf("Reached here\n");
        updateHistory(firstInput, &total_number_of_commands);

        // To tokenize the input string and break it into commands
        com_count = 0;
        char temp_tok[3] = ";";
        char *temp = strtok(firstInput, temp_tok);

        while (temp != NULL)
        {
            strcpy(input[com_count], temp);
            temp = strtok(NULL, temp_tok);
            com_count++;
        }

        for (int i = 0; i < com_count; i++)
        {
            // Used to separate the semi-colon separated commands from each other and further split them up by removing spaces
            // strcpy(temp_tok, " ");
            // if (checkPipes() == -1)
            // {
            //     continue;
            // }

            // checkPipes(i);

            char temp_tok2[3] = " \t";
            temp = strtok(input[i], temp_tok2);
            comm_count = 0;

            while (temp != NULL)
            {
                strcpy(command[comm_count], temp);
                temp = strtok(NULL, temp_tok2);
                comm_count++;
            }

            // if(checkPipes() != -1)
            // {
            //     continue;
            // }

            for (int j = 0; j < comm_count; j++)
            {
                if (strcmp(command[j], ">") == 0 || strcmp(command[j], "<") == 0 || strcmp(command[j], ">>") == 0)
                {
                    // printf("Entered here\n");
                    redirection();
                    redirection_flag = 1;
                    break;
                }
            }

            if (redirection_flag != 1)
            {
                execute();
            }

            // // Checking the commands to see what the user wants to execute
            // if (strcmp(command[0], "cd") == 0)
            // {
            //     if (comm_count > 2)
            //     {
            //         printf("Too many arguments passed for cd command\n");
            //     }

            //     else if (comm_count == 1) // This means command entered was `cd` and should show user pseudo-home directory(~)
            //     {
            //         chdir(pseudo_dir);
            //         getcwd(cur_dir, 1000);
            //     }

            //     else if (strcmp(command[1], ".") == 0)
            //     {
            //         changePrevDir(prevDir); // NEED TO WRITE THIS FUNCTION
            //         pwd();
            //     }

            //     else if (strcmp(command[1], "~") == 0)
            //     {
            //         changeCurrDir(cur_dir, pseudo_dir, prevDir); // NEED TO WRITE THIS FUNCTION
            //     }

            //     else if (strcmp(command[1], "..") == 0)
            //     {
            //         getcwd(prevDir, 1000);
            //         chdir("..");
            //         getcwd(cur_dir, 1000);
            //     }

            //     else if (strcmp(command[1], "-") == 0)
            //     {
            //         // printf("Entered this function\n");
            //         updateCurrDir(cur_dir, prevDir); // NEED TO WRITE THIS FUNCTION
            //     }

            //     else
            //     {
            //         checkDir(command[1], cur_dir, prevDir);
            //     }
            //     // printf("Previous directory-%s Current Directory-%s\n", prevDir, cur_dir);
            // }

            // // pwd command
            // else if (strcmp(command[0], "pwd") == 0)
            // {
            //     pwd();
            // }

            // // echo command
            // else if (strcmp(command[0], "echo") == 0)
            // {
            //     echo(command, comm_count);
            // }

            // // history command
            // else if (strcmp(command[0], "history") == 0)
            // {
            //     if (comm_count > 1)
            //     {
            //         printf("Too many arguments for history command\n");
            //     }
            //     else
            //     {
            //         printHistory();
            //     }
            // }

            // // ls command
            // else if (strcmp(command[0], "ls") == 0)
            // {
            //     char dir_file_storer[20][1000];
            //     int a_flag = 0, l_flag = 0, x = 0;
            //     if (comm_count == 1)
            //     {
            //         plain_ls(cur_dir);
            //     }

            //     else
            //     {
            //         for (int i = 1; i < comm_count; i++)
            //         {
            //             if (command[i][0] == '-')
            //             {
            //                 if (command[i][1] == 'a')
            //                 {
            //                     a_flag = 1;
            //                 }
            //                 else if (command[i][1] == 'l')
            //                 {
            //                     l_flag = 1;
            //                 }
            //                 else
            //                 {
            //                     printf("Invalid command\n");
            //                 }
            //             }

            //             else if (strcmp(command[i], "-a") == 0)
            //             {
            //                 a_flag = 1;
            //             }

            //             else if (strcmp(command[i], "-l") == 0)
            //             {
            //                 l_flag = 1;
            //             }

            //             else if (strcmp(command[i], "-la") == 0 || strcmp(command[i], "-al") == 0)
            //             {
            //                 a_flag = 1;
            //                 l_flag = 1;
            //             }

            //             else
            //             {
            //                 strcpy(dir_file_storer[x], command[i]);
            //                 x++;
            //             }
            //         }
            //     }

            //     if (strcmp(command[1], ".") == 0 && comm_count == 2)
            //     {
            //         plain_ls(cur_dir);
            //     }

            //     else if (strcmp(command[1], "..") == 0 && comm_count == 2)
            //     {
            //         char *temp_directory = malloc(1000 * sizeof(char));
            //         chdir("..");
            //         getcwd(temp_directory, 1000);
            //         plain_ls(temp_directory);
            //         chdir(cur_dir);
            //     }

            //     else if (strcmp(command[1], "~") == 0 && comm_count == 2)
            //     {
            //         plain_ls(pseudo_dir);
            //     }

            //     else if (strcmp(command[1], "-a") == 0 && comm_count == 2)
            //     {
            //         ls_a(cur_dir);
            //     }

            //     else if ((strcmp(command[1], "-l") == 0) && comm_count == 2)
            //     {
            //         ls_l(cur_dir);
            //     }

            //     else if ((strcmp(command[1], "-al") == 0 || strcmp(command[1], "-la") == 0) && comm_count == 2)
            //     {
            //         ls_la_al(cur_dir);
            //     }

            //     else
            //     {
            //         if (a_flag == 0 && l_flag == 0)
            //         {
            //             for (int i = 0; i < x; i++)
            //             {
            //                 DIR *tempp_trav;
            //                 tempp_trav = opendir(dir_file_storer[i]);

            //                 if (tempp_trav == NULL)
            //                 {
            //                     if (errno == ENOTDIR)
            //                     {
            //                         printf("%s\n", dir_file_storer[i]);
            //                     }
            //                     else if (errno == ENOENT)
            //                     {
            //                         printf("The file or directory with the name %s does not exist\n", dir_file_storer[i]);
            //                     }
            //                     else
            //                     {
            //                         printf("Error occured in opening the directory %s\n", dir_file_storer[i]);
            //                     }
            //                 }

            //                 else
            //                 {
            //                     printf("%s:\n", dir_file_storer[i]);
            //                     plain_ls(dir_file_storer[i]);
            //                     printf("\n");
            //                 }
            //             }
            //         }

            //         else if (a_flag == 1 && l_flag == 0)
            //         {
            //             if (x == 0)
            //             {
            //                 ls_a(cur_dir);
            //             }

            //             for (int i = 0; i < x; i++)
            //             {
            //                 DIR *tempp_trav;
            //                 tempp_trav = opendir(dir_file_storer[i]);

            //                 if (tempp_trav == NULL)
            //                 {
            //                     if (errno == ENOTDIR)
            //                     {
            //                         printf("%s\n", dir_file_storer[i]);
            //                     }
            //                     else if (errno == ENOENT)
            //                     {
            //                         printf("The file or directory with the name %s does not exist\n", dir_file_storer[i]);
            //                     }
            //                     else
            //                     {
            //                         printf("Error occured in opening the directory %s\n", dir_file_storer[i]);
            //                     }
            //                 }

            //                 else
            //                 {
            //                     printf("%s:\n", dir_file_storer[i]);
            //                     ls_a(dir_file_storer[i]);
            //                     printf("\n");
            //                 }
            //             }
            //         }

            //         else if (a_flag == 0 && l_flag == 1)
            //         {
            //             if (x == 0)
            //             {
            //                 ls_l(cur_dir);
            //             }

            //             for (int i = 0; i < x; i++)
            //             {

            //                 DIR *tempp_trav;
            //                 tempp_trav = opendir(dir_file_storer[i]);

            //                 if (tempp_trav == NULL)
            //                 {
            //                     if (errno == ENOTDIR)
            //                     {
            //                         permission(dir_file_storer[i]);
            //                     }
            //                     else if (errno == ENOENT)
            //                     {
            //                         printf("The file or directory with the name %s does not exist\n", dir_file_storer[i]);
            //                     }
            //                     else
            //                     {
            //                         printf("Error occured in opening the directory %s\n", dir_file_storer[i]);
            //                     }
            //                 }

            //                 else
            //                 {
            //                     printf("%s:\n", dir_file_storer[i]);
            //                     ls_l(dir_file_storer[i]);
            //                     printf("\n");
            //                 }
            //             }
            //         }

            //         else
            //         {
            //             // printf("Reached here\n");
            //             if (x == 0)
            //             {
            //                 ls_la_al(cur_dir);
            //             }

            //             for (int i = 0; i < x; i++)
            //             {

            //                 DIR *tempp_trav;
            //                 tempp_trav = opendir(dir_file_storer[i]);

            //                 if (tempp_trav == NULL)
            //                 {
            //                     if (errno == ENOTDIR)
            //                     {
            //                         printf("%s\n", dir_file_storer[i]);
            //                     }
            //                     else if (errno == ENOENT)
            //                     {
            //                         printf("The file or directory with the name %s does not exist\n", dir_file_storer[i]);
            //                     }
            //                     else
            //                     {
            //                         printf("Error occured in opening the directory %s\n", dir_file_storer[i]);
            //                     }
            //                 }

            //                 else
            //                 {
            //                     printf("%s:\n", dir_file_storer[i]);
            //                     ls_la_al(dir_file_storer[i]);
            //                     printf("\n");
            //                 }
            //             }
            //         }
            //     }
            // }

            // else if (strcmp(command[0], "discover") == 0)
            // {
            //     if (comm_count == 1)
            //     {
            //         // printf("Check 1\n");
            //         plain_discover(cur_dir, cur_dir);
            //     }

            //     else
            //     {
            //         int d_flag = 0, f_flag = 0, dir_flag = 0, file_flag = 0;
            //         char temp_dir[1000];
            //         char temp_file[1000];
            //         bool directory_encountered = false;
            //         bool illegal_dir = false;
            //         for (int i = 1; i < comm_count; i++)
            //         {
            //             if (command[i][0] == '"')
            //             {
            //                 file_flag = 1;
            //                 directory_encountered = true;
            //                 for (int j = 1; j < strlen(command[i]) - 1; j++)
            //                 {
            //                     temp_file[j - 1] = command[i][j];
            //                 }
            //             }
            //             else if (strcmp(command[i], "-d") == 0)
            //             {
            //                 d_flag = 1;
            //                 directory_encountered = true;
            //             }
            //             else if (strcmp(command[i], "-f") == 0)
            //             {
            //                 f_flag = 1;
            //                 directory_encountered = true;
            //             }
            //             else
            //             {
            //                 if (!directory_encountered)
            //                 {
            //                     if (strcmp(command[i], "~") == 0)
            //                     {
            //                         strcpy(command[i], pseudo_dir);
            //                     }
            //                     DIR *d = opendir(command[i]);
            //                     if (d == NULL)
            //                     {
            //                         printf("The given input %s does not exist\n", command[i]);
            //                         illegal_dir = true;
            //                         break;
            //                     }
            //                     else
            //                     {
            //                         strcpy(temp_dir, command[i]);
            //                         dir_flag = 1;
            //                     }
            //                 }
            //                 else
            //                 {
            //                     file_flag = 1;
            //                     strcpy(temp_file, command[i]);
            //                 }
            //             }
            //         }
            //         // printf("%d %d %d %d\n", d_flag, f_flag, dir_flag, file_flag);
            //         if (illegal_dir)
            //         {
            //             continue;
            //         }

            //         else if (file_flag == 1)
            //         {
            //             if (f_flag != 0 || d_flag != 0)
            //             {
            //                 printf("This seems like a problematic command\n");
            //             }
            //             else
            //             {
            //                 if (dir_flag == 1)
            //                 {
            //                     printf("%s\n", temp_dir);
            //                     if (discover_file_directory_2(temp_dir, temp_dir, temp_file) == 0)
            //                     {
            //                         printf("The file does not exist.\n");
            //                     }
            //                 }
            //                 else
            //                 {
            //                     strcpy(temp_dir, cur_dir);
            //                     printf("%s\n", temp_dir);
            //                     if (discover_file_directory(temp_dir, temp_dir, temp_file) == 0)
            //                     {
            //                         printf("The file does not exist.\n");
            //                     }
            //                 }
            //             }
            //         }

            //         else if (d_flag == 1 && f_flag == 0)
            //         {
            //             if (dir_flag == 0)
            //             {
            //                 strcpy(temp_dir, cur_dir);
            //                 printf("%s\n", temp_dir);
            //                 discover_d(temp_dir, temp_dir);
            //             }
            //             else
            //             {
            //                 printf("%s\n", temp_dir);
            //                 discover_d_2(temp_dir, temp_dir);
            //             }
            //         }
            //         else if (d_flag == 0 && f_flag == 1)
            //         {
            //             // printf("Reached here\n");
            //             // if (dir_flag == 0)
            //             // {
            //             //     strcpy(temp_dir, cur_dir);
            //             // }
            //             // discover_f(temp_dir, temp_dir);
            //             if (dir_flag == 0)
            //             {
            //                 strcpy(temp_dir, cur_dir);
            //                 printf("%s\n", temp_dir);
            //                 discover_f(temp_dir, temp_dir);
            //             }
            //             else
            //             {
            //                 printf("%s\n", temp_dir);
            //                 discover_f_2(temp_dir, temp_dir);
            //             }
            //         }
            //         else
            //         {
            //             // if (dir_flag == 0)
            //             // {
            //             //     strcpy(temp_dir, cur_dir);
            //             // }
            //             // plain_discover(temp_dir, temp_dir);
            //             if (dir_flag == 0)
            //             {
            //                 strcpy(temp_dir, cur_dir);
            //                 printf("%s\n", temp_dir);
            //                 plain_discover(temp_dir, temp_dir);
            //             }
            //             else
            //             {
            //                 printf("%s\n", temp_dir);
            //                 plain_discover_2(temp_dir, temp_dir);
            //             }
            //         }
            //     }
            // }

            // // pinfo command
            // else if (strcmp(command[0], "pinfo") == 0)
            // {
            //     if (comm_count == 1)
            //     {
            //         pinfo_blank();
            //     }
            //     else
            //     {
            //         int x = atoi(command[1]);
            //         pinfo_pid(x);
            //     }
            // }

            // else if (strcmp(command[0], "exit") == 0)
            // {
            //     updateToFile(hist_file_loc);
            //     exit(0);
            // }

            // // foreground/background process
            // else
            // {
            //     // printf("This is a fore/back process\n");
            //     char bgProcess[100][1000];
            //     int e = 0;
            //     for (int i = 0; i < comm_count; i++)
            //     {
            //         if (strcmp(command[i], "&") == 0)
            //         {
            //             bg(bgProcess, e);
            //             e = 0;
            //         }
            //         else
            //         {
            //             strcpy(bgProcess[e], command[i]);
            //             e++;
            //             // printf("%s\n", bgProcess[i]);
            //         }
            //         // printf("Finished iteration %d\n", i+1);
            //     }
            //     if (strcmp(command[comm_count - 1], "&") == 0)
            //     {
            //         break;
            //     }
            //     f2(bgProcess, e);
            // }
            fflush(stdout);
        }
        // }
        // fflush(stdin);
    }
}
