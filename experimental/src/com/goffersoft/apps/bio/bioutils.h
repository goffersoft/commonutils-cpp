/** 
 **
 ** This file is part of goffersoft bioinformatics package.
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
 ** along with goffersoft bioinformatics package. 
 ** If not, see <http://www.gnu.org/licenses/>.
 **
 **/

#ifndef __BIO_UTILS_H__
#define __BIO_UTILS_H__

#include <algorithm>
#include <string>

namespace com {
namespace goffersoft {
namespace apps {
namespace bio {


using std::min;
using std::string;

class BioUtils {
  public :
    static const char alphabets[5]; //{ 'a', 't', 'c', 'g', 'n' };
    static const unsigned num_alphabets;
    static const char alphabets_compliment[5]; //{ 't', 'a', 'g', 'c', 'n' };

    static string reverse_compliment(const string& str);
    static string compliment(const string& str);

    //In information theory, the Hamming distance between 
    //two strings of equal length is the number of positions 
    //at which the corresponding symbols are different. 
    //In another way, it measures the minimum number of 
    //substitutions required to change one string into 
    //the other, or the minimum number of errors that could 
    //have transformed one string into the other.
    static unsigned hamming_distance(const string& str1,
                            const string& str2,
                            unsigned length = 0);
    static string skew_graph(const string& str, unsigned length = 0);

  private :
    static int is_alphabet(char alpha);
    static string& _compliment(string& str1, const string& str, bool reverse);
};

} //com
} //goffersoft
} //apps
} //bio

#endif /* __BIO_UTILS_H__ */
