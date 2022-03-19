//
// Created by Bruce Williams on 18/03/2022.
//
#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371pass.h"


int main() {

    Item iObj1{"Starling"};
    std::string key = "Account Number";
    std::string value = "12345678";
    iObj1.addEntry(key, value);
    key = "Name";
    value = "Mr John Doe";
    iObj1.addEntry(key, value);
    key = "Sort Code";
    value = "12-34-56";
    iObj1.addEntry(key, value);

    Category cObj1{"Bank Accounts"};
    cObj1.addItem(iObj1);
    std::cout << cObj1.str();
//    std::cout << iObj1.str();
}