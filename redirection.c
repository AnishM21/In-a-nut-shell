#include "redirection.h"

#include "execute.h"

extern char command[100][1000];
extern int comm_count;

char input_file[256], output_file[256], append_file[256];

extern char temp_command[50][100];
extern int temp_com_count;

void redirection() {
    int inpr_flag = 0, inpr_ind = 0, outr_flag = 0, outr_ind = 0, app_flag = 0, app_ind = 0, in_fd = 0, out_fd = 0, app_fd = 0, in_fd_original, out_fd_original, app_fd_original;
    int redir_err = 0;
    for (int i = 0; i < comm_count; i++) {
        if (strcmp(command[i], "<") == 0) {
            inpr_flag = 1;
            inpr_ind = i;
            strcpy(input_file, command[i + 1]);
        } else if (strcmp(command[i], ">") == 0) {
            outr_flag = 1;
            outr_ind = i;
            strcpy(output_file, command[i + 1]);
        } else if (strcmp(command[i], ">>") == 0) {
            app_flag = 1;
            app_ind = i;
            strcpy(append_file, command[i + 1]);
        } else {
            continue;
        }
    }
    if (inpr_flag == 1) {
        in_fd_original = dup(0);
        in_fd = open(input_file, O_RDONLY);
        if (in_fd == -1) {
            redir_err = 1;
            printf("Error inputting the file\n");
        } else {
            dup2(in_fd, 0);
        }
    }
    if (outr_flag == 1) {
        out_fd_original = dup(1);
        out_fd = open(output_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            redir_err = 1;
            printf("Error outputting the file\n");
        } else {
            dup2(out_fd, 1);
        }
    }
    if (app_flag == 1) {
        app_fd_original = dup(1);
        app_fd = open(append_file, O_RDWR | O_CREAT | O_APPEND, 0644);
        if (app_fd == -1) {
            redir_err = 1;
            printf("Error appending the file\n");
        } else {
            dup2(app_fd, 1);
        }
    }

    if (redir_err != 1) {
        // printf("About to enter execute from redirection\n");
        execute();
    }

    if (inpr_flag == 1) {
        dup2(in_fd_original, 0);
        close(in_fd);
        close(in_fd_original);
    }
    if (outr_flag == 1) {
        dup2(out_fd_original, 1);
        close(out_fd);
        close(out_fd_original);
    }
    if (app_flag == 1) {
        dup2(app_fd_original, 1);
        close(app_fd);
        close(app_fd_original);
    }
}

void redirection_piping()
{
    int inpr_flag = 0, inpr_ind = 0, outr_flag = 0, outr_ind = 0, app_flag = 0, app_ind = 0, in_fd = 0, out_fd = 0, app_fd = 0, in_fd_original, out_fd_original, app_fd_original;
    int redir_err = 0;
    for (int i = 0; i < temp_com_count; i++) {
        if (strcmp(temp_command[i], "<") == 0) {
            inpr_flag = 1;
            inpr_ind = i;
            strcpy(input_file, temp_command[i + 1]);
        } else if (strcmp(temp_command[i], ">") == 0) {
            outr_flag = 1;
            outr_ind = i;
            strcpy(output_file, temp_command[i + 1]);
        } else if (strcmp(temp_command[i], ">>") == 0) {
            app_flag = 1;
            app_ind = i;
            strcpy(append_file, temp_command[i + 1]);
        } else {
            continue;
        }
    }
    if (inpr_flag == 1) {
        in_fd_original = dup(0);
        in_fd = open(input_file, O_RDONLY);
        if (in_fd == -1) {
            redir_err = 1;
            printf("Error inputting the file\n");
        } else {
            dup2(in_fd, 0);
        }
    }
    if (outr_flag == 1) {
        out_fd_original = dup(1);
        out_fd = open(output_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            redir_err = 1;
            printf("Error outputting the file\n");
        } else {
            dup2(out_fd, 1);
        }
    }
    if (app_flag == 1) {
        app_fd_original = dup(1);
        app_fd = open(append_file, O_RDWR | O_CREAT | O_APPEND, 0644);
        if (app_fd == -1) {
            redir_err = 1;
            printf("Error appending the file\n");
        } else {
            dup2(app_fd, 1);
        }
    }

    if (redir_err != 1) {
        // printf("About to enter execute from redirection\n");
        execute_piping();
    }

    if (inpr_flag == 1) {
        dup2(in_fd_original, 0);
        close(in_fd);
        close(in_fd_original);
    }
    if (outr_flag == 1) {
        dup2(out_fd_original, 1);
        close(out_fd);
        close(out_fd_original);
    }
    if (app_flag == 1) {
        dup2(app_fd_original, 1);
        close(app_fd);
        close(app_fd_original);
    }
}