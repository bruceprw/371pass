// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/15581
// -----------------------------------------------------
// Catch2 — https://github.com/catchorg/Catch2
// Catch2 is licensed under the BOOST license
// -----------------------------------------------------
// This file contains tests adding, getting and deleting
// Items in the Category container.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/category.h"

SCENARIO("An empty Category can be constructed successfully", "[category]") {

  const std::string ident = "Test";

  GIVEN("the category identifier '" + ident + "'") {

    WHEN("a new Category object is constructed") {

      Category c{ident};

      THEN("it will contain zero Items/be empty") {

        REQUIRE(c.size() == 0);
        REQUIRE(c.empty());

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Items can be added to and retrieved from a Category", "[category]") {

  const std::string ident = "Test";

  GIVEN("a Category object with identifier '" + ident + "'") {

    Category c{ident};

    AND_GIVEN("an Item with identifier '" + ident + "'") {

      Item i{ident};

      WHEN("adding the Item") {

        THEN("true is returned") {

          REQUIRE(c.addItem(i) == true);

          AND_THEN("the Category contains 1 Item") {

            REQUIRE(c.size() == 1);
            REQUIRE_FALSE(c.empty());

            AND_THEN("getting the Item using the ident '" + ident +
                     "' will return the expected object") {

              REQUIRE(c.getItem(ident) == i);
              REQUIRE_FALSE(c.empty());

            } // AND_THEN

          } // AND_THEN

          AND_GIVEN("another Item with the same ident, '" + ident + "'") {

            Item i2{ident};

            WHEN("adding the Item") {

              THEN("false is returned and the size of the Category will not "
                   "change") {

                REQUIRE(c.addItem(i2) == false);
                REQUIRE(c.size() == 1);
                REQUIRE_FALSE(c.empty());

              } // THEN

            } // WHEN

          } // AND_GIVEN

          const std::string ident3 = "Test2";

          AND_GIVEN("another Item with the a different ident, '" + ident3 +
                    "'") {

            Item i3{ident3};

            WHEN("adding the Item") {

              THEN("true is returned and the size of the Category will be 2") {

                REQUIRE(c.addItem(i3) == true);
                REQUIRE(c.size() == 2);
                REQUIRE_FALSE(c.empty());

                AND_THEN("getting the Item using the ident '" + ident3 +
                         "' will return the expected object") {

                  REQUIRE(c.getItem(ident3) == i3);

                } // AND_THEN

              } // THEN

            } // WHEN

          } // AND_GIVEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("Items can be added to and deleted from a Category", "[category]") {

  const std::string ident = "Test";

  GIVEN("a Category object with identifier '" + ident + "'") {

    Category c{ident};

    AND_GIVEN("an Item with identifier '" + ident + "") {

      Item i{ident};

      WHEN("the entry is added") {

        THEN("true is returned") {

          REQUIRE(c.addItem(i) == true);

          AND_THEN("the Category contains 1 Item") {

            REQUIRE(c.size() == 1);
            REQUIRE_FALSE(c.empty());

            WHEN("getting the Item using the ident '" + ident + "'") {

              THEN("the Item object is returned") {

                REQUIRE(c.getItem(ident) == i);

              } // THEN

            } // WHEN

            WHEN("deleting a non-existent Item with ident 'blah'") {

              THEN("an std::out_of_range exception is thrown and the Category "
                   "will not change") {

                REQUIRE_THROWS_AS(c.deleteItem("blah"), std::out_of_range);
                REQUIRE(c.getItem(ident) == i);
                REQUIRE(c.size() == 1);

              } // THEN

            } // WHEN

            WHEN("deleting the added Item with ident '" + ident) {

              THEN("true is returned and the Category will be empty") {

                REQUIRE(c.deleteItem(ident) == true);
                REQUIRE_THROWS_AS(c.getItem(ident), std::out_of_range);
                REQUIRE(c.size() == 0);

              } // THEN

            } // WHEN

          } // AND_THEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO
