#ifndef _INIPARSER
#define _INIPARSER
#include <fstream>
#include <string>
#include <vector>
#include <map>


class IniParser {
private:

    struct entry_s {

        std::string section;

        std::string name;

        std::string value;
		entry_s():section(""),name(""),value(""){}
        struct entry_s & clear(void)
        {
          
            section.erase();
            name.erase();
            value.erase();
            
            return *this;
        }
    };


    std::vector<struct entry_s> entry;


public:


    IniParser(void);


    explicit IniParser(const std::string &fname);

    int readFile(const std::string &fname);

    int getValue(
            std::string section, std::string name, std::string *value) const;


    int getValue(std::string section, std::string name, int *value) const;

    int getValue(std::string section, std::string name, double *value) const;
	 int getValue(std::string section, std::string name, float *value) const;

    int getValue(
            std::string section,
            std::string name, std::vector<std::string> *value) const;

  
    int getValue(std::string section, std::string name, bool *value) const;

 
    std::multimap<std::string, std::string> getOptions(const std::string &section) const;

    
    std::vector<std::string> getSections() const;
	int saveEntry(const std::string &fname) const;
	int addEntry(std::string section, std::string name, std::string value);
};

#endif 
