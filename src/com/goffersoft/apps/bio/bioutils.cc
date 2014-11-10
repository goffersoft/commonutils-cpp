#include "bioutils.h"

namespace com {
namespace goffersoft {
namespace apps {
namespace bio {
  
const char BioUtils::alphabets[] = { 'a', 't', 'c', 'g', 'n' };
const unsigned BioUtils::num_alphabets = sizeof(alphabets)/sizeof(char);

const char BioUtils::alphabets_compliment[] = { 't', 'a', 'g', 'c', 'n' };

int BioUtils::is_alphabet(char alpha) {
  int i = 0;
  while(i < num_alphabets) {
    if(alphabets[i] == alpha)
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
  string str1;
  return _compliment(str1, str, false);
}

string
BioUtils::reverse_compliment(const string& str) {
  string str1;
  return _compliment(str1, str, true);
}

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
    if(str1[i] != str2[i])
      hamming_distance++;
  }

  return hamming_distance;
}

} //com
} //goffersoft
} //apps
} //bio
