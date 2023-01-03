#include <iostream>
#include <stack>


int add(int a, char b);  // using slightly modified functions from previous homework <Basic arithmetic in C++> 
int mul(int a, char b);  // in order to use + and * operations with int and char

int main()
{
    
    int ans = 0;
    char sym;
    std::stack<char> Elements; 
    std::stack<char> Prefix;   
    std::cout<<"Enter an expression which consists of digits, < + > and < * > operators \n";
    std::cout<<"Type < = > when you are done\n";
    int check = 0;
    while (true)  // checking if the input is correct and filling Elements stack with expression
    {
        std::cin>>sym;
        if (sym == '=')
        {
            break;
        }

        if ((!isdigit(sym) && (check ^ 1)) || ((sym != '*' && sym != '+') && (check ^ 0)))  
        // checking if the input is correct and filling Elements stack with expression
        {                                                                              
            std::cout<<"Incorrect input: it shoud be like 1+2*6*9+4...= ";
            return 0;
        }

        check = (check ^ 1);
        Elements.push(sym);
    }
    Elements.pop();

    while (!Elements.empty())  // Filling Prefix stack with prefix expression (from right to left) ignoring < + >-es 
    // becouse if it's not < * > then it's < + > for sure 
    // (for example 1+2*3+4*5*6 (+ + 1 * 2 3 * 4 * 5 6) --> 6 5 * 4 * 3 2 * 1)
    
    {
        if(isdigit(Elements.top()))
        {
            Prefix.push(Elements.top());
            Elements.pop();
        }
        else if(Elements.top() == '+')
        {
            Elements.pop();
        }
        else if (Elements.top() == '*')
        {
            Elements.pop();
            Prefix.push(Elements.top());
            Prefix.push('*');
            Elements.pop();
        }
    }
   
    int temp; // for multiplication
    while(!Prefix.empty())
    {
        if (Prefix.top() == '*')
        {
            temp = 1;
            while (Prefix.top() == '*') 
            {
                Prefix.pop();
                temp = mul(temp,Prefix.top());
                Prefix.pop();
                
            }
            ans = ans + mul(temp,Prefix.top());
            Prefix.pop();
        }
        else
        {
            ans = add(ans,Prefix.top());
            Prefix.pop();
        }
    }
   std::cout<<"equals to "<<ans<<'\n';
   return 0;
}


int add(int a, char b)     
{ 
    b = (b ^ 48); // char nums in binary is like 0011xxxx so that 11 shoud be 00 to make it like integer binary

    //It 'XOR'es nums, then 'XOR'es the result with carries, and again and so on till there is no carries left 
    int sum;          
	do
    {       
		sum = (a^b);    
		b = (a&b)<<1;    //  carries 
		a = sum;         

	}while (b | 0);   //condition is same as (b != 0)
    return sum;   
}


int mul(int a, char b)
{ 
    b = (b ^ 48);   // char nums in binary is like 0011xxxx so that 11 shoud be 00 to make it like integer binary
    int idx = 1;
    int ans = 0;
    int sft_a = a;   // a * 2^(n)
    while(idx | 0)   //same as (idx != 0)
    {
        if (b & idx)  // if b has 1 in n(idx = 2^n)-th digit (digits (31 30 ... n-th ... 2 1 0))
        {
            ans = ans + sft_a; 
        }
        idx  = (idx<<1);
        sft_a = (sft_a<<1);
    }
    return ans;
}