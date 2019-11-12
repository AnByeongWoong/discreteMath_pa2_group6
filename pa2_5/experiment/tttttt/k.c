#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

#define BUFFERSIZE 1
int main(){
    FILE *instream;
    int read=0, size=0;
    char buffer[10];
    char *result;
    int buffer_size=sizeof(char)*BUFFERSIZE;
    int N=0 ,M=0;

    instream=fopen("/dev/stdin", "r");
    
    char * inputLogic = NULL;
    if( instream != NULL )
	{
		char strTemp[255];
		char *pStr;
        
        
		while( !feof( instream ) )
		{
			pStr = fgets( strTemp, sizeof(strTemp), instream );
            if(pStr == NULL){
                continue;
            }
            char *ptr = strtok(strTemp, " ");
            while(ptr != NULL){
                if(inputLogic == NULL){
                    inputLogic = (char*)malloc(sizeof(char)*strlen(ptr));
                }
                else{
                    if(ptr[0]=='('){
                        if(ptr[1]==' '){
                            inputLogic = realloc(inputLogic, sizeof(char)*2);    
                        }
                        else{
                            inputLogic = realloc(inputLogic, sizeof(char)*3);
                        }
                        
                    }
                    else{
                        inputLogic = realloc(inputLogic, sizeof(char)*(strlen(ptr)+1));
                    }
                    
                }


                if(strcmp(ptr,"(or")==0){
                    strcat(inputLogic,"(V ");
                }
                else if(strcmp(ptr,"(not")==0){
                    strcat(inputLogic,"(~ ");
                }
                else if(strcmp(ptr,"(and")==0){
                    strcat(inputLogic,"(n ");
                }
                else if(strcmp(ptr,"( ")==0){
                    strcat(inputLogic,"( ");
                }
                else{
                    
                    strcat(inputLogic,ptr);
                    strcat(inputLogic," ");
                }
                
               
                ptr = strtok(NULL, " ");
            }
           printf("%s\n",inputLogic);


            
            // char *ptr = strtok(strTemp, " ");
            // ptr = strtok(NULL, " ");
           
            }
	}
}
