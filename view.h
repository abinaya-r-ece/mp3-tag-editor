#ifndef VIEWTAG_H
#define VIEWTAG_H
#include <stdio.h>
#include<string.h>

#include "types.h" // Contains user defined types

/*
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

typedef struct _ViewtagInfo
{
    char src_audio_name[100];
    FILE *fptr_src_audio;
    char audio_extension[100];

} ViewtagInfo;

/* Encoding function prototype */

/* Read and validate Encode args from argv */
Status read_and_validate_view_args(char *argv[], ViewtagInfo *viewInfo);

/* Perform the encoding */
Status viewing_tag(ViewtagInfo *viewInfo);

/* Get File pointers for i/p and o/p files */
Status open_files(ViewtagInfo *viewInfo);

/* Encode secret file data*/
Status viewtags_audio(ViewtagInfo *viewInfo);


#endif