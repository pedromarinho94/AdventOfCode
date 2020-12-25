#include <iostream>
#include <fstream>
#include <string>

void calc_total(const std::string input, int &paper, int &ribbon);

int main()
{  
    std::ifstream myfile("input.txt");
                
    /* read file and save it to a string */
    if ( myfile.is_open() )
    {
        std::string input;
        int paper{0}, ribbon{0};
        
        /* reads one line at a time */
        while ( getline(myfile, input) )
        {   
            calc_total(input, paper, ribbon);
        }
        
        std::cout << "Total wrapping paper: " << paper << std::endl;
        std::cout << "Total ribbon: " << ribbon << std::endl;
        
        myfile.close();
    }
    else
    {
        std::cout << "Couldn't open file properly." << std::endl;
    }
}

void calc_total(const std::string input, int &paper, int &ribbon)
{
    std::string s_height, s_length, s_width;

    int i{0};
    
    /* read length until delimiter */
    while( input.at(i) != 'x' )
    {
        s_length += input.at(i);
        i++;
    }

    i++; // ignore delimiter
    
    /* read width until delimiter */
    while( input.at(i) != 'x' )
    {
        s_width += input.at(i);
        i++;
    }     

    i++; // ignore delimiter
    
    /* read height until delimiter */
    while( input[i] != '\0' )
    {
        s_height += input.at(i);
        i++;
    }    

    int length{0}, width{0}, height{0}, small{0}, c_length{0}, c_width{0}, c_height{0};
    
    length = stoi(s_length);
    width = stoi(s_width);
    height = stoi(s_height);

    c_length = length*width;
    c_width = width*height;
    c_height = height*length;

    if(c_length<=c_width && c_length<=c_height)
    {
        small = c_length;
    }
    else if(c_width<=c_height)
    {
        small = c_width;
    }
    else
    {
        small = c_height;
    }

    paper += 2*c_length + 2*c_width + 2*c_height + small;
    
    int volume{0}, perimeter{0};
    
    volume = length * width * height;
    
    if(length>=width && length>=height) // length biggest;
    {
        perimeter = 2*width + 2*height; 
    }
    else if(width>=height)              // width biggest;
    {
        perimeter = 2*height + 2*length; 
    }
    else                                // height biggest;
    {
        perimeter = 2*width + 2*length; 
    }
    
    ribbon += volume + perimeter;
}
