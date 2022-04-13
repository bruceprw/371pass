# 371pass - 972648 Edition

# Helper Functions
In order to make my life easier, I added a number of helper functions across the Wallet, Category, and Item classes.

* getEntries/getItems/getCategories() - Returns the whole member map belonging to each class, I added this to make it easier to access all the elements if I wanted to iterate through them
* contains() - Returns whether or not a container contains a given key - useful for error handling.
* getCategoryRef() - The template comments suggested that getCategory() should return a category object, this led to many hours angrily glaring at my monitor when none of my categories were updating. (I later remembered the difference between pass by reference and pass by value - which led to the creation of this function.)

# Clever things / Further work:
* action word case insensitivity - For some reason, the kind folks at the C++ HQ haven't written a std::string.tolower() function, so I had to use the std::transform function in order to make my action word case insensitive. I then tried to do this for all other command words (whilst avoiding editing the values in quotes), but this was too fiddly to get done in time.
* Edge case catching - Due to the open nature of our input, there are hundreds freaky little edge cases that I'm sure you have included in the hidden tests. I have done my best to cover as much as possible but I'm sure some will still slip through the cracks.