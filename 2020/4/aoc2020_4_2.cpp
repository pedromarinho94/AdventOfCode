#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::unordered_map<std::string, std::string>> fill_hash_map(std::vector<std::string> &passports, std::vector<std::string> &keys);
std::vector<std::string> get_keys(const std::vector<std::string> &passports);
bool check_key(const std::vector<std::string> &keys, const std::string &key);
void validation (const std::vector<std::unordered_map<std::string, std::string>> &vec_hash_map, const std::vector<std::string> &keys);
int evaluate_passport(const std::unordered_map<std::string, std::string> &passport);

int main(int argc, char *argv[])
{
    std::ifstream myfile(argv[1]);
    std::string input, aux_str;
    std::vector<std::string> passports;
    std::vector<std::string> keys;
    std::vector<std::unordered_map<std::string, std::string>> vec_hash_map;
    
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
        vec_hash_map = fill_hash_map(passports, keys);
        validation(vec_hash_map, keys);
    }
    else
    {
        std::cout << "Couldn't open file!" << std::endl;
    }
    
    return 0;
}

std::vector<std::unordered_map<std::string, std::string>> fill_hash_map(std::vector<std::string> &passports, std::vector<std::string> &keys)
{
    std::unordered_map<std::string, std::string> valid_keys_hash_map;
    std::unordered_map<std::string, std::string> aux_hash_map;
    std::vector<std::unordered_map<std::string, std::string>> vec_hash_map;

    for (auto key: keys)
    {
        if (key != "cid")
            valid_keys_hash_map[key];
    }
    
    for (auto passport: passports)
    {   
        aux_hash_map = valid_keys_hash_map;
        for (auto key: aux_hash_map)
        {
            size_t pos{0};
            pos = passport.find(key.first);
            
            if (pos != std::string::npos)
            {
                int aux_p = pos + key.first.size() + 1;
                
                while( passport.at(aux_p) != ' ' )
                {   
                    key.second += passport.at(aux_p);
                    aux_p++;
                }
                aux_hash_map[key.first]=key.second;
            }
            else
            {
                //key not found in passport
            }
        }
        vec_hash_map.push_back(aux_hash_map);
    }

    return vec_hash_map;   
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

void validation (const std::vector<std::unordered_map<std::string, std::string>> &vec_hash_map, const std::vector<std::string> &keys)
{
    int valid_nr{0};
    int valid{0};
    
    //iterate for each passport
    for (auto passport: vec_hash_map)
    {           
        valid = evaluate_passport(passport);
        
        if(valid == 7)
        {
            //std::cout << "Is valid!" << std::endl;
            valid_nr++;
        }
        else
        {
            //std::cout << "Is NOT valid!" << std::endl;
        }
    }
    std::cout << "Nr of valid passports: " << valid_nr << std::endl;
}

int evaluate_passport(const std::unordered_map<std::string, std::string> &passport)
{
    int ret{0};
    
    //iterate for each key of a passport
    for (auto key_val: passport)
    {   
        if(key_val.first == "byr" && !key_val.second.empty() )
        {
            int int_val = stoi(key_val.second);
            
            if ( (1920 <= int_val) && (int_val <= 2002) )
            {
                ret++;
            }
        }
        else if(key_val.first == "iyr" && !key_val.second.empty() )
        {
            int int_val = stoi(key_val.second);
            
            if ( (2010 <= int_val) && (int_val <= 2020) )
            {
                ret++;
            }        
        }
        else if(key_val.first == "eyr" && !key_val.second.empty() )
        {
            int int_val = stoi(key_val.second);
            
            if ( (2020 <= int_val) && (int_val <= 2030) )
            {
                ret++;
            }        
        }
        else if(key_val.first == "hgt" && !key_val.second.empty() )
        {
            size_t pos{0};
            int int_val = stoi(key_val.second);
            pos = key_val.second.find("cm");
            
            if (pos != std::string::npos) //found cm
            {
                if ( (150 <= int_val) && (int_val <= 193) )
                {
                    ret++;
                }        
            }
            else //found in
            {
                if ( (59 <= int_val) && (int_val <= 76) )
                {
                    ret++;
                }        
            }            
        }
        else if(key_val.first == "hcl" && !key_val.second.empty() )
        {
            size_t size = key_val.second.size();
            int pos{0};
            bool valid{true};
            char aux = key_val.second.at(pos);
            
            if ( (aux == '#') && (size == 7) )
            {   
                pos++;
                for (int i=pos; i<size; i++)
                {
                    aux = key_val.second.at(i);
                    
                    if ( ((48 <= aux) && (aux <= 57)) || ((97 <= aux) && (aux <= 102)) )
                    {
                        //do nothing
                    }
                    else
                    {
                        valid = false;
                    }
                }
                
                if(valid)
                    ret++; 
            }
        }
        else if(key_val.first == "ecl" && !key_val.second.empty() )
        {
            if ( (key_val.second == "amb") || 
                 (key_val.second == "blu") ||
                 (key_val.second == "brn") ||
                 (key_val.second == "gry") ||
                 (key_val.second == "grn") ||
                 (key_val.second == "hzl") ||
                 (key_val.second == "oth") )
            {
                ret++;
            }
        }
        else if(key_val.first == "pid" && !key_val.second.empty() )
        {   
            if ( key_val.second.size() == 9 )
            {
                ret++;
            }
             
        }
        else
        {
            //do nothing
        }
    }
    
    return ret;
}
