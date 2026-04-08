#ifndef EDITTAG_H
#define EDITTAG_H
#include <stdio.h>
#include<string.h>

#include "types.h" // Contains user defined types

/*
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

typedef struct _EdittagInfo
{
    char src_audio_name[100];
    char temp_audio_name[100];
    FILE *fptr_src_audio;
    FILE *fptr_tmp_audio;
    char audio_extension[100];
    char frame_id[50];
    char new_data[100];

} EdittagInfo;

/* Editing function prototype */

/* Read and validate Encode args from argv */
Status read_and_validate_edit_args(char *argv[], EdittagInfo *editInfo);

/* Perform the encoding */
Status editing_tag(EdittagInfo *editInfo);

/* Get File pointers for i/p and o/p files */
Status open_files_for_editing(EdittagInfo *editInfo);

/* Encode secret file data*/
Status edit_tags_audio(EdittagInfo *editInfo);


#endif