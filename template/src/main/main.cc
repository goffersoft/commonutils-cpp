/** 
 **
 ** This is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This software is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this software. If not, see <http://www.gnu.org/licenses/>.
 **
 **/
#include <string>

#include "main.h"
#include "utils.h"

using com::goffersoft::core::utils;
using std::string;
using std::begin;
using std::end;
using std::equal;

int main(int argc, const char **argv) {
    if(argc > 1) {
       string s(argv[1]);
       if(equal(s.begin(), s.end(), begin("test"),
                 utils::strequals_igncase)) {
           return test_main(argc, argv);
       }
    }

    return 0;
}
