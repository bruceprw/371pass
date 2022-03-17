// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 972648
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "category.h"

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};

Category::Category(std::string ident) {
    this->ident = ident;
    this->items = std::map<std::string, Item>();
}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();
unsigned int Category::size() const{
    return  this->items.size();
}



// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of Items in the Category is zero, false otherwise.
//
// Example:
//  Category c{"categoryIdent"};
//  auto empty = c.empty();

bool Category::empty() const {
    if (this->items.size() == 0){
        return true;
    }
    else return false;
}

// TODO Write a function, getIdent, that returns the identifier for the
//  Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();

std::string Category::getIdent() const {
    return this->ident;
}


// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");

void Category::setIdent(std::string ident) {
    this->ident = ident;
}



// TODO Write a function, newItem, that takes one parameter, an Item identifier,
//  (a string) and returns the Item object as a reference. If an object with the
//  same identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");

const Item &Category::newItem(std::string ident) {
    auto foundItem = this->items.find(ident);
    if (foundItem != this->items.end()) {
        return (Item&) *foundItem;
    }
    else {
        auto item = Item(ident);
        if (addItem(item)) {
            const Item& myRef = (Item&) this->items.find(ident)->second;
            return myRef;
        }
        else throw std::runtime_error("Cannot insert newItem");
    }
}

// TODO Write a function, addItem, that takes one parameter, an Item object,
//  and returns true if the object was successfully inserted. If an object with
//  the same identifier already exists, then the contents should be merged and
//  return false.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);

bool Category::addItem(Item item) {
    auto foundItem = this->items.find(item.getIdent());
    if(foundItem != this->items.end()) {
        mergeItems(const_cast<Item &>(item), (Item &) *foundItem);
        return false;
    }

    else {
        this->items.insert(std::pair<std::string, Item>(item.getIdent(), item));
        return true;
    }


}

// In the case that we are trying to add an item with an ident that is already in our map of items,
// merge the contents of the new item with those of the original item.
bool Category::mergeItems(Item& newItem, Item& originalItem) {

    auto newEntries = newItem.getEntries();
    for (auto const& it : newEntries){
        if (!originalItem.addEntry(it.first, it.second)){
            return false;
        }
    }
    return true;
}





// TODO Write a function, getItem, that takes one parameter, an Item
//  identifier (a string) and returns the Item as a reference. If no Item
//  exists, throw an appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  auto iObj = cObj.getItem("itemIdent");

Item& Category::getItem(std::string ident) {
    auto foundItem = this->items.find(ident);
    if(foundItem != this->items.end()) {
        return this->items.find(ident)->second;

    }
    else {
        throw std::out_of_range("No item with given ident found!");
    }

}

// TODO Write a function, deleteItem, that takes one parameter, an Item
//  identifier (a string), deletes it from the container, and returns true if
//  the Item was deleted. If no Item exists, throw an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  bool result = cObj.deleteItem("itemIdent");

bool Category::deleteItem(std::string ident) {
    auto foundItem = this->items.find(ident);
    if(foundItem != this->items.end()) {
        this->items.erase(ident);
        return true;
    }
    else throw std::out_of_range("No item with given ident found");
}



// TODO Write an == operator overload for the Category class, such that two
//  Category objects are equal only if they have the same identifier and same
//  Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj1.newItem("itemIdent");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }

bool operator==(const Category &lhs, const Category &rhs) {
    if (lhs.ident == rhs.ident) {
        if (lhs.items == rhs.items) {
            return true;
        }
        else return false;
    }
    else return false;
}



// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
std::string Category::str() {
    nlohmann::json j_items(this->items);
    return j_items.dump();
}

