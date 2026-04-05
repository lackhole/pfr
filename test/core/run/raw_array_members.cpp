// Copyright (c) 2016-2026 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/pfr/core.hpp>
#include <boost/core/lightweight_test.hpp>

#include <cstddef>
#include <type_traits>

namespace {

struct array_first {
    int values[2];
    int tail;
};

struct array_last {
    int head;
    int values[2];
};

struct two_arrays {
    int first[2];
    short second[3];
};

} // namespace

int main() {
    static_assert(boost::pfr::tuple_size_v<array_first> == 2, "");
    static_assert(boost::pfr::tuple_size_v<array_last> == 2, "");
    static_assert(boost::pfr::tuple_size_v<two_arrays> == 2, "");

    array_first first{{1, 2}, 3};
    static_assert(std::is_same<decltype(boost::pfr::get<0>(first)), int (&)[2]>::value, "");
    static_assert(std::is_same<decltype(boost::pfr::get<1>(first)), int&>::value, "");
    BOOST_TEST_EQ(boost::pfr::get<0>(first)[0], 1);
    BOOST_TEST_EQ(boost::pfr::get<0>(first)[1], 2);
    BOOST_TEST_EQ(boost::pfr::get<1>(first), 3);

    array_last last{4, {5, 6}};
    static_assert(std::is_same<decltype(boost::pfr::get<0>(last)), int&>::value, "");
    static_assert(std::is_same<decltype(boost::pfr::get<1>(last)), int (&)[2]>::value, "");
    BOOST_TEST_EQ(boost::pfr::get<0>(last), 4);
    BOOST_TEST_EQ(boost::pfr::get<1>(last)[0], 5);
    BOOST_TEST_EQ(boost::pfr::get<1>(last)[1], 6);

    two_arrays arrays{{7, 8}, {9, 10, 11}};
    std::size_t fields_seen = 0;
    boost::pfr::for_each_field(arrays, [&fields_seen](const auto& field) {
        ++fields_seen;
        static_cast<void>(field);
    });
    BOOST_TEST_EQ(fields_seen, 2u);

    return boost::report_errors();
}
