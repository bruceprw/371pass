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
// Categorys in the Wallet container.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/wallet.h"

SCENARIO("An empty Wallet can be constructed successfully", "[wallet]") {

  GIVEN("nothing") {

    WHEN("a new Wallet object is constructed") {

      Wallet w{};

      THEN("it will contain zero Categories/be empty") {

        REQUIRE(w.size() == 0);
        REQUIRE(w.empty());

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Category objects can be added to and retrieved from a Wallet",
         "[wallet]") {

  GIVEN("a Wallet object") {

    Wallet w{};

    const std::string ident = "Test";

    AND_GIVEN("a Category with identifier '" + ident + "'") {

      Category c{ident};

      WHEN("adding the Category") {

        THEN("true is returned") {

          REQUIRE(w.addCategory(c) == true);

          AND_THEN("the Wallet contains 1 Category") {

            REQUIRE(w.size() == 1);
            REQUIRE_FALSE(w.empty());

            AND_THEN("getting the Category using the ident '" + ident +
                     "' will return the expected object") {

              REQUIRE(w.getCategory(ident) == c);

            } // AND_THEN

          } // AND_THEN

          AND_GIVEN("adding a second empty Category with the same ident, '" +
                    ident) {

            Category c2{ident};

            WHEN("adding the Category") {

              THEN("false is returned and the size of the Wallet will not "
                   "change") {

                REQUIRE_FALSE(w.addCategory(c2));
                REQUIRE(w.size() == 1);
                REQUIRE_FALSE(w.empty());

              } // THEN

            } // WHEN

          } // AND_GIVEN

          const std::string ident3 = "Test2";
          Category c3{ident3};

          AND_GIVEN("another Category with a different ident, '" + ident3) {

            WHEN("the Category is added") {

              THEN("true is returned and the size of the Wallet will be 2") {

                REQUIRE(w.addCategory(c3) == true);
                REQUIRE(w.size() == 2);
                REQUIRE_FALSE(w.empty());

                AND_THEN("getting the Category using the ident '" + ident3 +
                         "' will return the expected object") {

                  REQUIRE(w.getCategory(ident3) == c3);

                } // AND_THEN

              } // THEN

            } // WHEN

          } // AND_GIVEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("Category objects can be added to and deleted from a Wallet",
         "[wallet]") {

  GIVEN("a Wallet object") {

    Wallet w{};

    const std::string ident = "Test";

    WHEN("a Category with identifier '" + ident + "' can be added") {

      Category c{ident};

      REQUIRE(w.addCategory(c) == true);

      THEN("the Wallet contains 1 Category") {

        REQUIRE(w.size() == 1);
        REQUIRE_FALSE(w.empty());

      } // THEN

      THEN("the Category can be retrieved by the ident '" + ident + "'") {

        REQUIRE(w.getCategory(ident) == c);

      } // THEN

      THEN("deleting the existent Category ('" + ident +
           "') will leave the Wallet empty") {

        REQUIRE(w.deleteCategory(ident));
        REQUIRE_THROWS_AS(w.getCategory(ident), std::out_of_range);
        REQUIRE(w.size() == 0);

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO
