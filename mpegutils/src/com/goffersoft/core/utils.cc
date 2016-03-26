/** 
 **
 ** This file is part of mpegutils.
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
 ** This file descrbes the utils class of the mpegutils project.
 ** This class cannot be instantiated. Has a bunch of static
 ** helper functions
 ** 
 **/

#include "utils.h"

using com::goffersoft::core::utils;

template<>
bool utils::cmp_equal<float> (
        const float& lhs,
        const float& rhs,
        const float epsilon) {
    return equal_xfld(lhs, rhs, epsilon);
}

template<>
bool utils::cmp_equal<double> (
        const double& lhs,
        const double& rhs,
        const double epsilon) {
    return equal_xfld(lhs, rhs, epsilon);
}

template<>
bool utils::cmp_equal<long double> (
        const long double& lhs,
        const long double& rhs,
        const long double epsilon) {
    return equal_xfld(lhs, rhs, epsilon);
}
