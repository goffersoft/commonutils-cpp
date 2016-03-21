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
#include "codeclean.h"


extern int test_object_main(int argc, char **argv);
extern int test_bioutils_main(int argc, char **argv);

using com::goffersoft::codeclean::codeclean;

int test_main(int argc, const char **argv) {
    codeclean tests;
    tests.run();
    tests.print_report();

    test_object_main(0, NULL);
    test_bioutils_main(0, NULL);

    return 0;
}
