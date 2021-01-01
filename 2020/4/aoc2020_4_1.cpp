#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void validation(std::vector<std::string> &passports, std::vector<std::string> &keys);
std::vector<std::string> get_keys(const std::vector<std::string> &passports);
bool check_key(const std::vector<std::string> &keys, const std::string &key);

int main(int argc, char *argv[])
{
    std::ifstream myfile(argv[1]);
    std::string input, aux_str;
    std::vector<std::string> passports;
    std::vector<std::string> keys;
    
    if ( myfile.is_open() )
    {
        while ( std::getline(myfile, input) )
        {
            if( input.size() == 0 )
            {
                //passport ends here
                passports.push_back(aux_str);
                aux_str.clear();
            }
            else
            {
                aux_str += input;
                aux_str += " ";
            }
        }
        passports.push_back(aux_str); //add last passport to vector
        
        keys = get_keys(passports);
        validation(passports, keys);
    }
    else
    {
        std::cout << "Couldn't open file!" << std::endl;
    }
    
    return 0;
}

void validation(std::vector<std::string> &passports, std::vector<std::string> &keys)
{
    //Hash Map
    std::unordered_map<std::string, std::string> base_hash_map;
    
    //vector of hash tables
    std::vector<std::unordered_map<std::string, std::string>> passports_map;
     
    for (auto key: keys)
    {
        if (key != "cid")
            base_hash_map[key];
    }
    
    for (auto n: base_hash_map)
    {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]" << std::endl;
    }
        
//    for (auto passport: passports)
//    {
//        std::cout << passport << std::endl;
//    }  
      
}

std::vector<std::string> get_keys(const std::vector<std::string> &passports)
{
    std::vector<std::string> KEYS;
    
    //iterate through all passports
    for (auto aux: passports)
    {   
        std::string key;
        bool stop_reading{false};
        
        //check keys for a single passport and add it to vector KEYS only if it's a new one
        for (int i{0}; i<aux.size(); i++)
        {
            if ( aux.at(i) != ':' && (stop_reading == false) )
            {
                key += aux.at(i);
            }

            if (aux.at(i) == ':')
            {
                if ( check_key(KEYS, key) )
                    KEYS.push_back(key);
                    
                key.clear();
                stop_reading = true;
            }
            
            if (aux.at(i) == ' ')
            {
                stop_reading = false;
            }         
        }
    }
    
    return KEYS;
}

bool check_key(const std::vector<std::string> &keys, const std::string &key)
{
    bool ret{true};
    
    if ( keys.empty() )
    {
        ret = true;
    }
    else
    {
        for (auto str: keys)
        {
            if ( key == str )
                ret = false;
        }
    }
    
    return ret;
}
