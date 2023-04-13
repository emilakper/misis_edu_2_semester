#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <geo2d/geo2d.hpp>

TEST_CASE("Test 01") {
    CHECK(1 == 1);
    PolyLine x;
    x.CreateLine(5);
    x.writeTo();

}