#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "greet.h"

TEST_CASE("app should have a greeting") {
    REQUIRE( greet() == "Hello world!" );
}
