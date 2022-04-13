// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 972648
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// A category contains one or more Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include <map>

#include "item.h"
#include "lib_json.hpp"

class Category {

private:
    std::map<std::string, Item> items;
    std::string ident;
    friend bool operator==(const Category& lhs, const Category& rhs);

public:
    Category(std::string ident);
    unsigned int size() const;
    bool empty() const;
    std::string getIdent() const;
    void setIdent(std::string id);
    const Item& newItem(std::string id);
    bool addItem(Item item);
    bool contains(const std::string& categoryID) const;

    bool mergeItems(Item& newItem, Item& originalItem);
    Item& getItem(std::string ident);
    std::map<std::string, Item> getItems() const;
    bool deleteItem(std::string ident);
    std::string str() const;
};



#endif // CATEGORY_H
