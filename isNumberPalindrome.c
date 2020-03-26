

bool isPalindrome(int x){

    long long int result = 0;
    long long int a;
    int sign_flag;
    
    if(x>=0 && x <=9)
        return true;
    
    sign_flag = (x>0)?0:1;
    
    if(sign_flag)
        return false;
    else
        a = x;
    
    
    while(a != 0)
    {
        result += a % 10;
        result *= 10;
        a /= 10;
    }
    
    
    result = result/10;
    
    return (result == x)?true:false;
    
}
