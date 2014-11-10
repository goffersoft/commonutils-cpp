/**
 **
 ** This file is part of goffersoft.
 **
 ** goffersoft is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** goffersoft is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with goffersoft. If not, see <http://www.gnu.org/licenses/>.
 ** 
 ** This file contains test code for the bioutils.h class
 **/
#include "bioutils.h"
#include "iostream"

using std::endl;
using std::cout;
using com::goffersoft::apps::bio::BioUtils;

int test_bioutils_main (int argc, char **argv) {
  cout << "reverse compliment of CTAATGT is : " 
       << BioUtils::reverse_compliment("CTAATGT") << endl;
  
  cout << "hamming distance between  " << endl
       << "CAGAAAGGAAGGTCCCCATACACCGACGCACCAGTTTA and" << endl
       << "CACGCCGTATGCATAAACGAGCCGCACGAACCAGAGAG is" << endl
       << BioUtils::hamming_distance(
          "CAGAAAGGAAGGTCCCCATACACCGACGCACCAGTTTA",
          "CACGCCGTATGCATAAACGAGCCGCACGAACCAGAGAG", 0) <<endl;

  return 0;
}
