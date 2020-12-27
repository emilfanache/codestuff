/*
 * ShmReadWrite.c
 *
 *  Created on: Dec. 7, 2020
 *      Author: Emil Fanache
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define PROJ_ID                     33
#define DEFAULT_KEY                 0xDEFA
#define FTOK_FILE                   "./s_mem"
#define MAX_BUF_SIZE                1024
#define WRITE_BUF_SIZE              512
#define ASCII_PRINTABLE_START       32
#define ASCII_PRINTABLE_STOP        126


#define STATUS_ERR        0
#define STATUS_OK         1


typedef struct shmdata_t
{
    unsigned actual_size;
    char buffer[MAX_BUF_SIZE];
} shmdata;

typedef enum
{
  ACT_SHM_R = 0,
  ACT_SHM_W
} shmaction;

/*******************************************************************
* NAME :        shm_generate_key
*
* DESCRIPTION : Generates a unique key id to associate to the shared
*               memory based on a file. If the file is not found
*               then the default key id (0xDEFA) will be used.
*
* INPUT:        fname - file name used by ftok to generate a uniqe key id
*
* RETURNS :     unique key id if s_mem exists, 0xDEFA otherwise
*******************************************************************/
key_t shm_generate_key(char *fname)
{
    key_t key;

    if (fname && fname[0] != '\0' && fname[0] != '?')
    {
        key = ftok(fname, PROJ_ID);
    }
    else
    {
        printf("Using default filename to generate unique key id: %s\n", FTOK_FILE);
        key = ftok(FTOK_FILE, PROJ_ID);
    }

    if (key < 0)
    {
        perror("Unable to generate key. Using default. Err: ");
        return DEFAULT_KEY;
    }

    return key;
}


/*******************************************************************
* NAME :        shm_build_data
*
* DESCRIPTION : Fills the buffer that is to be written in the shared
*               memory with common ASCII characters (range 32-126)
*
* INPUT:        data - pointer to the data struct that is to be filled
*               size - the buffer size that will be used as a counter
*                      for the number of ascii characters to write
*
*******************************************************************/
void shm_build_data(shmdata *data, unsigned int size)
{
    unsigned int ascii_idx;
    unsigned int i;

    if (!data)
        return;

    if (size > MAX_BUF_SIZE)
        size = MAX_BUF_SIZE;

    data->actual_size = size;
    memset(data->buffer, 0, MAX_BUF_SIZE * sizeof(char));

    ascii_idx = ASCII_PRINTABLE_START;
    for (i = 0; i < size - 1; i++)
    {
        data->buffer[i] = (char) ascii_idx;
        ascii_idx++;
        if (ascii_idx > ASCII_PRINTABLE_STOP)
            ascii_idx = ASCII_PRINTABLE_START;
    }

    data->buffer[size - 1] = '\0';
    return;
}

/*******************************************************************
* NAME :        shm_dump_data
*
* DESCRIPTION : Displays the buffer data that was written in the shared
*               memory.
*
* INPUT:        data - pointer to the data struct that is to be displayed
*******************************************************************/
void shm_dump_data(shmdata *data)
{
    unsigned int i;

    if (!data)
        return;

    if (data->actual_size == 0)
       return;

    printf("== == SHM == ==\n");
    printf("Buffer Size: %d\n", data->actual_size);
    printf("Buffer Content:\n");
    for (i = 0; i < data->actual_size; i++)\
    {
        printf("%c%s", data->buffer[i], ((i + 1) % 64 == 0) ? "\n" : "");
    }
    return;
}

/*******************************************************************
* NAME :        shm_print_usage
*
* DESCRIPTION : This serves as a help menu displayed when using a
*               wrong argument or the explicit -h option
*******************************************************************/
void shm_print_usage()
{
    printf("Usage:  SharedMemory -r - to read the shared memory struct\n");
    printf("                     -w - to write a struct to the shared memory\n");
    printf("                     -f - file name used to generate a key id (optional)\n");
    printf("                     -h - displays this help menu \n");
}

int main(int argc, char *argv[])
{
    char ftok_file[255];
    shmaction action;
    shmdata *pdata;
    key_t key_id;
    int option;
    int status;
    int shmid;
    int err;

    ftok_file[0] = '\0';
    status = STATUS_OK;
    option = 0;

    while((option = getopt(argc, argv, "hrwf:")) != -1)
    {
        switch(option)
        {
            case 'r':
                action = ACT_SHM_R;
                break;

            case 'w':
                action = ACT_SHM_W;
                break;

            case 'f':
                printf("Using filename to generate unique key id: %s\n", optarg);
                strncpy(ftok_file, optarg, sizeof(ftok_file));
                break;

            case 'h':
            default:
                shm_print_usage();
                return STATUS_OK;
        }
    }

    key_id = shm_generate_key(ftok_file);
    printf("Using key id: 0x%x (%d) \n", key_id, key_id);
    shmid = shmget(key_id, sizeof(shmdata), 0644|IPC_CREAT);
    if (shmid < 0)
    {
         perror("shmget err: ");
         status = STATUS_ERR;
         goto done;
    }

    pdata = shmat(shmid, NULL, 0);
    if (pdata == (void *) -1)
    {
       perror("shmat err: ");
       status = STATUS_ERR;
       goto done;
    }

    if (action == ACT_SHM_W)
    {
        shm_build_data(pdata, WRITE_BUF_SIZE);
        printf("Done writing data to memory!\n");
    }
    else
    {
        shm_dump_data(pdata);
    }

    err = shmdt(pdata);
    if (err < 0)
    {
       perror("shmdt error: ");
       status = STATUS_ERR;
       goto done;
    }

    if (action == ACT_SHM_R)
    {
        err = shmctl(shmid, IPC_RMID, 0);
        if (err < 0)
        {
           perror("shmctl: ");
           status = STATUS_ERR;
        }
    }

done:
    if (status == STATUS_ERR)
        printf("The execution encountered an error!\n");
    else
        printf("\nDone! All good!\n");

    return status;
}




