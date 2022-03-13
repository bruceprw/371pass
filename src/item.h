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
#include <unordered_map>
#include <string>
#include <sstream>

class Item {

public:

    Item(std::string ident);
    unsigned int size() const;
    bool empty() const;
    void setIdent(std::string ident);
    std::string getIdent() const;
    bool addEntry(std::string key, std::string value);
    std::string getEntry(std::string key) const;
    bool deleteEntry(std::string key);
    std::string str() const;

private:
    std::unordered_map<std::string, std::string> entries;
    std::string ident;
    friend bool operator==(const Item& lhs, const Item& rhs);

};



#endif // ITEM_H
