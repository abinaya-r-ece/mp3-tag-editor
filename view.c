#include <stdio.h>
#include "view.h"
#include<string.h>
#include "types.h"
#include <stdlib.h>

/* Function Definitions */
Status viewing_tag(ViewtagInfo *viewInfo) //Do Encoding
{
    if(open_files(viewInfo)==e_failure) //If opening all files failed return e_failure
    {
        printf("Error:While opening files\n");
        return e_failure;
    }
    if(viewtags_audio(viewInfo)==e_failure)
    {
        printf("Error:While viewing tags\n");
        return e_failure;
    }                                       
    return e_success;

}
            /*READ AND VALID ENCODE ARGUMENTS*/

Status read_and_validate_view_args(char *argv[], ViewtagInfo *viewInfo)
{
    int length=strlen(argv[2]); //Finding the length of argv[2]
    int dotcount=0;
    for(int i=0;argv[2][i]!='\0';i++) //Count the dot presence in argv[2]
    {
        if(argv[2][i]=='.')
        {
            dotcount++;
        }
    }
    if(dotcount!=1) //If dot count is not equal to one return e_failure
    {
        printf("Invalid source file name dot must present one time only\n");
        return e_failure;;
    }
    if (length < 5) //If length is less than five return e_failure
    {
        printf("Invalid source file name length must be five\n");
        return e_failure;
    }
    if((argv[2][length-1]=='3')&&
    (argv[2][length-2]=='p')&&
    (argv[2][length-3]=='m')&&
    (argv[2][length-4]=='.'))
    {
        strcpy(viewInfo->audio_extension,argv[2]); //If argv[2] is valid store it into src_image_fname
    }
    else
    {
        return e_failure;
    }
    return e_success;
}
            /*Opening files*/
Status open_files(ViewtagInfo *viewInfo) //Opening all files for encoding
{

    viewInfo->fptr_src_audio = fopen(viewInfo->audio_extension, "rb"); //Open  Source Image file
    if ( viewInfo->fptr_src_audio == NULL)                                // Do Error handling
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", viewInfo->audio_extension);

        return e_failure;
    }
    return e_success;                       // No failure return e_success
}

Status viewtags_audio(ViewtagInfo *viewInfo)
{                                                                            
    char tagbuffer[5]; //Declare one character buffer to store the secret data
    unsigned char sizebuffer[4];
    unsigned int size;
    fseek(viewInfo->fptr_src_audio,10,SEEK_SET);  //Declare one buffer to store the data from source image
    for(int i=0;i<6;i++)
    {
        if(fread(tagbuffer,sizeof(char),4,viewInfo->fptr_src_audio)!=4)
        break;   //Read data from secret file and store it in buffer
        tagbuffer[4]='\0';                                                        //Read data from image and store it in image buffer
        if(fread(sizebuffer,sizeof(char),4,viewInfo->fptr_src_audio)!=4)
        break;
        size = (((unsigned int)sizebuffer[0] << 24)) |
         (((unsigned int)sizebuffer[1] << 16)  ) |
         (((unsigned int)sizebuffer[2] << 8)  ) |
         (((unsigned int)sizebuffer[3] ) );
        //printf("%s",tagbuffer);
        //printf("Size:%d\n",size);
        fseek(viewInfo->fptr_src_audio,2,SEEK_CUR);
        if(size <=0)
            break;
        char *databuffer = malloc(size+1);
        fread(databuffer,sizeof(char),size,viewInfo->fptr_src_audio);
        databuffer[size]='\0';
        char *text=databuffer+1;
        int size1=size-1;
        char *result = malloc(size1 + 1);
        for(int i=0; i<size1; i++)
        {
            if(text[i] == '\0')
                result[i] = '.';
            else
                result[i] = text[i];
        }
        result[size1] = '\0';
        if(strcmp(tagbuffer, "TIT2") == 0)                  //compare the tag with TIT2
            printf("TITLE       | %s\n",text);       //print title

        else if(strcmp(tagbuffer, "TPE1") == 0)             //compare the tag with TPE1
            printf("ARTIST      | %s\n",text);       //print artist

        else if(strcmp(tagbuffer, "TALB") == 0)             //compare the tag with TALB
            printf("ALBUM       | %s\n",text);       //print album

        else if(strcmp(tagbuffer, "TYER") == 0)             //compare the tag with TYER
            printf("YEAR        | %s\n",text);       //print year

        else if(strcmp(tagbuffer, "TCON") == 0)             //compare the tag with TCON
            printf("CONTENT     | %s\n",text);       //print content

        else if(strcmp(tagbuffer, "COMM") == 0)             //compare the tag with COMM
            printf("COMMENT     | %s\n",text);       //print comment
        free(databuffer);
        free(result);
    }
    return e_success;
}