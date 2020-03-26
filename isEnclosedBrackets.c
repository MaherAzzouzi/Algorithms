bool isValid(char * s){

    char stack[100000];
    int i;
    int stack_index = 0;
    
    if(!s)
        return true;
    

    for(i=0; s[i]; i++)
    {
        if(s[i] == '(')
            stack[stack_index++] = '(';
        else if(s[i] == '[')
            stack[stack_index++] = '[';
        else if(s[i] == '{')
            stack[stack_index++] = '{';
        else if(s[i] == ')'){
                if(stack_index <= 0 || stack[--stack_index] != '(')
                    return false;
        }
        else if(s[i] == ']'){
                if(stack_index <= 0 || stack[--stack_index] != '[')
                    return false;
        }
        else if(s[i] == '}'){
                if(stack_index <= 0 || stack[--stack_index] != '{')
                    return false;
        }
    }
    

    if(stack_index == 0)
        return true;
    else
        return false;
}

