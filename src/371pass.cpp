// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 972648
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include "371pass.h"
#include "lib_cxxopts.hpp"
#include "wallet.h"

// Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Load the database file by calling load() on a Wallet object
//  2. Parse the 'action' argument to decide what action should be taken (
//     create, read, update, or delete). Read is the easiest to implement, and
//     update is the hardest. The details of how these arguments work is in the
//     coursework specification.
//  4. Save the updated Wallet object to the JSON file if there have been
//     changes (calling save() on the Wallet object).
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of software development.
//
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }
int App::run(int argc, char *argv[]) {
    auto options = App::cxxoptsSetup();
    auto args = options.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
        std::cout << options.help() << '\n';
        return 0;
    }


    // Open the database and construct the Wallet
    const std::string db = args["db"].as<std::string>();
    Wallet wObj{};
    wObj.load(db);

    try {
        if (argc == 1) {
            throw std::invalid_argument("missing action argument(s)");
        }

    }
    catch (const std::invalid_argument& invalid_argument) {
        std::cerr << "Error: " << invalid_argument.what();
    }
    Action a = Action::READ;
    try {
        a = parseActionArgument(args);

    }
    catch (const std::invalid_argument& invalid_argument) {
        std::cerr << "Error: invalid action argument(s).";
        return 1;
    }


    switch (a) {
        case Action::CREATE:
            try {
                if (!args.count("category") && !args.count("item") && !args.count("entry")) {
                    throw std::invalid_argument("missing category, item or entry argument(s).");
                } else if (!args.count("category") && (args.count("item") || args.count("entry"))) {
                    throw std::invalid_argument("missing category argument(s).");
                } else if (!args.count("item") && args.count("entry")) {
                    throw std::invalid_argument("missing item argument(s).");
                }
            }
            catch (const std::invalid_argument &invalid_argument) {
                std::cerr << "Error: " << invalid_argument.what();
                return 1;
            }

            try {
                if (args.count("category") && !args.count("item")) {
                    auto catName = args["category"].as<std::string>();
                    wObj.newCategory(catName);
                } else if (args.count("category") && args.count("item") && !args.count("entry")) {
                    auto catName = args["category"].as<std::string>();
                    auto itemName = args["item"].as<std::string>();
                    wObj.getCategoryRef(catName).newItem(itemName);

                } else if (args.count("category") && args.count("item") && args.count("entry")) {
                    auto catName = args["category"].as<std::string>();
                    auto itemName = args["item"].as<std::string>();
                    auto entry = args["entry"].as<std::string>();
                    auto entryDelimiterPos = entry.find(',');

                    auto entryName = entry.substr(0, entryDelimiterPos);
                    auto entryValue = entry.substr(entryDelimiterPos + 1);
                    if (!entryName.empty() && !entryValue.empty()) {
                        wObj.newCategory(catName);
                        wObj.getCategoryRef(catName).newItem(itemName);
                        wObj.getCategoryRef(catName).getItem(itemName).addEntry(entryName, entryValue);
                    }
                    else throw std::runtime_error("Entry ident/value not comma delimited.");

                }
            }

            catch (const std::runtime_error &runtime_error) {
                std::cerr << "Error: " << runtime_error.what();
                return 1;
            }

            catch (const std::out_of_range &out_of_range) {
                std::cerr << "Error: " << out_of_range.what();
            }

            wObj.save(db);
            break;

        case Action::READ:
            try {

                if (!args.count("category") && !args.count("item") && !args.count("entry") &&
                    (argc == 3 || argc == 5)) {
                    std::cout << getJSON(wObj);
                    break;
                }

                if (args.count("category") && !args.count("item")) {
                    auto catName = args["category"].as<std::string>();
                    if (wObj.contains(catName)) {
                        std::cout << getJSON(wObj, catName);
                        break;
                    } else throw std::runtime_error("invalid category argument(s).");
                } else if (args.count("category") && args.count("item")) {
                    auto catName = args["category"].as<std::string>();
                    auto itemName = args["item"].as<std::string>();
                    if (wObj.contains(catName)) {
                        auto cat = wObj.getCategory(catName);
                        if (cat.contains(itemName) && !args.count("entry") && args.count("item")) {
                            std::cout << getJSON(wObj, catName, itemName);
                            break;
                        } else if (cat.contains(itemName) && args.count("entry")) {
                            auto entryName = args["entry"].as<std::string>();
                            if (wObj.getCategory(catName).getItem(itemName).contains(entryName)) {
                                std::cout << getJSON(wObj, catName, itemName, entryName);
                                break;
                            } else throw std::runtime_error("invalid entry argument(s).");
                        } else throw std::runtime_error("invalid item argument(s).");
                    } else throw std::runtime_error("invalid category argument(s).");
                }

            }
            catch (const std::runtime_error &runtime_error) {
                std::cerr << "Error: " << runtime_error.what();
                return 1;
            }
            break;


        case Action::UPDATE:
            try {
                if (!args.count("category") && !args.count("item") && !args.count("entry")) {
                    throw std::invalid_argument("missing category, item or entry argument(s).");
                } else if (!args.count("category") && (args.count("item") || args.count("entry"))) {
                    throw std::invalid_argument("missing category argument(s).");
                } else if (!args.count("item") && args.count("entry")) {
                    throw std::invalid_argument("missing item argument(s).");
                }
            }
            catch (const std::invalid_argument &invalid_argument) {
                std::cerr << "Error: " << invalid_argument.what();
                return 1;
            }

            try {
                if (args.count("category") && !args.count("item") && !args.count("entry")) {
                    auto catName = args["category"].as<std::string>();
                    auto delimiterPos = catName.find(':');

                    if (delimiterPos == std::string::npos) {
                        throw std::runtime_error("oldident:newident not formatted correctly.");
                    } else {
                        auto oldCatIdent = catName.substr(0, delimiterPos);
                        auto newCatIdent = catName.substr(delimiterPos + 1);

                        if (wObj.contains(oldCatIdent)) {
                            wObj.getCategoryRef(oldCatIdent).setIdent(newCatIdent);
                            std::cout << wObj.contains(newCatIdent) << std::endl;
                        } else throw std::runtime_error("invalid category argument(s).");
                    }
                } else if (args.count("category") && args.count("item") && !args.count("entry")) {
                    auto catName = args["category"].as<std::string>();
                    auto itemName = args["item"].as<std::string>();
                    auto delimiterPos = itemName.find(':');

                    if (delimiterPos == std::string::npos) {
                        throw std::runtime_error("oldident:newident not formatted correctly.");
                    } else {
                        auto oldItemIdent = itemName.substr(0, delimiterPos);
                        auto newItemIdent = itemName.substr(delimiterPos + 1);

                        if (wObj.contains(catName) && wObj.getCategoryRef(catName).contains(oldItemIdent)) {
                            wObj.getCategoryRef(catName).deleteItem(oldItemIdent);
                            wObj.getCategoryRef(catName).addItem(newItemIdent);
                        } else throw std::invalid_argument("invalid item or category argument(s).");
                    }
                }

                    else if (args.count("category") && args.count("item") && args.count("entry")) {
                        auto catName = args["category"].as<std::string>();
                        auto itemName = args["item"].as<std::string>();
                        auto entry = args["entry"].as<std::string>();

                        auto colonPos = entry.find(':');
                        if (colonPos == std::string::npos-1) {
                            throw std::runtime_error("invalid entry argument(s).");
                        } else {

                            auto oldEntryIdent = entry.substr(0, colonPos);
                            auto newEntryIdent = entry.substr(colonPos + 1);
                            try {
                                if (oldEntryIdent.empty() || newEntryIdent.empty() || entry.back() == ':') {
                                    throw std::runtime_error("invalid entry argument(s).");
                                }
                            }
                            catch (const std::runtime_error& runtime_error) {
                                std::cerr << "Error: " << runtime_error.what();
                                return 1;
                            }

                            //Just update entry ident.
                            // --entry "oldkey:newkey"
                            if (wObj.contains(catName) && (entry.find(':')  != std::string::npos )&& (entry.find(',')== std::string::npos)){

                                if (wObj.getCategoryRef(catName).getItem(itemName).contains(oldEntryIdent)) {
                                    auto oldValue = wObj.getCategoryRef(catName).getItem(itemName).getEntries().at(oldEntryIdent);
                                    wObj.getCategoryRef(catName).getItem(itemName).deleteEntry(oldEntryIdent);
                                    wObj.getCategoryRef(catName).getItem(itemName).addEntry(newEntryIdent, oldValue);
                                }


                            }

                            // update both entry ident and value
                            // --entry "oldkey:newkey,value"
                            else if (wObj.contains(catName) && (entry.find(':')  != std::string::npos )&& (entry.find(',')!= std::string::npos)){
                                auto commaPos = entry.find(',');
                                newEntryIdent = entry.substr(colonPos, commaPos);
                                auto newEntryValue = entry.substr(commaPos+1);
                                wObj.getCategoryRef(catName).getItem(itemName).deleteEntry(oldEntryIdent);
                                wObj.getCategoryRef(catName).getItem(itemName).addEntry(newEntryIdent, newEntryValue);
                            }
                            // Update entry value but not ident
                            // --entry "oldkey,newvalue"
                            else if (wObj.contains(catName) && (entry.find(':')  == std::string::npos )&& (entry.find(',')!= std::string::npos)){
                                auto commaPos = entry.find(',');

                                auto originalEntryIdent = entry.substr(0, commaPos);
                                auto newEntryValue = entry.substr(commaPos+1);
                                wObj.getCategoryRef(catName).getItem(itemName).deleteEntry(originalEntryIdent);
                                wObj.getCategoryRef(catName).getItem(itemName).addEntry(originalEntryIdent, newEntryValue);
                            }


                            else throw std::invalid_argument("invalid item or category argument(s).");
                        }

                    }
                }

                catch (const std::runtime_error &runtime_error) {
                    std::cerr << "Error: " << runtime_error.what();
                    return 1;
                }

                wObj.save(db);
                break;

                case Action::DELETE:

                    try {
                        if (!args.count("category") && !args.count("item") && !args.count("entry")) {
                            throw std::invalid_argument("missing category, item or entry argument(s).");
                        } else if (!args.count("category") && (args.count("item") || args.count("entry"))) {
                            throw std::invalid_argument("missing category argument(s).");
                        } else if (!args.count("item") && args.count("entry")) {
                            throw std::invalid_argument("missing item argument(s).");
                        }
                    }
                    catch (const std::invalid_argument &invalid_argument) {
                        std::cerr << "Error: " << invalid_argument.what();
                        return 1;
                    }
                try {
                    if (args.count("category") && !args.count("item") && !args.count("entry")) {
                        auto catName = args["category"].as<std::string>();
                        if (wObj.contains(catName)) {
                            wObj.deleteCategory(catName);
                        } else {
                            throw std::runtime_error("invalid category argument(s).");
                        }
                    } else if (args.count("category") && args.count("item") && !args.count("entry")) {
                        auto catName = args["category"].as<std::string>();
                        auto itemName = args["item"].as<std::string>();
                        if (wObj.contains(catName) && wObj.getCategoryRef(catName).contains(itemName)) {
                            wObj.getCategoryRef(catName).deleteItem(itemName);
                        } else throw std::invalid_argument("invalid item argument(s).");
                    }

                    if (args.count("category") && args.count("item") && args.count("entry")) {
                        auto catName = args["category"].as<std::string>();
                        auto itemName = args["item"].as<std::string>();
                        auto entry = args["entry"].as<std::string>();

                        auto entryDelimiterPos = entry.find(',');

                        auto entryName = entry.substr(0, entryDelimiterPos);

                        wObj.getCategoryRef(catName).getItem(itemName).deleteEntry(entryName);

                    }
                }

                catch (const std::runtime_error &runtime_error) {
                    std::cerr << "Error: " << runtime_error.what();
                    return 1;
                }

                wObj.save(db);
                break;
        default:
            return 1;

            }


    return 0;
}


// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
cxxopts::Options App::cxxoptsSetup() {
  cxxopts::Options cxxopts("371pass", "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db", "Filename of the 371pass database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action", "Action to take, can be: 'create', 'read', 'update', 'delete'.",
      cxxopts::value<std::string>())(

      "category",
      "Apply action to a category (e.g., if you want to add a category, set the"
      " action argument to 'add' and the category argument to your chosen"
      " category identifier).",
      cxxopts::value<std::string>())(

      "item",
      "Apply action to an item (e.g., if you want to add an item, set the "
      "action argument to 'add', the category argument to your chosen category "
      "identifier and the item argument to the item identifier).",
      cxxopts::value<std::string>())(

      "entry",
      "Apply action to an entry (e.g., if you want to add an entry, set the "
      "action argument to 'add', the category argument to your chosen category "
      "identifier, the item argument to your chosen item identifier, and the "
      "entry argument to the string 'key,value'). If there is no comma, an "
      "empty entry is inserted. If you are simply retrieving an entry, set the "
      "entry argument to the 'key'. If you are updating an entry key, use a : "
      "e.g., oldkey:newkey,newvalue.",
      cxxopts::value<std::string>())(

      "h,help", "Print usage.");

  return cxxopts;
}

// Rewrite this function so that it works. This function should
//  case-insensitively check the action argument retrieved from cxxopts and
//  convert this to a value from the ACTION enum. If an invalid value is given
//  in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
    std::string input = args["action"].as<std::string>();

    // Make input case-insensitive by transforming string to lowercase:
    std::transform(input.begin(), input.end(),
                   input.begin(), [](unsigned char c){ return std::tolower(c);});
    try {
        //Check for arg completeness
        if (!args.count("category") && args.count("item")) {
            throw std::invalid_argument("missing category argument(s).");
        } else if (!args.count("category") && args.count("entry")) {
            throw std::invalid_argument("missing category argument(s).");
        } else if (!args.count("item") && (args.count("category") && args.count("entry"))) {
            throw std::invalid_argument("missing item argument(s).");
        }
    }
        catch (const std::invalid_argument &invalid_argument) {
            std::cerr << "Error: " << invalid_argument.what();
            exit(1);
        }

        if (input == "create") {
            return Action::CREATE;
        } else if (input == "read") {
            return Action::READ;
        } else if (input == "update") {
            return Action::UPDATE;
        } else if (input == "delete") {
            return Action::DELETE;
        }
        else {
            throw std::invalid_argument("action");
        }
}

//  Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::cout << getJSON(wObj);
std::string App::getJSON(Wallet &wObj) { 
  // Only uncomment this once you have implemented the functions used!
   return wObj.str();
}

//  Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Category in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(wObj, c);
std::string App::getJSON(Wallet &wObj, const std::string &c) {
//  return "{}";
  // Only uncomment this once you have implemented the functions used!
   auto cObj = wObj.getCategory(c);
   return cObj.str();
}

//  Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Item in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::cout << getJSON(wObj, c, i);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i) {
//  return "{}";
  // Only uncomment this once you have implemented the functions used!
   auto cObj = wObj.getCategory(c);
   const auto iObj = cObj.getItem(i);
   return iObj.str();
}

//  Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Entry in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::string e = "entry argument value";
//  std::cout << getJSON(wObj, c, i, e);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i, const std::string &e) {
//  return "{}";
  // Only uncomment this once you have implemented the functions used!
   auto cObj = wObj.getCategory(c);
   auto iObj = cObj.getItem(i);
   return iObj.getEntry(e);
}
