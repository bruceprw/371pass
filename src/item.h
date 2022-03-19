// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 972648
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// An Item class contains multiple 'entries' as
// key/value pairs (e.g., a key might be 'username'
// and a value would be the username, another might be
// 'url' and the value is the website address the
// username is for.
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>
#include "lib_json.hpp"


class Item {
private:
    std::string ident;
    std::map<std::string, std::string> entries;
    friend bool operator==(const Item& lhs, const Item& rhs);

public:

    Item(std::string ident);
    unsigned int size() const;
    bool empty() const;
    void setIdent(std::string ident);
    std::string getIdent() const;
    bool contains(const std::string& ident) const;
    bool addEntry(std::string key, std::string value);
    std::map<std::string, std::string> getEntries();
    std::string getEntry(std::string key) const;
    bool deleteEntry(std::string key);
    std::string str() const;
//    void to_json(nlohmann::json &j, const Item &i);

    std::map<std::string, std::string> getEntries() const;
};



#endif // ITEM_H
