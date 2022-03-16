// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 972648
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "item.h"

// Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Item iObj{"identIdent"};
    Item::Item(std::string ident){
    this->ident = ident;
    this->entries = std::map<std::string, std::string>();
}

// Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of entries in the Item contains.
//
// Example:
//  Item iObj{"identIdent"};
//  auto size = iObj.size();

    unsigned int Item::size() const {
        return entries.size();
}

// Write a function, empty, that takes no parameters and returns true
//  if the number of entries in the Item is zero, false otherwise.
//
// Example:
//  Item iObj{"identIdent"};
//  auto empty = iObj.empty();
    bool Item::empty() const {
        return entries.empty();
}

// Write a function, setIdent, that takes one parameter, a string for a new
//  Item identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.setIdent("identIdent2");

    void Item::setIdent(std::string ident) {
        this->ident = ident;
}

// Write a function, getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"identIdent"};
//  auto ident = iObj.getIdent();

    std::string Item::getIdent() const {
        return this->ident;
}

// Write a function, addEntry, that takes two parameters, an entry
//  key and value and returns true if the entry was inserted into the
//  container or false if the entry already existed and was replaced.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");

    bool Item::addEntry(std::string key, std::string value) {
        entries[key] = value;
}

// Write a function, getEntry, that takes one parameter, an entry
//  key and returns its value. If no entry exists, throw an appropriate
//  exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  auto value = iObj.getEntry("key");

    std::string Item::getEntry(std::string key) const {
        if (entries.find(key) != entries.end()) {
            return entries.at(key);
        }
        else {
            //TODO throw appropriate exception
        }
}





// Write a function, deleteEntry, that takes one parameter, an entry
//  key, deletes it from the container, and returns true if the Item was
//  deleted. If no entry exists, throw an appropriate exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  iObj.deleteEntry("key");

    bool Item::deleteEntry(std::string key) {
        if (entries.find(key) != entries.end()) {
            entries.erase(key);
            return true;
        }
        else {
            //TODO: return appropriate exception
        }
    }



// Write an == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
//
// Example:
//  Item iObj1{"identIdent"};
//  iObj1.addEntry("key", "value");
//  Item iObj2{"identIdent2"};
//  if(iObj1 == iObj2) {
//    ...
//  }

    bool operator==(const Item &lhs, const Item &rhs) {
        if (lhs.ident == rhs.ident) {
            if (lhs.entries == rhs.entries) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }



// Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();

    std::string Item::str() const {
        std::stringstream sstr;
        sstr << "{";
        for(const auto& elem : entries) {
            sstr<< elem.first << ":" << elem.second << ",";
        }
        sstr.seekp(-1, sstr.cur); // Overwrite trailing comma.
        sstr << "}";
        return  sstr.str();
    }

