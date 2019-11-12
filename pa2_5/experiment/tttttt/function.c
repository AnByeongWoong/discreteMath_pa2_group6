
int findDimension(char *b){
    int garoCount = 0;
    int countDirection=0;
    for(int k=0; k<strlen(b); k++){
        while(b[k] !=' ' ){
            if(b[k] == '('){
                garoCount++;
            }
            else if(b[k] == ')'){
                garoCount--;
            }
            if(k==strlen(b)-1){
                printf("aaaaa%d\n",garoCount);
                break;
            }
            k++;
        }
        if(garoCount==0){
            countDirection++;
        }
    }

    return countDirection;
}