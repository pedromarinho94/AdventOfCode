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
    std::string s_pos1, s_pos2;
    int i{0}, pos1{0}, pos2{0};
    char letter;
    
    while (input.at(i) != '-')
    {
        s_pos1 += input.at(i);
        i++;
    }
    i++;
    pos1 = stoi(s_pos1);
    
    while (input.at(i) != ' ')
    {
        s_pos2 += input.at(i);
        i++;
    }
    pos2 = stoi(s_pos2);
    
    while (input.at(i) != ':')
    {
        i++;
    }
    letter = input.at(i-1);

    while (input.at(i) != ' ')
    {
        i++;
    }
    i++;
    
    pos1--;
    pos2--;
    
    if ( (input.at(i+pos1) == letter) && (input.at(i+pos2) == letter) )
        return false;
    else if ( (input.at(i+pos1) == letter) || (input.at(i+pos2) == letter) )
        return true;
    else
        return false;
}
