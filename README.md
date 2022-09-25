# README
## Assignment 2
## Anish Mathur (2020102044)

### Introduction ###
This is a rudimentary version of a shell, coded in C. It contains the following functionalities:</br>

> HOW TO RUN SHELL: </br>
>1. In terminal enter command ```make``` followed by ```./a.out```</br>
>2. To exit from the shell enter ```exit``` command. </br>

<b>Note to reader:</b> The shell contains 2 folders <b>test</b> and <b>test1</b> which were folders I made for the purpose of testing out my shell.

1. <b>cd command:</b> </br>
The cd command is used to change the directory we are in. In this shell, apart from the basic functionality where one enters the directory along with the command the following flags have been implemented:-

    ```cd .``` changes the previous directory to the current directory while staying in the current directory.

    ```cd ..``` will move the user up one directory. For example if the user is in ```/home/anish/Desktop/OSN/Assignment2``` he will then be going to ```/home/anish/Desktop/OSN```.

    ```cd -```  will send the user to the previous directory.

    ```cd ~``` sends the user to the home directory. In our shell it shall be our "pseudo-home", which is the current directory from which our shell is being run.

>Related files: ```cd.c``` ```cd.h```

2. <b>echo command:</b> </br>
The echo command is used to print out whatever is entered after it, with a single space. In this shell, the echo command accounts for <b>spaces</b> and <b>tabs</b>.
>Related files: ```echo.c``` ```echo.h```

3. <b>pwd command:</b> </br>
The pwd command simply prints out the current directory the shell is in.
>Related files: ```pwd.c``` ```pwd.h```

4. <b>ls command:</b> </br>
The ls command is used to print directories and computer files in a system. In this shell, one can provide the names of directories or files in the directory the user is in currently. The command outputs the names of directories in blue, files in white and executables in green. </br>

    The command also accounts for the following flags: </br>
    ```-l``` This command is used to display the permissions, last time modified, owner ID etc and much more for each file/directory in the current directory. The shell can also handle a flag like ```-lllll```.</br>

    ```-a``` This command is used to display all the hidden files present in the current directory. The shell can also handle a flag like ```-aaaa```. </br>

    The command line arguments can contain filenames, directory names and flags in any order.
>Related files: ```ls.c``` ```ls.h```

5. <b>System commands (foreground and background):</b></br
All commands other than those implemented in the shell can be run using the <i><b>execvp</b></i> command. Background processes have been differentiated using the <b>&</b> token, and each background process generates a unique process ID (pid), which upon completion returns an update if the process exited normally or abnormally.

    However,for a process ```sleep 5 &``` after printing ```Process sleep with pid xyz exited normally/abnormally``` the shell moves to the next line where it awaits the next command to be executed by the shell.

    The shell also prints out the time taken by a foreground process (if > 1s) <b>in a new line</b> after every foreground process.

>Related files: ```foreground.c foreground.h background.c signalHandler.h signalHandler.c```

6. <b>Pinfo command:</b></br>
The pinfo command is used to print information about the any process which is <b>currently</b> being executed/run in the system. It works in 2 ways: </br>
        
    1)```pinfo``` which returns 4 updates about the shell PID: </br>
        
        1. PID : Printing the PID of the shell.
        2. Process Status : Can be {R / R+ / S /S+ / Z} where the +  
        represents a process running in the foreground. R stands for 
        running, S for Sleeping and Z for Zombie process.
        3. Memory : The memory taken by the process in # NEED TO ADD
        4. Executable path : The path of the executable file of a process or command.

    2)```pinfo PID``` which returns the afore mentioned information for the argument PID (for a particular process).
>Related files: ```pinfo.c pinfo.h```

7. <b>Discover command:</b></br>
The discover command prints the files and directories in a given hierarchy. While ls only prints files and directories in a the current directory, discover shall print all subsequent files and directories from the current directory. It takes in the following (optional) arguments as input: </br>
    
    1. <b>Target directory</b>: This tells the shell which directory to enter and search for files (if filename given). Else it assumes it to be the current directory the shell is in.

    2. <b>Flags</b>: The function takes in 2 flags, <b>-d</b>, which prints all the directories in the subsequent hierarchy and <b>-f</b> which prints all the files in the subsequent hierarchy.

    3. <b>File name</b>: The function takes the file name at the end. If target directory is not specified it prints the path from the current directory (assuming file exists) or prints the path from the given directory. Else it returns an error statement informing the file could not be found. The file name must only be given in ```" "```.
>Related files: ```discover.c discover.h```

8. <b>History command:</b></br>
The history command is used to print the previous 10 instructions entered by the user (legal or illegal). It also compares the previous instruction entered and if found to be the same does not update history.

    When the ```exit``` command is entered, it updates the previous 20 commands to a file, which is read once every time the shell is run. <b>Exiting the shell in any other way shall not lead to updation of the file.</b>
>Related files: ```history.c history.h history.txt```

## <u>CODE FLOW:</u>
In ```shell.c``` the system name, user name etc. are initialised and show in a prompt. Then we tokenize the string using the ```strtok``` function and next with ```" " and tabs``` so as to break down every command into code words which are then iterated through to understand which command is to be executed.

Once the command is identified, flags and other arguments are stored and then finally operated on.

## <u>Assumptions:</u>
1. Each command is at max 1000 characters long.
2. The time taken for a foreground process, if more than 1 second, is shown in the next line.
3. The ```history.txt``` file is only updated when the ```exit``` command is used.
4. The discover command will show the absolute path when ~ is given as the directory.
5. The discover command does not show hidden files.  
