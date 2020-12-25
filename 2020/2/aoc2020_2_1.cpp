#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool is_pw_valid(const std::string &input);

int main()
{
    std::ifstream myfile("input.txt");
    std::string input;
    int valid{0}, invalid{0};
    
    if ( myfile.is_open() )
    {
        while ( getline(myfile,input) )
        {
            if ( is_pw_valid(input) )
            {
                valid++;
            }
            else
            {
                invalid++;
            }
        }
        
        std::cout << "Nr of valid pws: " << valid << std::endl;
    }
    else
    {
        std::cout << "Can't open file!" << std::endl;
    }
    
    return 0;
}

bool is_pw_valid(const std::string &input)
{
    std::string s_lowest, s_highest;
    int i{0}, lowest{0}, highest{0}, counter{0};
    char letter;
    
    while (input.at(i) != '-')
    {
        s_lowest += input.at(i);
        i++;
    }
    i++;
    lowest = stoi(s_lowest);
    
    while (input.at(i) != ' ')
    {
        s_highest += input.at(i);
        i++;
    }
    highest = stoi(s_highest);
    
    while (input.at(i) != ':')
    {
        i++;
    }
    letter = input.at(i-1);

    while (input.size() != i)
    {
        if (input.at(i) == letter)
        {
            counter++;
        }
        i++;
    }
    
    if( (counter >= lowest) && (counter <= highest) )
        return true;
    else
        return false;
}
