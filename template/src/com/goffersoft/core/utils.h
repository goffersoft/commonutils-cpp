/** 
 **
 ** This file is part of template.
 **
 ** template is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** template is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with template. If not, see <http://www.gnu.org/licenses/>.
 **
 ** This file descrbes the utils class of the template project.
 ** This class cannot be instantiated. Has a bunch of static
 ** helper functions
 **/
#ifndef __UTILS_H__
#define __UTILS_H__

#include<cctype>
#include<cmath>
#include<limits>
#include<type_traits>
#include<functional>
#include<memory>
#include<iostream>

namespace com {
namespace goffersoft {
namespace core {

using std::shared_ptr;
using std::is_integral;
using std::is_unsigned;
using std::is_floating_point;
using std::is_same;
using std::function;
using std::numeric_limits;
using std::isnan;
using std::isinf;

class utils {
    public :
        utils() = delete;

        static bool strequals_igncase(unsigned char a,
                                      unsigned char b) {
            return tolower(a) == tolower(b);
        }

        template<typename T>
        static function<T()> uniqid(T init_val) {
            static_assert(!is_same<T, bool>::value,
                          "T must be one of uint[64,32,16,8]_t");
            static_assert(is_unsigned<T>::value,
                          "T must be one of uint[64,32,16,8]_t");
            static_assert(is_integral<T>::value,
                          "T must be one of uint[64,32,16,8]_t");
            
            shared_ptr<T> next_val(new T(init_val));

            return [init_val, next_val]() {
                       T tmp = *next_val;
                       (*next_val)++;
                       if( (*next_val) == 0) {
                           *next_val = init_val;
                       }
                       return tmp;
                   };
        }

        template<typename T>
        static bool equal_xfld(const T& lhs,
                               const T& rhs,
                               const T epsilon = numeric_limits<T>::epsilon()) {
            static_assert(is_floating_point<T>::value,
                          "T must be one of float, double or long double");
            if( isnan(lhs) && isnan(rhs) )
                return true; 
            else if( isinf(lhs) && isinf(rhs) )
                return true;
            else if(isinf(lhs) || isinf(rhs) ||
                    isnan(lhs) || isnan(rhs))
                return false;

            const T diff = (lhs - rhs);

            return ((diff >= -epsilon) && (diff <= epsilon));
        }

        template<typename T>
        static bool cmp_equal(const T& lhs,
                              const T& rhs,
                              const T epsilon = numeric_limits<T>::epsilon()) {
            return (lhs == rhs);
        }

};


template<>
bool utils::cmp_equal<float> (
        const float& lhs,
        const float& rhs,
        const float epsilon);

template<>
bool utils::cmp_equal<double> (
        const double& lhs,
        const double& rhs,
        const double epsilon);

template<>
bool utils::cmp_equal<long double> (
        const long double& lhs,
        const long double& rhs,
        const long double epsilonn);

} //com
} //goffersoft
} //core

#endif /* __UTILS_H__ */
