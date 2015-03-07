#include "bioutils.h"
#include <sstream>
#include <ctype.h>

namespace com {
namespace goffersoft {
namespace apps {
namespace bio {
  
const char BioUtils::alphabets[] = { 'a', 't', 'c', 'g', 'n' };
const unsigned BioUtils::num_alphabets = sizeof(alphabets)/sizeof(char);

const char BioUtils::alphabets_compliment[] = { 't', 'a', 'g', 'c', 'n' };

using std::stringstream;

int BioUtils::is_alphabet(char alpha) {
  int i = 0;
  while(i < num_alphabets) {
    if(alphabets[i] == tolower(alpha))
      return i;
    i++;
  }
  return -1;
}

string&
BioUtils::_compliment(string& str1, const string& str, bool reverse) {
  int index;
  char tmp;

  for(int i = 0; i < str.length(); i++) {
    if((index = is_alphabet(str[i])) != -1) {
      tmp = alphabets_compliment[index];
    } else {
      tmp = str[i];
    }
    if(reverse)
      ((char *)(str1.c_str()))[str.length() - i - 1] = tmp;
    else
      ((char *)(str1.c_str()))[i] = tmp;
  }
  return str1;
}

string
BioUtils::compliment(const string& str) {
  string str1 = str;
  return _compliment(str1, str, false);
}

string
BioUtils::reverse_compliment(const string& str) {
  string str1 = str;
  return _compliment(str1, str, true);
}

//In information theory, the Hamming distance between 
//two strings of equal length is the number of positions 
//at which the corresponding symbols are different. 
//In another way, it measures the minimum number of 
//substitutions required to change one string into 
//the other, or the minimum number of errors that could 
//have transformed one string into the other.
unsigned
BioUtils::hamming_distance(const string& str1,
                           const string& str2,
                           unsigned length) {
  int len = min(str1.length(), str2.length());

  if(length > 0 && length < len) {
    len = length;
  }
  int hamming_distance = 0;

  for(int i = 0; i < len; i++)
  {
    if(tolower(str1[i]) != tolower(str2[i]))
      hamming_distance++;
  }

  return hamming_distance;
}

string
BioUtils::skew_graph(const string& str, unsigned length) {
  int numc = 0;
  int numg = 0;
  int i = 0;
  stringstream ss;
  
  int len = str.length();

  if(length > 0 && length < len) {
    len = length;
  }

  while (i < len) {
    if(tolower(str[i]) == 'c') {
      numc++;
    } else if (tolower(str[i]) == 'g') {
      numg++;
    }
    ss << numg - numc << ',';
    i++;
  }
  return ss.str();
}

} //com
} //goffersoft
} //apps
} //bio
