/** 
 **
 ** This file is part of algs4cc.
 **
 ** algs4cc is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** algs4cc is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with algs4cc. If not, see <http://www.gnu.org/licenses/>.
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
#ifndef __CODECLEAN__
#define __CODECLEAN__

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <memory>

#include "except.h"
#include "utils.h"

namespace com {
namespace goffersoft {
namespace codeclean{

using std::function;
using std::forward;
using std::bind;
using std::vector;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
using std::ostream;
using std::istream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::stringstream;
using std::streambuf;
using std::array;

using com::goffersoft::core::not_implemented_error;

class test {
    public:
        using TestFuncType = function<bool(void)>;
        using IdFuncType = function<uint32_t(void)>;

    private:
        uint32_t id;
        string name;
        TestFuncType test_func;
        
        static const string ws_ts_prefix;
        static const string ws_r_prefix;
        static const array<const char*, 256>& escs;

        static array<const char*, 256>& init_escs() {
            array<const char*, 256>& tmp = 
                        *new array<const char*, 256>();
            tmp['\0'] = "\\0";
            tmp['\a'] = "\\a";
            tmp['\b'] = "\\b";
            tmp['\f'] = "\\f";
            tmp['\n'] = "\\n";
            tmp['\r'] = "\\r";
            tmp['\t'] = "\\t";
            tmp['\v'] = "\\v";

            return tmp;
        }
        
        template<typename T>
        static T* get_raw(const T& t) {
            return nullptr;
        }
        
        template <typename T>
        static void print_msg(const T& expected,
                              const T& actual,
                              ostream& os,
                              const string &msg,
                              bool fail_msg) {
            if(fail_msg) {
                const T* exp = &expected; 
                const T* act = &actual;
                const T* tmp = get_raw(expected);
                if(tmp != nullptr) {
                    exp = tmp;
                    act = get_raw(actual);
                }
                os << ws_ts_prefix << msg << endl
                   << ws_r_prefix
                   << "expected: "<< *exp << endl
                   << ws_r_prefix
                   << "actual  : "<< *act << endl;
                if(tmp != nullptr) {
                    delete exp;
                    delete act;
                }
            } else {
                os << ws_ts_prefix << msg << endl;
            }
        }

        static IdFuncType get_next_id;

    public:
        using decision_func = bool();
        using cap_func = void();
        using mock_func = void();

        static const string& noname;

        test(const string& tname = noname) :
                        test(nullptr, tname) {}

        test(const TestFuncType& tf,
             const string& tname = noname) {
            name = tname;
            id = get_next_id();
            test_func = tf; 
            if(&tname == &noname) {
                stringstream ss;
                ss << "test-" << id;
                name = ss.str();
            } else {
                name = tname;
            }
        }

        const TestFuncType& get_test() {
            if(test_func == nullptr) {
                test_func = bind(&test::run, this);
            }
            return test_func;
        }

        uint32_t get_id() {
            return id;
        }

        const string& get_name() {
            return name;
        }

        virtual test& clone() const {
            throw not_implemented_error("must override in derived class");
        }

        virtual bool run() {
            throw not_implemented_error("must override in derived class");
        }

        static bool ccassert(bool val,
                             const string& msg = "test failed",
                             ostream& os = cout,
                             const string& fail_msg = "test failed",
                             const string& pass_msg = "test_passed") {
            if(!val) {
                os << ws_ts_prefix << fail_msg << endl; 
                return false;
            } else {
                os << ws_ts_prefix << pass_msg << endl; 
                return true;
            }
        }

        static bool ccassert(const function<decision_func>& dfunc,
                             ostream& os = cout,
                             const string& fail_msg = "test failed",
                             const string& pass_msg = "test_passed") {
            if(!dfunc()) {
                os << ws_ts_prefix << fail_msg << endl; 
                return false;
            } else {
                os << ws_ts_prefix << pass_msg << endl; 
                return true;
            }
        }

        template <typename T>
        static bool ccassert_equals(
                 const T& expected,
                 const T& actual,
                 ostream& os = cout,
                 const string& fail_msg = "test failed",
                 const string& pass_msg = "test_passed") {
            if (expected != actual) {
                print_msg(expected,
                          actual,
                          os, fail_msg, true);
                return false;
            } else {
                print_msg(expected,
                          actual,
                          os, pass_msg, false);
                return true;
            }
        }

        template <typename T>
        static bool ccassert_not_equals(
                 const T& expected,
                 const T& actual,
                 ostream& os = cout,
                 const string& fail_msg = "test failed",
                 const string& pass_msg = "test_passed") {
            if (expected == actual) {
                print_msg(expected,
                          actual,
                          os, fail_msg, true);
                return false;
            } else {
                print_msg(expected,
                          actual,
                          os, pass_msg, false);
                return true;
            }
        }
       
        static void capture_ostream(ostream& os,
                                    ostream& oscap,
                                    const function<cap_func>& cfunc) {
            // save os's buffer
            streambuf *sbuf = os.rdbuf();

            // redirect os to the oscap's buffer
            os.rdbuf(oscap.rdbuf());

            //call func to execute ostream related cmds
            cfunc();

            // redirect os to its old self
            os.rdbuf(sbuf);
        }

        static string capture_any(ostream& os, const function<cap_func>& cfunc) {
            stringstream ostr;
            capture_ostream(os, ostr, cfunc);
            return ostr.str();
        }

        static string capture_stdout(const function<cap_func>& cfunc) {
            stringstream ostr;
            capture_ostream(cout, ostr, cfunc);
            return ostr.str();
        }

        static string capture_stderr(const function<cap_func>& cfunc) {
            stringstream ostr;
            capture_ostream(cerr, ostr, cfunc);
            return ostr.str();
        }

        static void mock_istream(istream& is,
                                 istream& mockis,
                                 const function<mock_func>& mfunc) {
            // save is's buffer
            streambuf *sbuf = is.rdbuf();

            // redirect is to the ismock's buffer
            is.rdbuf(mockis.rdbuf());

            //call func to execute istream related cmds
            mfunc();

            // redirect is to its old self
            is.rdbuf(sbuf);
        }

        static void mock_stdin(istream& mockis,
                                 const function<mock_func>& mfunc) {
            mock_istream(cin, mockis, mfunc);
        }
};

class testcase {
    public :
        using IdFuncType = function<uint32_t(void)>;
    private :
        using TPtrType = unique_ptr<test>;
        using VecType = vector<TPtrType>;
        using VecPtrType = shared_ptr<VecType>;

        static const string ws_tc_prefix;
        static const string ws_t_prefix;
        uint32_t id;
        string name;
        VecPtrType list_of_tests;
        static const string& noname;
        uint32_t num_tests_passed = 0;
        uint32_t num_tests_failed = 0;
        uint32_t num_tests = 0;

        static IdFuncType get_next_id;

    public :
        testcase(const string& tcname = noname) {
            list_of_tests = VecPtrType(new VecType());
            id = get_next_id();
            if(&tcname == &noname) {
                stringstream ss;
                ss << "testcase-" << id;
                name = ss.str();
            } else {
                name = tcname;
            }
        }

        void add_test(const test::TestFuncType& tf,
                      const string& tname = test::noname) {
            list_of_tests->push_back(
                  TPtrType(new test(tf, tname))
                       );
        }

        void add_test(const test& t) {
            list_of_tests->push_back(
                  TPtrType(&t.clone())
                       );
        }

        virtual void run(ostream& os = cout) {
            num_tests = list_of_tests->size();
            os << ws_tc_prefix
               << "Running Test Case #"
               << id << "," << name << endl;
            for(auto& t : *list_of_tests) {
                os << ws_t_prefix
                   << "Running Test #"
                   << t->get_id() << ","
                   << t->get_name() << endl;
                bool status = ((t->get_test())());
                if(status) {
                    num_tests_passed++;
                } else {
                    num_tests_failed++;
                }
            }
        }
        
        uint32_t get_num_tests_passed() {
            return num_tests_passed;
        }

        uint32_t get_num_tests_failed() {
            return num_tests_failed;
        }

        uint32_t get_num_tests() {
            return num_tests;
        }

        void print_report(ostream& os = cout) {
            os << ws_tc_prefix 
               << "TestCase(" << id << ',' << name << ") : " << endl
               << ws_t_prefix << "Report(Total/Pass/Fail) : ("
               << num_tests << "/"
               << num_tests_passed << "/"
               << num_tests_failed << ")" << endl;
        }
};


class testsuite {
    public :
        using IdFuncType = function<uint32_t(void)>;

    private :
        using TcPtrType = unique_ptr<testcase>;
        using VecType = vector<TcPtrType>;
        using VecPtrType = shared_ptr<VecType>;

        uint32_t id;
        string name;
        VecPtrType list_of_testcases;
        uint32_t num_tests_passed = 0;
        uint32_t num_tests_failed = 0;
        uint32_t num_tests = 0;

        static const string ws_ts_prefix;
        static const string ws_tc_prefix;
        static const string& noname;
        static IdFuncType get_next_id;

    public :
        testsuite(const string& tsname = noname) {
            list_of_testcases = VecPtrType(new VecType());
            id = get_next_id();
            if(&tsname == &noname) {
                stringstream ss;
                ss << "testsuite-" << id;
                name = ss.str();
            } else {
                name = tsname;
            }
        }

        void add_testcase(const testcase& tc) {
            list_of_testcases->push_back(
                   TcPtrType(new testcase(tc))
                   );
        }

        virtual void run(ostream& os = cout) {
            os << ws_ts_prefix
               << "Running Test Suite #"
               << id << "," << name << endl;
            for(auto& tc : *list_of_testcases) {
                tc->run(os);
                num_tests_passed += tc->get_num_tests_passed();
                num_tests_failed += tc->get_num_tests_failed();
                num_tests += tc->get_num_tests();
            }
        }

        uint32_t get_num_tests_passed() {
            return num_tests_passed;
        }

        uint32_t get_num_tests_failed() {
            return num_tests_failed;
        }

        uint32_t get_num_tests() {
            return num_tests;
        }
        void print_report(ostream& os = cout) {
            os << ws_ts_prefix 
               << "TestSuite(" << id << ',' << name << ") : " << endl
               << ws_tc_prefix
               << "Report(Total/Pass/Fail) : ("
               << num_tests << "/"
               << num_tests_passed << "/"
               << num_tests_failed << ")" << endl;
            for(auto& ts : *list_of_testcases) {
                ts->print_report();
            }
        }
};

class codeclean {
    private :
        static const string ws_prefix;
        using TsPtrType = unique_ptr<testsuite>;
        using VecType = vector<TsPtrType>;
        using VecPtrType = shared_ptr<VecType>;

        VecPtrType list_of_testsuites;
        string name;
        uint32_t num_tests_passed = 0;
        uint32_t num_tests_failed = 0;
        uint32_t num_tests = 0;

    public :
        codeclean() {
            list_of_testsuites = VecPtrType(new VecType());
        }

        void add_testsuite(const testsuite& ts) {
            list_of_testsuites->push_back(
                TsPtrType(new testsuite(ts))
                      );
        }

        virtual void run(ostream& os = cout) {
            os << ws_prefix << "Running Tests" << endl;
            for(auto& ts : *list_of_testsuites) {
                ts->run(os);
                num_tests_passed += ts->get_num_tests_passed();
                num_tests_failed += ts->get_num_tests_failed();
                num_tests += ts->get_num_tests();
            }
        }

        void print_report(ostream& os = cout) {
            os << ws_prefix 
               << "Test Report(Total/Pass/Fail) : ("
               << num_tests << "/"
               << num_tests_passed << "/"
               << num_tests_failed << ")" << endl;
            for(auto& ts : *list_of_testsuites) {
                ts->print_report();
            }
        }
};

template<>
string* test::get_raw<string>(const string& oldstr);

} //com
} //goffersoft
} //codeclean

#endif /* __CODECLEAN__ */
