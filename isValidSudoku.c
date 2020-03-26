

bool isValidSudoku(char** board, int boardSize, int* boardColSize){

    int i,j,k,l;
    
    int number;
    
    int hash_table[10] = {0};
    int h_i;
    
    for(i=0; i<boardSize; i++)
    {
        for(j=0; j<boardSize; j++)
        {
            if(board[i][j] != '.'){
                number = board[i][j] - '0';
                hash_table[number]++;
                
                if(hash_table[number] > 1)
                    return false;
            
                
             }
        }
        
        for(h_i=0; h_i<=boardSize; h_i++)
            hash_table[h_i] = 0;
    
    }

    
    for(i=0; i<boardSize; i++)
    {
        for(j=0; j<boardSize; j++)
        {
            if(board[j][i] != '.')
            {
                number = board[j][i] - '0';
                hash_table[number]++;
                
                if(hash_table[number] > 1)
                    return false;
            }
        }
    
        for(h_i=0; h_i<=boardSize; h_i++)
            hash_table[h_i] = 0;
    }

    
    for(l=0; l<boardSize; l+=3)
        for(k=0; k<boardSize; k += 3)
        {
            for(i=l; i<l+3; i++){

                for(j=k; j<k+3; j++)
                {
                    if(board[i][j] != '.')
                    {
                    number = board[i][j] - '0';
                    hash_table[number]++;

                    if(hash_table[number] > 1)
                        return false;
                    }
                }

            }

            for(h_i=0; h_i<=boardSize; h_i++)
                hash_table[h_i] = 0;
        }
    
    return true;
    
}

