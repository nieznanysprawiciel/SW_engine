/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014, 2015 - 2016 Axel Menzel <info@rttr.org>                     *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
*************************************************************************************/

#include <catch/catch.hpp>

#include <rttr/type>

using namespace rttr;

struct type_with_no_equal_operator
{
    int i;
};

struct other_type_with_no_equal_operator
{
    int i;
};

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("variant::operator==() - empty", "[variant]")
{
    SECTION("empty type")
    {
        variant a;
        variant b;

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("valid type - lhs")
    {
        variant a = 23;
        variant b;

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }

    SECTION("valid type - rhs")
    {
        variant a;
        variant b = 23;

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("variant::operator==() - basic", "[variant]")
{
    SECTION("int - equal")
    {
        variant a = 23;
        variant b = 23;

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("int - NOT equal")
    {
        variant a = 23;
        variant b = 12;

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }

    SECTION("int - uint8_t")
    {
        variant a = 12;
        variant b = static_cast<uint8_t>(12);

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("double - float")
    {
        variant a = 12.5f;
        variant b = 12.5;

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("float - double")
    {
        variant a = 12.1234;
        variant b = 12.1234f;

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

enum class COLOR
{
    RED,
    GREEN,
    BLUE
};

TEST_CASE("variant::operator==() - enums", "[variant]")
{
    variant a = COLOR::RED;
    variant b = 0;

    CHECK((a == b) == false);
    CHECK((a != b) == true);

    b = COLOR::RED;

    CHECK((a == b) == true);
    CHECK((a != b) == false);

     a = COLOR::BLUE;

    CHECK((a == b) == false);
    CHECK((a != b) == true);
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("variant::operator==() - raw arrays", "[variant]")
{
    SECTION("int - pos.")
    {
        int array[2][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
        int arrays[2][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
        variant a = array;
        variant b = arrays;

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("int - neg.")
    {
        int array[2][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
        int arrays[2][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 0, 5}};
        variant a = array;
        variant b = arrays;

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }

    SECTION("type_with_no_equal_operator")
    {
        type_with_no_equal_operator array[5] = {1, 2, 3, 4, 5};
        type_with_no_equal_operator arrays[5] = {1, 2, 3, 4, 5};
        variant a = array;
        variant b = arrays;

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("type_with_no_equal_operator")
    {
        type_with_no_equal_operator array[5] = {1, 2, 3, 4, 5};
        type_with_no_equal_operator arrays[5] = {1, 2, 3, 0, 5};
        variant a = array;
        variant b = arrays;

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("variant::operator==() - std::string", "[variant]")
{
    SECTION("equal")
    {
        variant a = "text";
        variant b = "text";

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("case sensitive")
    {
        variant a = "Text";
        variant b = "text";

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

struct point
{
    point(int x, int y) : _x(x), _y(y) {}

    point(const point& other) : _x(other._x), _y(other._y) { }

    point(point&& other) : _x(other._x), _y(other._y) { other._x = 0; other._y = 0; }

    bool operator ==(const point& other) const { return (_x == other._x && _y == other._y); }
    int _x;
    int _y;
};

static std::string convert_to_string(const point& p, bool& ok)
{
    ok = true;
    return "[" + std::to_string(p._x) + ", " + std::to_string(p._y) + "]";
}

TEST_CASE("variant::operator==() - custom", "[variant]")
{
    type::register_converter_func(convert_to_string);

    SECTION("equal")
    {
        variant a = point(12, 12);
        variant b = point(12, 12);

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("NOT equal")
    {
        variant a = point(12, 23);
        variant b = point(12, 12);

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }

    SECTION("different types")
    {
        variant a = point(12, 23);
        variant b = type_with_no_equal_operator{12};

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }

    SECTION("compare std::string with point")
    {
        variant a = "[12, 23]";
        variant b = point{12, 23};

        CHECK((a == b) == true);
        CHECK((a != b) == false);

        CHECK((b == a) == true);
        CHECK((b != a) == false);

        CHECK(a.is_type<std::string>()  == true);
        CHECK(b.is_type<point>()        == true);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("variant::operator==() - no build in == operator", "[variant]")
{
    SECTION("no equal operator, same types")
    {
        variant a = type_with_no_equal_operator{12};
        variant b = type_with_no_equal_operator{12};

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("no equal operator, same types")
    {
        variant a = type_with_no_equal_operator{12};
        variant b = type_with_no_equal_operator{23};

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }

     SECTION("no equal operator, different types")
    {
        variant a = other_type_with_no_equal_operator{12};
        variant b = type_with_no_equal_operator{23};

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("variant::operator==() - template type - comparator registered", "[variant]")
{
    SECTION("same types, same content")
    {
        variant a = std::make_tuple(23, std::string("some long long text"));
        variant b = std::make_tuple(23, std::string("some long long text"));

        CHECK((a == b) == false);
        CHECK((a != b) == true);

        type::register_comparators<std::tuple<int, std::string>>();

        CHECK((a == b) == true);
        CHECK((a != b) == false);
    }

    SECTION("same types, different content")
    {
        variant a = std::make_tuple(23, std::string("some long long text"));
        variant b = std::make_tuple(23, std::string("different content"));

        CHECK((a == b) == false);
        CHECK((a != b) == true);
    }

    SECTION("self equal test")
    {
        variant a = std::make_tuple(23, std::string("some long long text"));
       
        CHECK((a == a) == true);
        CHECK((a != a) == false);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("variant::operator==() - nullptr type", "[variant]")
{
    SECTION("nullptr == nullptr")
    {
        variant a = nullptr;
        variant b = nullptr;

        CHECK((a == b) == true);
    }

    SECTION("valid ptr == nullptr")
    {
        int int_obj = 12;
        variant a = &int_obj;
        variant b = nullptr;

        CHECK((a == b) == false);
    }

    SECTION("nullptr == valid ptr")
    {
        int int_obj = 12;
        variant a = nullptr;
        variant b = &int_obj;

        CHECK((a == b) == false);
    }

    SECTION("invalid ptr == nullptr")
    {
        int* int_obj = nullptr;
        variant a = int_obj;
        variant b = nullptr;

        CHECK((a == b) == true);
    }

    SECTION("nullptr == invalid ptr")
    {
        int* int_obj = nullptr;
        variant a = nullptr;
        variant b = int_obj;

        CHECK((a == b) == true);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
