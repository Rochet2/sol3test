#include "stackinterface.h"
#include <limits>

#include "catch.hpp"

TEST_CASE("StackInterface")
{
    sol::state lua;

    SECTION("int64_t and uint64_t") {
#define MAKE_DEFINES(TYPE) \
        const TYPE max##TYPE = std::numeric_limits<TYPE>::max(); \
        const TYPE min##TYPE = std::numeric_limits<TYPE>::min(); \
        const TYPE zero##TYPE = 0; \
        lua[std::string("max")+#TYPE] = max##TYPE; \
        lua[std::string("min")+#TYPE] = min##TYPE; \
        lua[std::string("zero")+#TYPE] = zero##TYPE; \
        lua[std::string("f_max")+#TYPE] = [&](TYPE v) { REQUIRE(v == max##TYPE); }; \
        lua[std::string("f_min")+#TYPE] = [&](TYPE v) { REQUIRE(v == min##TYPE); }; \
        lua[std::string("f_pass")+#TYPE] = [&](TYPE) { };

        MAKE_DEFINES(int64_t);
        MAKE_DEFINES(uint64_t);
        MAKE_DEFINES(int32_t);
        MAKE_DEFINES(uint32_t);

        SECTION("operations") {
        }

        SECTION("passing") {
            SECTION("f_max") {
                REQUIRE_NOTHROW(lua.script("f_maxint64_t(maxint64_t)"));
                REQUIRE_NOTHROW(lua.script("f_maxuint64_t(maxuint64_t)"));
                REQUIRE_NOTHROW(lua.script("f_maxint32_t(maxint32_t)"));
                REQUIRE_NOTHROW(lua.script("f_maxuint32_t(maxuint32_t)"));
            }
            SECTION("f_min") {
                REQUIRE_NOTHROW(lua.script("f_minint64_t(minint64_t)"));
                REQUIRE_NOTHROW(lua.script("f_minuint64_t(minuint64_t)"));
                REQUIRE_NOTHROW(lua.script("f_minint32_t(minint32_t)"));
                REQUIRE_NOTHROW(lua.script("f_minuint32_t(minuint32_t)"));
            }
            SECTION("f_pass") {
                REQUIRE_NOTHROW(lua.script("f_passint64_t(zeroint64_t)"));
                REQUIRE_THROWS(lua.script("f_passint64_t(zerouint64_t)"));
                REQUIRE_THROWS(lua.script("f_passint64_t(-1)"));
                REQUIRE_THROWS(lua.script("f_passint64_t(1)"));

                REQUIRE_THROWS(lua.script("f_passuint64_t(zeroint64_t)"));
                REQUIRE_NOTHROW(lua.script("f_passuint64_t(zerouint64_t)"));
                REQUIRE_THROWS(lua.script("f_passuint64_t(-1)"));
                REQUIRE_THROWS(lua.script("f_passuint64_t(1)"));

                REQUIRE_THROWS(lua.script("f_passint32_t(zeroint64_t)"));
                REQUIRE_THROWS(lua.script("f_passint32_t(zerouint64_t)"));
                REQUIRE_NOTHROW(lua.script("f_passint32_t(-1)"));
                REQUIRE_NOTHROW(lua.script("f_passint32_t(1)"));

                REQUIRE_THROWS(lua.script("f_passuint32_t(zeroint64_t)"));
                REQUIRE_THROWS(lua.script("f_passuint32_t(zerouint64_t)"));
                REQUIRE_NOTHROW(lua.script("f_passuint32_t(-1)"));
                REQUIRE_NOTHROW(lua.script("f_passuint32_t(1)"));
            }
        }
    }
}
