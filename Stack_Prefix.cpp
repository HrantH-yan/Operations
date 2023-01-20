#include <iostream>
#include <stack>


int main()
{
    int ans = 0;
    char sym;
    std::stack<char> Elements; 
    std::stack<char> Prefix;   
    std::cout<<"Enter an expression: Only digits, '+' and '*' operators \n";
    std::cout<<"Add '=' at the end:\n";

    int check = 0;
    std::cin>>sym;
    while (sym != '=') // checking input and filling 'Elements' with expression
    {  
        if ((!isdigit(sym) && (check == 0)) || (sym != '*' && sym != '+' && (check == 1)))  
        {                                                                              
            std::cerr<<"Incorrect input: correct example '1+2*6*9+4...+1 ='\n";
            return 1;
        }
        check = (check ^ 1);
        Elements.push(sym);
        std::cin>>sym;
    }
    if (check == 0)
    {
        Elements.pop();
    }

    while (!Elements.empty())              // Filling Prefix stack with prefix expression
    {                                      // (from right to left) ignoring '+'-es
        if(isdigit(Elements.top()))        // becouse if it's not '*' then it's '+'
        {                                  // 1+2*3+4*5*6 (++1*2 3*4*5 6)-->(6 5*4*3 2*1)
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
    
    int temp;    // for multiplication
    while(!Prefix.empty())
    {
        if (Prefix.top() == '*')
        {
            temp = 1;
            while (Prefix.top() == '*') 
            {
                Prefix.pop();
                temp = temp * (Prefix.top() ^ 48);
                Prefix.pop();
            }
            ans = ans + temp * (Prefix.top() ^ 48);
            Prefix.pop();
        }
        else
        {
            ans = ans + (Prefix.top() ^ 48);
            Prefix.pop();
        }
    }
    
    std::cout<<"Equal to "<<ans<<'\n';
    return 0;
}
