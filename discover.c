#include "discover.h"

void plain_discover(char *current_directory, char *tempp)
{
    struct dirent **fileArray;
    struct stat file_stat;

    // printf("%s\n", current_directory);
    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    // printf("total %d\n", num_files);

    if (num_files < 0)
    {
        printf("An error occured opening the directory %s\n", current_directory);
        return;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            if (temp->d_name[0] != '.')
            {
                if (strcmp(tempp, current_directory) == 0)
                {
                    strcpy(temporary_path, ".");
                }
                else
                {
                    strcpy(temporary_path, current_directory);
                }
                strcat(temporary_path, "/");
                strcat(temporary_path, temp->d_name);
                // printf("%s\n", temporary_path);

                // stat(temporary_path, &file_stat);

                // if (file_stat.st_mode & S_IFDIR) // Checks permissions for directory
                // {
                //     char temppp[1000];
                //     strcpy(temppp, current_directory);
                //     strcat(temppp, "/");
                //     strcat(temppp, temp->d_name);
                //     printf("./%s\n", temp->d_name);
                //     // printf("%s\n", temppp);
                //     // chdir(temppp);
                //     // plain_discover(temppp);
                //     // chdir(current_directory);
                // }
                // else
                // {
                //     printf("./%s\n", temp->d_name);
                // }

                if (temp->d_type == 4)
                {
                    printf("%s\n", temporary_path);
                    plain_discover(temporary_path, tempp);
                }
                else
                {
                    printf("%s\n", temporary_path);
                }
            }
        }
        return;
    }
}

void plain_discover_2(char *current_directory, char *tempp)
{
    struct dirent **fileArray;
    struct stat file_stat;

    // printf("%s\n", current_directory);
    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    // printf("total %d\n", num_files);

    if (num_files < 0)
    {
        printf("An error occured opening the directory %s\n", current_directory);
        return;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            if (temp->d_name[0] != '.')
            {
                // if (strcmp(tempp, current_directory) == 0)
                // {
                //     strcpy(temporary_path, ".");
                // }
                // else
                // {
                    strcpy(temporary_path, current_directory);
                // }
                strcat(temporary_path, "/");
                strcat(temporary_path, temp->d_name);
                // printf("%s\n", temporary_path);

                // stat(temporary_path, &file_stat);

                // if (file_stat.st_mode & S_IFDIR) // Checks permissions for directory
                // {
                //     char temppp[1000];
                //     strcpy(temppp, current_directory);
                //     strcat(temppp, "/");
                //     strcat(temppp, temp->d_name);
                //     printf("./%s\n", temp->d_name);
                //     // printf("%s\n", temppp);
                //     // chdir(temppp);
                //     // plain_discover(temppp);
                //     // chdir(current_directory);
                // }
                // else
                // {
                //     printf("./%s\n", temp->d_name);
                // }

                if (temp->d_type == 4)
                {
                    printf("%s\n", temporary_path);
                    plain_discover_2(temporary_path, tempp);
                }
                else
                {
                    printf("%s\n", temporary_path);
                }
            }
        }
        return;
    }
}

void discover_d(char *current_directory, char *tempp)
{
    struct dirent **fileArray;
    struct stat file_stat;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    if (num_files < 0)
    {
        printf("An error occured opening the directory %s\n", current_directory);
        return;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            if (temp->d_name[0] != '.')
            {
                if (strcmp(tempp, current_directory) == 0)
                {
                    strcpy(temporary_path, ".");
                }
                else
                {
                    strcpy(temporary_path, current_directory);
                }
                strcat(temporary_path, "/");
                strcat(temporary_path, temp->d_name);

                if (temp->d_type == 4)
                {
                    printf("%s\n", temporary_path);
                    discover_d(temporary_path, tempp);
                }
                else
                {
                    // printf("%s\n", temporary_path);
                    continue;
                }
            }
        }
        return;
    }
}

void discover_d_2(char *current_directory, char *tempp)
{
    struct dirent **fileArray;
    struct stat file_stat;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    if (num_files < 0)
    {
        printf("An error occured opening the directory %s\n", current_directory);
        return;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            if (temp->d_name[0] != '.')
            {
                // if (strcmp(tempp, current_directory) == 0)
                // {
                //     strcpy(temporary_path, ".");
                // }
                // else
                // {
                strcpy(temporary_path, current_directory);
                // }
                strcat(temporary_path, "/");
                strcat(temporary_path, temp->d_name);

                if (temp->d_type == 4)
                {
                    printf("%s\n", temporary_path);
                    discover_d_2(temporary_path, tempp);
                }
                else
                {
                    // printf("%s\n", temporary_path);
                    continue;
                }
            }
        }
    }
    return;
}

void discover_f(char *current_directory, char *tempp)
{
    struct dirent **fileArray;
    struct stat file_stat;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    if (num_files < 0)
    {
        printf("An error occured opening the directory %s\n", current_directory);
        return;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            if (temp->d_name[0] != '.')
            {
                if (strcmp(tempp, current_directory) == 0)
                {
                    strcpy(temporary_path, ".");
                }
                else
                {
                    strcpy(temporary_path, current_directory);
                }
                strcat(temporary_path, "/");
                strcat(temporary_path, temp->d_name);

                if (temp->d_type == 8)
                {
                    printf("%s\n", temporary_path);
                }
                else
                {
                    discover_f(temporary_path, tempp);
                    // printf("%s\n", temporary_path);
                }
            }
        }
        return;
    }
}

void discover_f_2(char *current_directory, char *tempp)
{
    struct dirent **fileArray;
    struct stat file_stat;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    if (num_files < 0)
    {
        printf("An error occured opening the directory %s\n", current_directory);
        return;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            if (temp->d_name[0] != '.')
            {
                // if (strcmp(tempp, current_directory) == 0)
                // {
                //     strcpy(temporary_path, ".");
                // }
                // else
                // {
                strcpy(temporary_path, current_directory);
                // }
                strcat(temporary_path, "/");
                strcat(temporary_path, temp->d_name);

                if (temp->d_type == 8)
                {
                    printf("%s\n", temporary_path);
                }
                else
                {
                    discover_f_2(temporary_path, tempp);
                    // printf("%s\n", temporary_path);
                }
            }
        }
        return;
    }
}

int discover_file_directory(char *current_directory, char *tempp, char *file_name)
{
    struct dirent **fileArray;
    struct stat file_stat;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    if (num_files < 0)
    {
        printf("An error occured opening the directory %s\n", current_directory);
        return 0;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            if (temp->d_name[0] != '.')
            {
                if (strcmp(tempp, current_directory) == 0)
                {
                    strcpy(temporary_path, ".");
                }
                else
                {
                    strcpy(temporary_path, current_directory);
                }
                strcat(temporary_path, "/");
                strcat(temporary_path, temp->d_name);

                if (temp->d_type == 4)
                {
                    // printf("%s\n", temporary_path);
                    discover_file_directory(temporary_path, tempp, file_name);
                }
                else if (strcmp(temp->d_name, file_name) == 0)
                {
                    printf("%s\n", temporary_path);
                    return 1;
                }
                else
                {
                    continue;
                }
            }
        }
        return 0;
    }
}

int discover_file_directory_2(char *current_directory, char *tempp, char *file_name)
{
    struct dirent **fileArray;
    struct stat file_stat;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    if (num_files < 0)
    {
        printf("An error occured opening the directory %s\n", current_directory);
        return 0;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            if (temp->d_name[0] != '.')
            {
                strcpy(temporary_path, current_directory);
                strcat(temporary_path, "/");
                strcat(temporary_path, temp->d_name);

                if (temp->d_type == 4)
                {
                    // printf("%s\n", temporary_path);
                    discover_file_directory_2(temporary_path, tempp, file_name);
                }
                else if (strcmp(temp->d_name, file_name) == 0)
                {
                    printf("%s\n", temporary_path);
                    return 1;
                }
                else
                {
                    continue;
                }
            }
        }
        return 0;
    }
}