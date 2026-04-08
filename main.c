/*
NAME : ABINAYA R
DATE : 25-02-2026
PROJECT NAME : MP3 TAG READER & EDIT
DESCRIPTION : An MP3 Tag Reader is a program that reads metadata (ID3 tags) from MP3 files, such as title, artist, album, and year.
there is two parts edit and view part ,edit part we can edit the  tag detail according to user input ,view part we can view tag details.

SAMPLE OUTPUT : ./a.out -v sample.mp3
----------------------------------------------------------------------
                       MP3 Tag Reader
----------------------------------------------------------------------
Tag        | Field      | Data
----------------------------------------------------------------------
TIT2       | Title        | Hits Songs
TPE1       | Artist       | Yo Yo Honey Singh - [SongsPk.CC]
TALB       | Album        | Yaariyan
TYER       | Year         | 2013
TCON       | Content type | Bollywood Music - [SongsPk.CC]
COMM       | Composer     | eng
----------------------------------------------------------------------
 MP3 Tag Reader View Completed
---------------------------------------------------------------------- 

*/

#include <stdio.h>
#include <string.h>
#include "view.h"
#include "edit.h"
#include "types.h"

OperationType check_operation_type(char *);     //checking operation type whether its view tag or edit tag

int main(int argc, char *argv[])
{
    if(argc==1) // Check whether the arguments count is more than one or not
    {
        printf("More than one command line arguments are needed\n");
        return e_failure;
    }
    
    if(strcmp(argv[1],"-v")==0) //Checking whether the operation is encoding or not
    {
        if(argc!=3) //Arguments count must be 4 or 5 for encoding
        {
            printf("Minimum 3 Command line arguments are required for view tag\n");
            return e_failure;
        }
    }

    int ret=check_operation_type(argv[1]); //Checking operation type of argv[1]
    if(ret==e_view) //If the return value is e_view do viewing tag
    {
        ViewtagInfo viewInfo; //Creating varaible for structure EncodeInfo
        if(read_and_validate_view_args(argv, &viewInfo) == e_success) //Validating arguments of encoding
        {
            if(viewing_tag(&viewInfo)==e_failure)
            {
                printf("ERROR : Failed to view tags\n");
                return e_failure;
            }
        }
        else
        {
            printf("FAILED IN VALIDATING ARGUMENTS\n"); //If validating arguments failed return failure and terminate the program
            return e_failure;
        }
    }

    else if(ret == e_edit) //If the return value is e_decode go with decoding
    {
        if(argc != 5)  // Expecting 5 arguments: ./a.out -e <tag> <new_data> <file>
        {
            printf("INVALID COMMAND LINE\n");
            printf("./a.out -e <tag> <new_data> <mp3_file>\n");
            return e_failure;
        }
        EdittagInfo editInfo;
        if(read_and_validate_edit_args(argv,&editInfo)==e_success)
        {
            if(editing_tag(&editInfo)==e_failure)
            {
                printf("ERROR : Failed to edit tags\n");
                return e_failure;
            }
        }
        else
        {
            printf("FAILED IN VALIDATING ARGUMENTS\n");
            return e_failure;
        }
    }

    else if(ret == e_unsupported) 
    {
        printf("INVALID SECOND ARGUMENT\n");
        return e_failure; //If the return value is e_unsupported terminate the program
    }
}

//Checking whether the argument[1] is view tag or edit tag

OperationType check_operation_type(char *symbol) 
{
    if(strcmp(symbol,"-v")==0) 
    {
        return e_view; //If it is "-v" it will return e_view
    }
    else if(strcmp(symbol,"-e")==0) 
    {
        return e_edit; //Else if it is "-e" it will return e_edit
    }
    else 
    {
        return e_unsupported; //Else it will return e_unsupported
    }
}