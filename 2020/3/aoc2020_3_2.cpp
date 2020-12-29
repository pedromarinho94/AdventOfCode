#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void count_trees_down_one(const std::string &input, const int &right, int &nr_trees, int &last_pos, int &i, int &line, bool &flag);

void count_trees_down_two(const std::string &input, const int &right, int &nr_trees, int &last_pos, int &i, int &line, bool &flag);

int main()
{
    std::ifstream myfile("input.txt");
    std::string input;
    int nr_trees1{0}, nr_trees3{0}, nr_trees5{0}, nr_trees7{0}, nr_trees2{0};
    int last_pos1{1}, last_pos3{3}, last_pos5{5}, last_pos7{7}, last_pos2{1};
    int i1{0}, i3{0}, i5{0}, i7{0}, i2{0};
    int line1{1}, line3{1}, line5{1}, line7{1}, line2{0};
    bool flag1{false}, flag3{false}, flag5{false}, flag7{false}, flag2{false};
    unsigned int mult{0};
    
    if ( myfile.is_open() )
    {
        while ( getline(myfile, input) )
        {
            count_trees_down_one(input, 1, nr_trees1, last_pos1, i1, line1, flag1);
            count_trees_down_one(input, 3, nr_trees3, last_pos3, i3, line3, flag3);
            count_trees_down_one(input, 5, nr_trees5, last_pos5, i5, line5, flag5);
            count_trees_down_one(input, 7, nr_trees7, last_pos7, i7, line7, flag7);
            count_trees_down_two(input, 1, nr_trees2, last_pos2, i2, line2, flag2);
        }

        std::cout << "Right 1, down 1 -> " << nr_trees1 << std::endl;
        std::cout << "Right 3, down 1 -> " << nr_trees3 << std::endl;
        std::cout << "Right 5, down 1 -> " << nr_trees5 << std::endl;
        std::cout << "Right 7, down 1 -> " << nr_trees7 << std::endl;
        std::cout << "Right 1, down 2 -> " << nr_trees2 << std::endl;
                
        mult = nr_trees1 * nr_trees3 * nr_trees5 * nr_trees7 * nr_trees2;
        
        std::cout << "Mult: " << mult << std::endl;
        
        myfile.close();
    }
    else
    {
        std::cout << "Can't open file!" << std::endl;
    }
    
    return 0;
}

void count_trees_down_one(const std::string &input, const int &right, int &nr_trees, int &last_pos, int &i, int &line, bool &flag)
{    
    //count tree at +[3;1]    
    if( input.at(i) == '#' && line!=0 && flag==false)
    {
        nr_trees++;
        //std::cout << "▲ nr:" << nr_trees << " at [" << line << ";" << i << "]" << std::endl;
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
            last_pos = right;
        }
    //std::cout << "forward" << std::endl;
    }
    
    //count tree at +[3;1] after abrupt line change
    if( input.at(i) == '#' && line!=0 && flag == true)
    {
        nr_trees++;
        //std::cout << "p:▲ nr:" << nr_trees << " at [" << line << ";" << i << "]" << std::endl;
        last_pos = right;
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
        last_pos = right;
        flag=false;

        // go left 3 times
        for(int j=i+last_pos; i<j; i++)
        {
            //std::cout << "pp:forward" << std::endl;
        }
    }

    //std::cout << "down" << std::endl;
    line++;
    return;
}

void count_trees_down_two(const std::string &input, const int &right, int &nr_trees, int &last_pos, int &i, int &line, bool &flag)
{    
    static int one_more{0};
    
    if(one_more == 1)
    {
        one_more = 0;
        //std::cout << "2:down" << std::endl;
        return;
    }
        
    //count tree at +[3;1]    
    if( input.at(i) == '#' && line!=0 && flag==false)
    {
        nr_trees++;
        //std::cout << "▲ nr:" << nr_trees << " at [" << line << ";" << i << "]" << std::endl;
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
            line++;
            flag=true;
            one_more = 1;
            //std::cout << "c:forward" << std::endl;
            //std::cout << "c:down" << std::endl;
            return;
        }
        else
        {
            last_pos = right;
        }
    //std::cout << "forward" << std::endl;
    }
    
    //count tree at +[3;1] after abrupt line change
    if( input.at(i) == '#' && line!=0 && flag == true)
    {
        nr_trees++;
        //std::cout << "p:▲ nr:" << nr_trees << " at [" << line << ";" << i << "]" << std::endl;
        last_pos = right;
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
        last_pos = right;
        flag=false;

        // go left 3 times
        for(int j=i+last_pos; i<j; i++)
        {
            //std::cout << "pp:forward" << std::endl;
        }
    }

    line++;
    line++;
    one_more = 1;
    //std::cout << "down" << std::endl;
    return;
}
