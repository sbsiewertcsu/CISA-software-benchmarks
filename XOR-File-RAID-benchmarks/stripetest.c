#include <stdio.h>
#include <stdlib.h>

#include "raidlib.h"

int main(int argc, char *argv[])
{
    int bytesWritten, bytesRestored;
    char rc;
    int chunkToRebuild=0;

    if(argc < 3)
    {
        printf("useage: stripetest inputfile outputfile <sector to restore>\n");
        exit(-1);
    }
    
    if(argc >= 4)
    {
	sscanf(argv[3], "%d", &chunkToRebuild);
        printf("chunk to restore = %d\n", chunkToRebuild);
    }
   
    bytesWritten=stripeFile(argv[1], 0); 

    printf("input file was written as 4 data chunks + 1 XOR parity - could have been on 5 devices\n");
    printf("Remove chunk %d and enter g for go - could have been on 5 devices\n", chunkToRebuild);
    printf("Hit return to start rebuild:");

    rc=getchar();

    printf("working on restoring file ...\n");

    bytesRestored=restoreFile(argv[2], 0, bytesWritten, chunkToRebuild); 

    printf("FINISHED\n");
        
}
