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
    static unsigned hamming_distance(const string& str1,
                            const string& str2,
                            unsigned length = 0);

  private :
    static int is_alphabet(char alpha);
    static string& _compliment(string& str1, const string& str, bool reverse);
};

} //com
} //goffersoft
} //apps
} //bio

#endif /* __BIO_UTILS_H__ */
