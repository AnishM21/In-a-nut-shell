#include "cd.h"

void changePrevDir(char* previous_directory)
{
    getcwd(previous_directory, 1000);
}

void changeCurrDir(char* current_directory, char* pseudo_home, char* previous_directory)
{
    getcwd(previous_directory, 1000);
    if(chdir(pseudo_home) != 0)
    {
        printf("Some error occured with cd ~");
    } 
    getcwd(current_directory, 1000);
}

void updateCurrDir(char* current_directory, char* previous_directory)
{
    // printf("Before cd - Previous directory-%s Current Directory-%s\n", previous_directory, current_directory);
    // printf("Previous directory-%s Current Directory-%s\n", previous_directory, current_directory); //Debugging statements
    char temp[1000];
    strcpy(temp, current_directory);
    
    // previous_directory = current_directory;
    // current_directory = temp;
    // printf("Previous directory-%s Current Directory-%s\n", previous_directory, current_directory); //Debugging statements
    
    chdir(previous_directory);
    getcwd(current_directory, 1000);
    chdir(temp);
    getcwd(previous_directory, 1000);
    
    if(chdir(current_directory) != 0)
    {
        printf("Some error occured with cd -");
    } 
    
    // printf("After cd - Previous directory-%s Current Directory-%s\n\n", previous_directory, current_directory);
    // printf("%s\n", current_directory); //Debugging statements
}

void checkDir(char* arr, char* current_directory, char* previous_directory)
{
    
    if (chdir(arr) != 0)
    {
        printf("The directory does not exist\n");
        return;
    }
    else
    {
        chdir(current_directory);
        getcwd(previous_directory, 1000);
        chdir(arr);
        getcwd(current_directory, 1000);
    }
}




