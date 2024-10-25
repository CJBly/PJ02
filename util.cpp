#include <stdio.h>
#include <string.h>
#include "util.h"

int nextInstruction(char *Word, int *Index, double *Key)
{
    int  returnV;

    fscanf(stdin, "%s", Word);

    if (strcmp(Word, "Stop")==0)     return 1;
    if (strcmp(Word, "PrintArray")==0)    return 1;
    if (strcmp(Word, "PrintHeap")==0)      return 1;
    if (strcmp(Word, "BuildHeap")==0)      return 1;

    if (strcmp(Word, "Insert")==0){
        returnV = fscanf(stdin, "%d", Index);
        if (returnV == 1){
            return 1;
        }else{
            return 0;
        }
    }
    if(strcmp(Word, "ExtractMin")==0){
	    return 1;
    }
    if(strcmp(Word, "DecreaseKey")==0){
	    returnV = fscanf(stdin, "%d %lf", Index, Key);
	    if(returnV == 2){
		    return 1;
	    }
	    else{
		    return 0;
	    }
    }



    return 0;
}
