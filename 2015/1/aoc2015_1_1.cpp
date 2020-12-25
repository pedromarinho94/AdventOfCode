#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string input;
    int floor=0;
    
    std::ifstream myfile("input.txt");
    
    /* read file and save it to a string */
    if ( myfile.is_open() )
    {
        getline(myfile, input);
        
        std::cout << input << std::endl;
        
        myfile.close();
    }
    else
    {
        std::cout << "Couldn't open file properly" << std::endl;
    }
    
    for (auto c: input)
    {
        if(c == '(')
            floor++;
        else
            floor--;
    }
    
    std::cout << "Floor is: " << floor << std::endl;
    
    return 0;
}
