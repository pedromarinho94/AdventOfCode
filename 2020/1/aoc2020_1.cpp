#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void get_value(const std::vector<int> &entries);

int main()
{
    std::ifstream myfile("input.txt");
    std::string input;
    std::vector<int> entries;
    
    if ( myfile.is_open() )
    {        
        while ( getline(myfile, input) )
        {
            int entry = stoi(input);
            
            entries.push_back(entry);
        } 
        
        get_value(entries);
        
        myfile.close();
    }
    else
    {
        std::cout << "Can't open file!" << std::endl;
    }
    
    return 0;
}

void get_value(const std::vector<int> &entries)
{    
    bool found = false;
    
    for (int i{0}; (i<entries.size()-1) && found==false; i++)
    {   
        for (int k=i+1; k<entries.size(); k++)
        {   
            if (2020 == (entries.at(i) + entries.at(k)) )
            {
                std::cout << "Entry 1: " << entries.at(i) << std::endl;
                std::cout << "Entry 2: " << entries.at(k) << std::endl;
                std::cout << "Result: " << entries.at(i) * entries.at(k) << std::endl;
                found=true;
                break;  
            }
        }
    }
}
