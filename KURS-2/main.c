#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#define SIGNATURE_LENGTH 8

typedef struct checking_file
{
    FILE *file;
    char path[MAX_PATH];
    bool infected;
}checking_file;

typedef struct signatures_database
{
    FILE *file;
    char path[MAX_PATH];
}signatures_database;

typedef struct signature
{
    size_t offset;
    uint8_t signature[SIGNATURE_LENGTH];
}signature;

int get_file_size(FILE*, size_t*);
int is_file_executable(FILE*, bool*);
int input_path(char*);
int command_handler(char, checking_file*, signatures_database*);
int check_file(checking_file*, signatures_database*);
int find_signature(checking_file*, signatures_database*);
int hint();

int main()
{
    int result;
    char command;
    checking_file *checking_file;
    signatures_database *signatures;
    do
    {
        result = hint();
        if (result != 0)
            return 1;
        result = printf("Enter command: ");
        if (result < 0)
            return 2;
        result = fflush(stdin);
        if (result != 0)
            return 3;
        result = scanf("%c", &command);
        if (result != 1)
            return 4;
        result = command_handler(command, checking_file, signatures);
        if (result != 0)
        {
            printf("An error occurred, error code: %d", result);
            return 5;
        }
    }
    while (command != 'e');
    return 0;
}

int command_handler(char command, checking_file *file_for_check, signatures_database *signatures)
{
    if (command != 'e' && command != 's')
        return 1;
    int result;
    switch (command)
    {
        case 'e':
        {
            /* С этой хуйней надо что-то придумать, а то залупа получается какая-то */
            return 0;
        }
        case 's':
        {
            file_for_check = (checking_file*)malloc(sizeof(checking_file));
            if (file_for_check == NULL)
                return 2;
            signatures = (signatures_database*)malloc(sizeof(signatures_database));
            if (signatures == NULL)
                return 3;
            result = printf("Enter path to signatures database: ");
            if (result < 0)
                return 2;
            result = input_path(signatures->path);
            switch (result)
            {
                case 1:
                    return 3;
                case 2:
                    return 4;
                case 3:
                    return 5;
                case 4:
                    return 6;
                case 5:
                    return 7;
                case 6:
                    return 8;
                default:
                {
                    signatures->file = fopen(signatures->path, "r");
                    if (signatures->file == NULL)
                        return 9;
                    break;
                }
            }
            result = printf("Enter path to checking file: ");
            if (result < 0)
                return 10;
            result = input_path(file_for_check->path);
            switch (result)
            {
                case 1:
                    return 11;
                case 2:
                    return 12;
                case 3:
                    return 13;
                case 4:
                    return 14;
                case 5:
                    return 15;
                case 6:
                    return 16;
                default:
                {
                    file_for_check->file = fopen(file_for_check->path, "rb");
                    if (file_for_check->file == NULL)
                    {
                        fclose(signatures->file);
                        return 17;
                    }
                    result = check_file(file_for_check, signatures);
                    switch (result)
                    {
                        case 1:
                            return 18;
                        case 2:
                            return 19;
                        case 3:
                            return 20;
                        case 4:
                            return 21;
                        case 5:
                            return 22;
                        case 6:
                            return 23;
                        case 7:
                            return 24;
                        case 8:
                            return 25;
                        case 9:
                            return 26;
                        case 10:
                            return 27;
                        default:
                        {
                            if (file_for_check->infected)
                            {
                                result = printf("Attention! File is infected!\n");
                                if (result < 0)
                                    return 28;
                            }
                            else
                            {
                                result = printf("File is clean!\n");
                                if (result < 0)
                                    return 29;
                            }
                            result = fclose(signatures->file);
                            if (result != 0)
                            {
                                fclose(file_for_check->file);
                                return 30;
                            }
                            result = fclose(file_for_check->file);
                            if (result != 0)
                                return 31;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        default:
            ;
    }
    return 0;
}

int check_file(checking_file *checking_file, signatures_database *signatures)
{
    if (checking_file == NULL)
        return 1;
    if (signatures == NULL)
        return 2;
    if (checking_file->file == NULL)
        return 3;
    if (signatures->file == NULL)
        return 4;
    if (strlen(checking_file->path) == 0)
        return 5;
    if (strlen(signatures->path) == 0)
        return 6;
    int result;
    bool executable = false;
    size_t sig_size = 0;
    result = is_file_executable(checking_file->file, &executable);
    switch (result)
    {
        case 1:
            return 4;
        case 2:
            return 5;
        case 3:
            return 6;
        case 4:
            return 7;
        case 5:
            return 8;
        case 6:
            return 9;
        case 7:
            return 10;
        case 8:
            return 11;
        case 9:
            return 12;
        case 10:
            return 13;
        case 11:
            return 14;
        default:
            break;
    }
    result = get_file_size(signatures->file, &sig_size);
    switch (result)
    {
        case 1:
            return 9;
        case 2:
            return 10;
        case 3:
            return 11;
        case 4:
            return 12;
        case 5:
            return 13;
        case 6:
            return 14;
        default:
            break;
    }
    if (sig_size == 0)
        return 15;
    if (executable)
    {
        result = find_signature(checking_file, signatures);
        if (result != 0)
            return 16;
    }
    return 0;
}

int find_signature(checking_file *checking_file, signatures_database *signatures)
{
    if (checking_file == NULL)
        return 1;
    if (signatures == NULL)
        return 2;
    if (checking_file->file == NULL)
        return 3;
    if (signatures->file == NULL)
        return 4;
    if (strlen(checking_file->path) == 0)
        return 5;
    if (strlen(signatures->path) == 0)
        return 6;
    int result;
    size_t file_size = 0;
    signature buffer, temp_signature;
    result = get_file_size(checking_file->file, &file_size);
    switch (result)
    {
        case 1:
            return 7;
        case 2:
            return 8;
        case 3:
            return 9;
        case 4:
            return 10;
        case 5:
            return 11;
        case 6:
            return 12;
        default:
            break;
    }
    while (feof(signatures->file) == 0)
    {
        result = fscanf(signatures->file, "%zu%"SCNu8"%"SCNu8"%"SCNu8"%"SCNu8"%"SCNu8"%"SCNu8"%"SCNu8"%"SCNu8"",
                        &temp_signature.offset,&temp_signature.signature[0], &temp_signature.signature[1],
                        &temp_signature.signature[2], &temp_signature.signature[3], &temp_signature.signature[4],
                        &temp_signature.signature[5], &temp_signature.signature[6], &temp_signature.signature[7]);
        if (result != 9)
            return 13;
        if (file_size <= temp_signature.offset)
            continue;
        result = fseek(checking_file->file, temp_signature.offset, SEEK_SET);
        if (result != 0)
            return 14;
        result = fread(buffer.signature, sizeof(unsigned char), 8, checking_file->file);
        if (result != 8)
            return 15;
        if (memcmp(buffer.signature, temp_signature.signature, 8) == 0)
        {
            checking_file->infected = true;
            return 0;
        }
        else
            checking_file->infected = false;
    }
    return 0;
}

int get_file_size(FILE *file, size_t *size)
{
    if (file == NULL)
        return 1;
    if (size == NULL)
        return 2;
    size_t current_offset;
    int result;
    current_offset = ftell(file);
    if (current_offset == -1)
        return 3;
    result = fseek(file, 0, SEEK_END);
    if (result != 0)
        return 4;
    *size = ftell(file);
    if (*size == -1)
        return 5;
    result = fseek(file, current_offset, SEEK_SET);
    if (result != 0)
        return 6;
    return 0;
}

int is_file_executable(FILE *file, bool *status)
{
    if (file == NULL)
        return 1;
    if (status == NULL)
        return 2;
    size_t current_offset, size = 0;
    int result;
    uint8_t buffer[2];
    *status = false;
    result = get_file_size(file, &size);
    switch (result)
    {
        case 1:
            return 3;
        case 2:
            return 4;
        case 3:
            return 5;
        case 4:
            return 6;
        case 5:
            return 7;
        case 6:
            return 8;
        default:
            break;
    }
    if (size == 0)
    {
        *status = false;
        return 0;
    }
    current_offset = ftell(file);
    if (current_offset == -1)
        return 9;
    rewind(file);
    result = fread(buffer, sizeof(uint8_t), 2, file);
    if (result != 2)
        return 10;
    if (buffer[0] != 'M' || buffer[1] != 'Z')
        *status = false;
    else
        *status = true;
    result = fseek(file, current_offset, SEEK_SET);
    if (result != 0)
        return 11;
    return 0;
}

int input_path(char *path)
{
    if (path == NULL)
        return 1;
    int result;
    result = fflush(stdin);
    if (result != 0)
        return 2;
    result = scanf("%[^\n]s", path);
    if (result != 1)
        return 3;
    while (strlen(path) == 0)
    {
        result = printf("Path can't be zero-length! Try one more time: ");
        if (result < 0)
            return 4;
        result = fflush(stdin);
        if (result != 0)
            return 5;
        result = scanf("%[^\n]s", path);
        if (result != 1)
            return 6;
    }
    return 0;
}

int hint()
{
    int result;
    result = printf("Exit: e\nScan new file: s\n");
    if (result < 0)
        return 1;
    return 0;
}