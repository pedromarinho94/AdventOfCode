#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define RIGHT 3

void count_trees(const std::string &input);

int main()
{
    std::ifstream myfile("input.txt");
    std::string input;
    
    if ( myfile.is_open() )
    {
        while ( getline(myfile, input) )
        {
            count_trees(input);
        }

        myfile.close();
    }
    else
    {
        std::cout << "Can't open file!" << std::endl;
    }
    
    return 0;
}

void count_trees(const std::string &input)
{   
    static bool flag{false};
    static int line{1};
    static int last_pos{RIGHT};
    static int i{0}, nr_trees{0};
    
    //count tree at +[3;1]    
    if( input.at(i) == '#' && line!=0 && flag==false)
    {
        nr_trees++;
        std::cout << "▲ nr:" << nr_trees << " at [" << line << ";" << i << "]" << std::endl;
    }     
    else if (flag == false)
    {
        //std::cout << "at [" << line << ";" << i << "]" << std::endl;
    } 
    
    // go left 3 times
    for(int j=i+last_pos; i<j; i++)
    {   
        //abrupt line change     
        if ( i == input.size()-1 )
        {   
            last_pos = j-i-1;
            i=0;
            line++;
            flag=true;
            //std::cout << "c:forward" << std::endl;
            //std::cout << "c:down" << std::endl;
            return;
        }
        else
        {
            last_pos = RIGHT;
        }
    //std::cout << "forward" << std::endl;
    }
    
    //count tree at +[3;1] after abrupt line change
    if( input.at(i) == '#' && line!=0 && flag == true)
    {
        nr_trees++;
        std::cout << "p:▲ nr:" << nr_trees << " at [" << line << ";" << i << "]" << std::endl;
        last_pos = RIGHT;
        flag=false;
        
        // go left 3 times
        for(int j=i+last_pos; i<j; i++)
        {        
            //std::cout << "p:forward" << std::endl;
        }
    }     
    
        
    //position check at +[3;1] after abrupt line change
    if( input.at(i) != '#' && line!=0 && flag == true)
    {   
        //std::cout << "pp:at [" << line << ";" << i << "]" << std::endl;
        last_pos = RIGHT;
        flag=false;
        
        // go left 3 times
        for(int j=i+last_pos; i<j; i++)
        {        
            //std::cout << "pp:forward" << std::endl;
        }
    }   
    
    //next line
    //std::cout << "down" << std::endl;   
    line++;
    return;
}
