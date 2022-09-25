#include "ls.h"

// NEED TO CODE -lllla etc

void plain_ls(char *current_directory)
{
    struct dirent **fileArray;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    if (num_files < 0)
    {
        printf("An error occured opening the directory");
        return;
    }

    else
    {
        struct dirent *temp;
        for (int i = 0; i < num_files; i++)
        {
            temp = fileArray[i];
            struct stat file_stat;

            char temporary_path[100];
            strcpy(temporary_path, current_directory);
            strcat(temporary_path, "/");
            strcat(temporary_path, temp->d_name);

            stat(temporary_path, &file_stat);

            if (temp->d_name[0] == '.')
            {
                continue;
            }
            else if (temp->d_type == 4)
            {
                printf("\033[0;34m");
                printf("%s\n", temp->d_name);
                printf("\033[0m");
            }
            // else if (temp->d_type == 8)
            // {
            //     printf("%s\n",temp->d_name);
            // }
            else if(file_stat.st_mode & S_IXUSR)
            {
                printf("\033[0;32m");
                printf("%s\n", temp->d_name);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", temp->d_name);
            }
            
            // printf("%s\n", temp->d_name);

        }
    }
}

void ls_a(char *current_directory)
{
    struct dirent **fileArray;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    if (num_files < 0)
    {
        printf("An error occured opening the directory");
        return;
    }

    else
    {
        struct dirent *temp;
        for (int i = 0; i < num_files; i++)
        {
            temp = fileArray[i];
            // printf("%s\n", temp->d_name);
            struct stat file_stat;

            char temporary_path[100];
            strcpy(temporary_path, current_directory);
            strcat(temporary_path, "/");
            strcat(temporary_path, temp->d_name);

            stat(temporary_path, &file_stat);

            if (temp->d_type == 4)
            {
                printf("\033[0;34m");
                printf("%s\n", temp->d_name);
                printf("\033[0m");
            }
            else if(file_stat.st_mode & S_IXUSR)
            {
                printf("\033[0;32m");
                printf("%s\n", temp->d_name);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n",temp->d_name);
            }
        }
    }
}

void ls_l(char *current_directory)
{
    struct dirent **fileArray;
    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    printf("total %d\n", num_files);

    if (num_files < 0)
    {
        printf("An error occured opening the directory\n");
        return;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            // printf("Fuck you\n");
            
            struct dirent *temp;
            char temporary_path[100];
            temp = fileArray[i];
            // printf("%s",temp->d_name);
            struct stat file_stat;

            strcpy(temporary_path, current_directory);
            strcat(temporary_path, "/");
            strcat(temporary_path, temp->d_name);

            stat(temporary_path, &file_stat);

            // printf("Fuck you tonight\n");

            if (temp->d_name[0] == '.')
            {
                continue;
            }

            if (file_stat.st_mode & S_IFDIR) // Checks permissions for directory
            {
                printf("d");
            }
            else
            {
                printf("-");
            }

            if (file_stat.st_mode & S_IRUSR) // Checks permissions for user
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IWUSR)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IXUSR)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }

            if (file_stat.st_mode & S_IRGRP) // Checks permissions for group
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IWGRP)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IXGRP)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }

            if (file_stat.st_mode & S_IROTH) // Checks permissions for group
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IWOTH)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IXOTH)
            {
                printf("x ");
            }
            else
            {
                printf("- ");
            }

            printf("%ld ", file_stat.st_nlink);

            printf("%d ", file_stat.st_uid);

            printf("%d ", file_stat.st_gid);

            printf("%ld ", file_stat.st_size);

            // struct tm *time = localtime(&(file_stat.st_mtime));
            // char temporary_time[100];
            // strftime(temporary_time, 100, "%b %d %H:%M", time);
            // printf("%s ", ctime(&file_stat.st_mtime));
            // printf("%s ", temporary_time);
            // printf("%s\n", temp->d_name);
            if (temp->d_type == 4)
            {
                printf("\033[0;34m");
                printf("%s\n", temp->d_name);
                printf("\033[0m");
            }
            else if(file_stat.st_mode & S_IXUSR)
            {
                printf("\033[0;32m");
                printf("%s\n", temp->d_name);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n",temp->d_name);
            }


        }
    }
}

void ls_la_al(char *current_directory)
{
    struct dirent **fileArray;
    struct stat file_stat;

    int num_files = scandir(current_directory, &fileArray, NULL, alphasort);

    printf("total %d\n", num_files);

    if (num_files < 0)
    {
        printf("An error occured opening the directory");
        return;
    }

    else
    {
        for (int i = 0; i < num_files; i++)
        {
            struct dirent *temp;
            char temporary_path[1000];
            temp = fileArray[i];
            strcpy(temporary_path, current_directory);
            strcat(temporary_path, "/");
            strcat(temporary_path, temp->d_name);

            stat(temporary_path, &file_stat);

            // if (temp->d_name[0] == '.')
            // {
            //     continue;
            // }

            if (file_stat.st_mode & S_IFDIR) // Checks permissions for directory
            {
                printf("d");
            }
            else
            {
                printf("-");
            }

            if (file_stat.st_mode & S_IRUSR) // Checks permissions for user
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IWUSR)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IXUSR)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }

            if (file_stat.st_mode & S_IRGRP) // Checks permissions for group
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IWGRP)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IXGRP)
            {
                printf("x");
            }
            else
            {
                printf("-");
            }

            if (file_stat.st_mode & S_IROTH) // Checks permissions for group
            {
                printf("r");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IWOTH)
            {
                printf("w");
            }
            else
            {
                printf("-");
            }
            if (file_stat.st_mode & S_IXOTH)
            {
                printf("x ");
            }
            else
            {
                printf("- ");
            }

            printf("%ld ", file_stat.st_nlink);

            printf("%d ", file_stat.st_uid);

            printf("%d ", file_stat.st_gid);

            printf("%ld ", file_stat.st_size);

            struct tm *time = localtime(&(file_stat.st_mtime));
            char temporary_time[100];
            strftime(temporary_time, 100, "%b %d %H:%M", time);
            printf("%s ", temporary_time);

            // printf("%s\n", temp->d_name);

            if (temp->d_type == 4)
            {
                printf("\033[0;34m");
                printf("%s\n", temp->d_name);
                printf("\033[0m");
            }
            else if(file_stat.st_mode & S_IXUSR)
            {
                printf("\033[0;32m");
                printf("%s\n", temp->d_name);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n",temp->d_name);
            }
        }
    }
}

void permission(char *filePath)
{
    struct stat file_stat;
    stat(filePath, &file_stat);

    if (file_stat.st_mode & S_IFDIR) // Checks permissions for directory
    {
        printf("d");
    }
    else
    {
        printf("-");
    }

    if (file_stat.st_mode & S_IRUSR) // Checks permissions for user
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (file_stat.st_mode & S_IWUSR)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (file_stat.st_mode & S_IXUSR)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    if (file_stat.st_mode & S_IRGRP) // Checks permissions for group
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (file_stat.st_mode & S_IWGRP)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (file_stat.st_mode & S_IXGRP)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    if (file_stat.st_mode & S_IROTH) // Checks permissions for group
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (file_stat.st_mode & S_IWOTH)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (file_stat.st_mode & S_IXOTH)
    {
        printf("x ");
    }
    else
    {
        printf("- ");
    }

    printf("%ld ", file_stat.st_nlink);

    printf("%d ", file_stat.st_uid);

    printf("%d ", file_stat.st_gid);

    printf("%ld ", file_stat.st_size);

    struct tm *time = localtime(&(file_stat.st_mtime));
    char temporary_time[100];
    strftime(temporary_time, 100, "%b %d %H:%M", time);
    printf("%s ", temporary_time);

    printf("%s\n", filePath);
}