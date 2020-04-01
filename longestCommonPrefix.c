char * longestCommonPrefix(char ** strs, int strsSize){

    
    int i, j;
    char element;
    char *result;
    int r_i=0;
    
    i=0;
   
    
    if(!strsSize)
        return "";    
    
    result = (char *)malloc(10000*sizeof(char));
    
    while(strs[0][i] != '\0')
    {
        element = strs[0][i];
    
        for(j=1; j<strsSize; j++)
            if(strs[j][i] != element){
                result[r_i] = '\0';
                return result;
            }

        result[r_i++] = element;
        i++;

    }   
    
    result[r_i] = '\0';
    return result;
    
}

