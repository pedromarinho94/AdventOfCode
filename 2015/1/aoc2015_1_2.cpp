#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string input;
    int floor=0;
    bool first_basement = false;
    
    std::ifstream myfile("input.txt");
    
    /* read file and save it to a string */
    if ( myfile.is_open() )
    {
        getline(myfile, input);
        
        //std::cout << input << std::endl;
        
        myfile.close();
    }
    else
    {
        std::cout << "Couldn't open file properly" << std::endl;
    }
    
    for (int i{0}; i<input.size(); i++)
    {
        if ( '(' == input.at(i) )
            floor++;
        else
            floor--;
            
        if ( (-1 == floor) && (false == first_basement) )
        {
            std::cout << "Index of basement: " << i+1 << std::endl;
            first_basement = true;
        }
    }
    
    std::cout << "Floor is: " << floor << std::endl;
    
    return 0;
}
