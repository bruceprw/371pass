// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 972648
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// The root object that holds all data for 371pass. This
// class contains Categories, which in turn hold Items,
// which hold a mapping of entries.
// -----------------------------------------------------

#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <map>
#include "category.h"

class Wallet {
public:
    Wallet();

    unsigned int size() const;
    bool empty() const;
    Category& newCategory(std::string categoryID);
    bool contains(const std::string& categoryID) const;
    bool addCategory(Category category);
    bool mergeCategories(Category& newCategory, Category& originalCategory);
    Category getCategory(std::string categoryID);
    bool deleteCategory(std::string categoryID);
    void load(std::string filename);
    void save(std::string filename);
    std::string str();

private:
    std::map<std::string, Category> categories;
    friend bool operator==(const Wallet& lhs, const Wallet& rhs);


};

#endif // WALLET_H
