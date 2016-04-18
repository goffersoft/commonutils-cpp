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
 ** This file descrbes the utils class of the experimental project.
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

using std::ostream;
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

        template <typename T>
        static ostream& print_data(ostream& os, const T& t) {
            return os << t;
        }

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
        
        // -1 ==> lns < rhs 
        // 1 ==> lns > rhs 
        // 0 ==> lns == rhs 
        // -2 if lhs or rhs is nan ==> isnan()
        // if lhs or rhs is inf ==> isinf()
        // -1 if lhs is -inf
        // 1 if lhs is -inf
        // 1 if rhs is -inf
        // -1 if rhs is inf
        template<typename T>
        static int cmp_xfld(const T& lhs,
                            const T& rhs,
                            const T epsilon = numeric_limits<T>::epsilon()) {
            static_assert(is_floating_point<T>::value,
                          "T must be one of float, double or long double");

            if( isnan(lhs) && isnan(rhs) ) {
                return 0; 
            } else if( isinf(lhs) && isinf(rhs) ) {
                if(lhs == rhs) {
                    return 0;
                } else if (lhs < rhs) {
                    return -1;
                } else if (lhs > rhs) {
                    return 1;
                }
            } else if(isnan(lhs) || isnan(rhs)) {
                return -2;
            } else {
                if(isinf(lhs)) {
                    if(lhs == std::numeric_limits<T>::infinity()) {
                        return 1;
                    } else { // -inf
                        return -1;
                    }
                }
                if(isinf(rhs)) {
                    if(rhs == std::numeric_limits<T>::infinity()) {
                        return -1;
                    } else { // -inf
                        return 1;
                    }
                }
            }

            const T diff = (lhs - rhs);
            if((diff >= -epsilon) && (diff <= epsilon)) {
                return 0;
            } else if (diff < 0) {
                return -1;
            } else {
                return 1;
            }
        }

        template<typename T>
        static bool equal_xfld(const T& lhs,
                               const T& rhs,
                               const T epsilon = numeric_limits<T>::epsilon()) {
            return (cmp_xfld(lhs, rhs, epsilon) == 0)?true:false;
        }

        template<typename T>
        static bool cmp_equal(const T& lhs,
                              const T& rhs,
                              const T epsilon = numeric_limits<T>::epsilon()) {
            return (lhs == rhs);
        }

        // -1 ==> lns < rhs 
        // 1 ==> lns > rhs 
        // 0 ==> lns == rhs 
        template<typename T>
        static int cmp(const T& lhs,
                       const T& rhs,
                       const T epsilon = numeric_limits<T>::epsilon()) {
            if(lhs == rhs) {
                return 0;
            } else if(lhs < rhs) {
                return -1;
            } else {
                return 1;
            }
        }

        template<typename T1, typename T2>
        static int32_t cmp(const T1& this_first,
                           const T2& this_second,
                           const T1& that_first,
                           const T2& that_second) {
            int32_t cmp_first = cmp(this_first, that_first);
    
            if(cmp_first == 0) {
                int32_t cmp_second = cmp(this_second, that_second);

                if(cmp_second == 0) {
                    return 0;
                } else if(cmp_second < 0) {
                    return -1;
                } else {
                    return 1;
                }
            } else if(cmp_first < 0) {
                return -1;
            } else {
                return 1;
            }
        }
};
template <>
ostream& utils::print_data<uint8_t>(ostream& os,
                                    const uint8_t& t);

template <>
ostream& utils::print_data<int8_t>(ostream& os,
                                    const int8_t& t);

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

template<>
int utils::cmp<float> (
        const float& lhs,
        const float& rhs,
        const float epsilon);

template<>
int utils::cmp<double> (
        const double& lhs,
        const double& rhs,
        const double epsilon);

template<>
int utils::cmp<long double> (
        const long double& lhs,
        const long double& rhs,
        const long double epsilonn);

} //com
} //goffersoft
} //core

#endif /* __UTILS_H__ */
