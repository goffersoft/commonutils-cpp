/** 
 **
 ** This file is part of mepgutils.
 **
 ** mpegutils is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** mpegutils is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with mpegutils. If not, see <http://www.gnu.org/licenses/>.
 **
 ** This file descrbes the object class of the mpegutils project.
 ** This class contains code to manipulate lists.
 **/
#ifndef __ASSERT_HELPER__H__
#define __ASSERT_HELPER__H__

#include <stdio.h>
#include <assert.h>

#include <iostream>

namespace com {
namespace goffersoft {
namespace core {

using std::endl;
using std::ostream;
using std::cout;

class AssertHelper {
  private:
    AssertHelper() {}

  public:
    template <typename T>
    static void equals(
             const T& expected,
             const T& actual,
             int line = __LINE__,
             const char* file = __FILE__,
             ostream& os = cout) {
      if (expected != actual) {
        os <<"Test Failed "
           <<file<<" : "<<line
           <<" expected: "<<expected
           <<" actual: "<<actual
           <<endl;
      } else {
        os <<"Test Passed"
           <<endl;
      }
    }

    template <typename T>
    static void not_equals(
             const T& expected,
             const T& actual,
             int line = __LINE__,
             const char* file = __FILE__,
             ostream& os = cout) {
      if (expected == actual) {
        os <<"Test Failed: "
           <<file<<" : "<<line
           <<" expected: "<<expected
           <<" actual: "<<actual
           <<endl;
      } else {
        os <<"Test Passed"
           <<endl;
      }
    }
};

} //com
} //goffersoft
} //core

#endif /* __ASSERT_HELPER__H__ */
