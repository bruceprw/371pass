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
// This file contains tests the equals operator overload
// for the Item, Category and Wallet objects.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"

#include "../src/item.h"
#include "../src/category.h"
#include "../src/wallet.h"

SCENARIO("The == operator on Item evaluates its contents correctly", "[item]") {

  const std::string ident1 = "ident1";
  const std::string ident2 = "ident2";

  const std::string key1 = "key1";
  const std::string key2 = "key2";

  const std::string value1 = "value1";
  const std::string value2 = "value2";

  GIVEN("an empty Item object with the identifier '" + ident1 + "'") {

    Item iObj1{ident1};

    REQUIRE(iObj1.empty());

    WHEN("compared against itself") {

      THEN("the result will be true") {

        REQUIRE(iObj1 == iObj1);

      } // THEN

    } // WHEN

    AND_GIVEN("another empty Item object with the same identifier '" + ident1 +
              "'") {

      Item iObj2{ident1};

      REQUIRE(iObj2.empty());

      WHEN("compared against each other") {

        THEN("the result will be true") {

          REQUIRE(iObj1 == iObj2);

        } // THEN

      } // WHEN

      WHEN("an entry is added to one of the Item objects") {

        REQUIRE(iObj1.addEntry(key1, value1) == true);

        AND_WHEN("compared against each other") {

          THEN("the result will be false") {

            REQUIRE_FALSE(iObj1 == iObj2);

          } // THEN

        } // AND_WHEN

        AND_WHEN("the same entry is added to the other Item object") {

          REQUIRE(iObj2.addEntry(key1, value1) == true);

          AND_WHEN("compared against each other") {

            THEN("the result will be true") {

              REQUIRE(iObj1 == iObj2);

            } // THEN

          } // AND_WHEN

        } // AND_WHEN

        AND_WHEN("a different entry is added to the other Item object") {

          REQUIRE(iObj2.addEntry(key2, value2) == true);

          AND_WHEN("compared against each other") {

            THEN("the result will be false") {

              REQUIRE_FALSE(iObj1 == iObj2);

            } // THEN

          } // AND_WHEN

        } // AND_WHEN

      } // WHEN

    } // AND_GIVEN

    AND_GIVEN("another empty Item object with identifier '" + ident2 + "'") {

      Item iObj2{ident2};

      REQUIRE(iObj2.empty());

      WHEN("compared against each other") {

        THEN("the result will be false") {

          REQUIRE_FALSE(iObj1 == iObj2);

        } // THEN

        AND_WHEN("an entry is added to one of the Item objects") {

          iObj1.addEntry(key1, value1);

          AND_WHEN("compared against each other") {

            THEN("the result will be false") {

              REQUIRE_FALSE(iObj1 == iObj2);

            } // THEN

          } // AND_WHEN

          AND_WHEN("the same entry is added to the other Item object") {

            iObj2.addEntry(key1, value1);

            AND_WHEN("compared against each other") {

              THEN("the result will be false") {

                REQUIRE_FALSE(iObj1 == iObj2);

              } // THEN

            } // AND_WHEN

          } // AND_WHEN

        } // AND_WHEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("The == operator on Category evaluates its contents correctly",
         "[category]") {

  const std::string ident1 = "ident1";
  const std::string ident2 = "ident2";

  GIVEN("an empty Category object with the identifier '" + ident1 + "'") {

    Category cObj1{ident1};

    REQUIRE(cObj1.empty());

    WHEN("compared against itself") {

      THEN("the result will be true") {

        REQUIRE(cObj1 == cObj1);

      } // THEN

    } // WHEN

    AND_GIVEN("another empty Category object with the same identifier '" +
              ident1 + "'") {

      Category cObj2{ident1};

      REQUIRE(cObj2.empty());

      WHEN("compared against each other") {

        THEN("the result will be true") {

          REQUIRE(cObj1 == cObj2);

        } // THEN

      } // WHEN

      WHEN("an Item is added to one of the Category objects") {

        Item iObj1{ident1};

        REQUIRE(cObj1.addItem(iObj1) == true);

        AND_WHEN("compared against each other") {

          THEN("the result will be false") {

            REQUIRE_FALSE(cObj1 == cObj2);

          } // THEN

        } // AND_WHEN

        AND_WHEN("the same Item is added to the other Category object") {

          REQUIRE(cObj2.addItem(iObj1) == true);

          AND_WHEN("compared against each other") {

            THEN("the result will be true") {

              REQUIRE(cObj1 == cObj2);

            } // THEN

          } // AND_WHEN

        } // AND_WHEN

        AND_WHEN("a different Item is added to the other Category object") {

          Item iObj2{ident2};

          REQUIRE(cObj2.addItem(iObj2) == true);

          AND_WHEN("compared against each other") {

            THEN("the result will be false") {

              REQUIRE_FALSE(cObj1 == cObj2);

            } // THEN

          } // AND_WHEN

        } // AND_WHEN

      } // WHEN

    } // AND_GIVEN

    AND_GIVEN("another empty Category object with identifier '" + ident2 +
              "'") {

      Category cObj2{ident2};

      REQUIRE(cObj2.empty());

      WHEN("compared against each other") {

        THEN("the result will be false") {

          REQUIRE_FALSE(cObj1 == cObj2);

        } // THEN

        AND_WHEN("an Item is added to one of the Category objects") {

          Item iObj1{ident1};

          REQUIRE(cObj1.addItem(iObj1) == true);

          AND_WHEN("compared against each other") {

            THEN("the result will be false") {

              REQUIRE_FALSE(cObj1 == cObj2);

            } // THEN

          } // AND_WHEN

          AND_WHEN("the same Item is added to the other Category object") {

            REQUIRE(cObj2.addItem(iObj1) == true);

            AND_WHEN("compared against each other") {

              THEN("the result will be false") {

                REQUIRE_FALSE(cObj1 == cObj2);

              } // THEN

            } // AND_WHEN

          } // AND_WHEN

        } // AND_WHEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("The == operator on Wallet evaluates its contents correctly",
         "[wallet]") {

  const std::string ident1 = "ident1";
  const std::string ident2 = "ident2";

  GIVEN("an empty Wallet object") {

    Wallet wObj1{};

    REQUIRE(wObj1.empty());

    WHEN("compared against itself") {

      THEN("the result will be true") {

        REQUIRE(wObj1 == wObj1);

      } // THEN

    } // WHEN

    AND_GIVEN("another empty Wallet object") {

      Wallet wObj2{};

      REQUIRE(wObj2.empty());

      WHEN("compared against each other") {

        THEN("the result will be true") {

          REQUIRE(wObj1 == wObj2);

        } // THEN

      } // WHEN

      WHEN("a Category is added to one of the Wallet objects") {

        Category cObj1{ident1};

        REQUIRE(wObj1.addCategory(cObj1) == true);

        AND_WHEN("compared against each other") {

          THEN("the result will be false") {

            REQUIRE_FALSE(wObj1 == wObj2);

          } // THEN

        } // AND_WHEN

        AND_WHEN("the same Category is added to the other Wallet object") {

          REQUIRE(wObj2.addCategory(cObj1) == true);

          AND_WHEN("compared against each other") {

            THEN("the result will be true") {

              REQUIRE(wObj1 == wObj2);

            } // THEN

          } // AND_WHEN

        } // AND_WHEN

        AND_WHEN("a different Category is added to the other Wallet object") {

          Category cObj2{ident2};

          REQUIRE(wObj2.addCategory(cObj2) == true);

          AND_WHEN("compared against each other") {

            THEN("the result will be false") {

              REQUIRE_FALSE(wObj1 == wObj2);

            } // THEN

          } // AND_WHEN

        } // AND_WHEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO
