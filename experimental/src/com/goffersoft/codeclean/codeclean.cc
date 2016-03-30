/** 
 **
 ** This file is part of experimental.
 **
 ** experimental is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** experimental is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with experimental. If not, see <http://www.gnu.org/licenses/>.
 **
 ** this file describes the classes that are used for implementing a
 ** unit test framework
 **      1) a test is made of a vector of testsuite classes
 **            a) member function to add a testsuite
 **
 **      2) each testsuite class are made up of a vector of
 **         testcase classes.
 **            a) member function to add a testcase
 **
 **      3) each testcase class is made of a vector of testcases
 **            a) member functions to add a test
 **
 **      4) two ways of creating a test class
 **           a) public derivation from base test class
 **                 1) must override clone
 **                 2) must override run function (code goes here)
 **           b) create a function object(std::function, std::bind)
 **              of type bool(boid)
 ** 
 **/
#include "codeclean.h"

using std::string;
using std::array;
using std::function;

using com::goffersoft::codeclean::codeclean;
using com::goffersoft::codeclean::testsuite;
using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;
using com::goffersoft::core::utils;

testsuite::id_func_type testsuite::get_next_id = utils::uniqid((uint32_t)1);
testcase::id_func_type testcase::get_next_id = utils::uniqid((uint32_t)1);
test::id_func_type test::get_next_id = utils::uniqid((uint32_t)1);

const string&  test::noname = "t-noname";
const string&  testcase::noname = "tc-noname";
const string&  testsuite::noname = "ts-noname";


const string codeclean::ws_prefix = string(0, ' ');
const string testsuite::ws_ts_prefix = string(4, ' ');
const string testcase::ws_tc_prefix = string(8, ' ');
const string testcase::ws_t_prefix = string(12, ' ');
const string test::ws_ts_prefix = string(16, ' ');
const string test::ws_r_prefix = string(20, ' ');
        
const array<const char*, 256>&
test::escs = test::init_escs();

template<>
string* test::get_raw<string>(const string& oldstr) {
    string *newstr = new string;
    for(auto c : oldstr) {
        if(escs[c] != nullptr) {
            *newstr += escs[c];
        } else {
            *newstr += c;
        }
    }
    return newstr;
}
