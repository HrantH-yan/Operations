#include <iostream>
#include <stack>

int main()
{
    int ans = 0;
    char sym;
    std::stack<char> Elements; 
    std::stack<char> Prefix;   
    std::cout<<"Enter an expression which consists of digits, '+' and '*' operators \n";
    std::cout<<"Add '=' at the end:\n";

    int check = 0;
    while (true)  // checking if the input is correct and filling Elements stack with expression
    {
        std::cin>>sym;
        if (sym == '=')
        {
            break;
        }
        if ((!isdigit(sym) && (check == 0)) || ((sym != '*' && sym != '+') && (check == 1)))  
        // checking if the input is correct and filling Elements stack with expression
        {                                                                              
            std::cout<<"Incorrect input: it shoud be like 1+2*6*9+4...= ";
            return 0;
        }
        check = (check ^ 1);
        Elements.push(sym);
    }
    if (check == 0)
    {
        Elements.pop();
    }

    while (!Elements.empty())        // Filling Prefix stack with prefix expression (from right to left) ignoring '+'-es
    {                                // becouse if it's not '*' then it's '+'
        if(isdigit(Elements.top()))  // (for example 1+2*3+4*5*6 (+ + 1 * 2 3 * 4 * 5 6) --> 6 5 * 4 * 3 2 * 1)
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
    
    std::cout<<"equals to "<<ans<<'\n';
    return 0;
}
