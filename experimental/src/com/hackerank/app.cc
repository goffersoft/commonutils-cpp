#include "ex1.h"
#include "ex2.h"
#include "ex3.h"

void D::check(int new_val)
{
       update_val(new_val);
       cout<<"Value = "<<val<<endl<<"A's func called "<<callA<<" times "<<endl<<"B's func called "<<callB<<" times "<<endl<<"C's func called "<<callC<<" times"<<endl;
}


tag& tag::root_tag = *new tag("root", nullptr);
const string& tag::bad_key = string("Not Found!");
const tag& tag::tag_not_found = tag("Bad Tag", tag::root_tag);
const tag::attr_type& tag::attr_not_found =
             tag::attr_type(new string("Bad Key"), new string("Bad Value"));

vector<token<char> > src_tokens = {
  pair_token<char>('<', '>', 1),
  pair_token<char>('>', '<', 2),
  binary_token<char>('='),
  unary_token<char>('/') 
};

vector<token<char> > query_tokens = {
  binary_token<char>('.'),
  binary_token<char>('~'),
};

bool is_token(char c, vector<token<char> > tarray) {
  for(token<char> t: tarray) {
    if(t.get_token() == c)
      return true;
  }
  return false;
}

bool is_query_token(char c) {
  return is_token(c, query_tokens);
}

bool  is_src_token(char c) {
  return is_token(c, src_tokens);
}

void ex4() {
  string input_str =  {
    "4 3\r\n"
    //"1 3\r\n"
    "<tag1 value = \"HelloWorld\">\r\n"
    "<tag2 name = \"Name1\">\r\n"
    "</tag2>\r\n"
    "</tag1>\r\n"
    "tag1.tag2~name\r\n"
    "tag1~name\r\n"
    "tag1~value\r\n"
  };
  try {
    istringstream iss1(input_str);
    hrml_parser parser = hrml_parser(iss1, cout);
    parser.parse();
  } catch (exception* e) {
    cout << e->what() << endl;
    return;
  }
/*
  string input[] =  {
    "4 3",
    "<tag1 value = \"HelloWorld\">",
    "<tag2 name = \"Name1\">",
    "</tag2>",
    "</tag1>",
    "tag1.tag2~name",
    "tag1~name",
    "tag1~value",
  };
  int num_src_lines;
  int num_query_lines;
  istringstream iss(input[0]);
  iss >> num_src_lines  >> num_query_lines;
  string* src_lines = new string[num_src_lines];
  string* query_lines = new string[num_query_lines];
  stack<char> tokens = stack<char>();
  stack<string*> values = stack<string*>();
  stack<attr<string*, void*> > objects = stack<attr<string*, void*> >();

  cout << num_src_lines << " " << num_query_lines << endl;

  int index;
  int start_index = -1;
  int stop_index; 
  string *s;
  for(int i = 1; i <= num_src_lines; i++) {
    index = 0;
    start_index = -1;
    for(char& c : input[i]) {
      if(isspace(c) || c == '"') {
        if(start_index >= 0) {
          s = new string();
          *s = input[i].substr(start_index,
                               stop_index - start_index + 1);
          cout << "[" << i  << "]" << " = "
               << input[i].substr(start_index,
                                  stop_index - start_index + 1) << endl;
          start_index = -1;
          values.push(s);
        }
      } else if(is_src_token(c)) {
        if(start_index >= 0) {
          s = new string();
          *s = input[i].substr(start_index,
                               stop_index - start_index + 1);
          cout << "[" << i  << "]" << " = "
               << input[i].substr(start_index,
                                  stop_index - start_index + 1) << endl;
          start_index = -1;
          values.push(s);
        }
        tokens.push(c);
        cout << "[" << i  << "]" << " = " << c  << endl;
      } else {
        if(start_index < 0)  
          start_index = index;
        stop_index = index;
      }
      index++;
    }
    if(start_index >= 0) {
     s = new string();
     *s = input[i].substr(start_index,
                          stop_index - start_index + 1);
      cout << "[" << i  << "]" << " = "
           << input[i].substr(start_index,
                              stop_index - start_index + 1) << endl;
      start_index = -1;
      values.push(s);
    }
  }
  while(!tokens.empty()) {
    cout << tokens.top() << " ";
    tokens.pop();
  }
  cout << endl;

  while(!values.empty()) {
    string *s = values.top();
    cout << *s << " ";
    values.pop();
    delete s;
  }
  cout << endl;

  for(int i = num_src_lines+1; i <= sizeof(input)/sizeof(string); i++) {
    index = 0;
    start_index = -1;
    for(char& c : input[i]) {
      if(isspace(c) || c == '"') {
        if(start_index >= 0) {
          s = new string();
          *s = input[i].substr(start_index,
                               stop_index - start_index + 1);
          cout << "[" << i  << "]" << " = "
               << input[i].substr(start_index,
                                  stop_index - start_index + 1) << endl;
          start_index = -1;
          values.push(s);
        }
      } else if(is_query_token(c)) {
        if(start_index >= 0) {
          s = new string();
          *s = input[i].substr(start_index,
                               stop_index - start_index + 1);
          cout << "[" << i  << "]" << " = "
               << input[i].substr(start_index,
                                  stop_index - start_index + 1) << endl;
          start_index = -1;
          values.push(s);
        }
        cout << "[" << i  << "]" << " = " << c << endl;
        tokens.push(c);
      } else {
        if(start_index < 0)  
          start_index = index;
        stop_index = index;
      }
      index++;
    }
    if(start_index >= 0) {
      s = new string();
      *s = input[i].substr(start_index,
                           stop_index - start_index + 1);
      cout << "[" << i  << "]" << " = "
           << input[i].substr(start_index,
                              stop_index - start_index + 1) << endl;
      start_index = -1;
      values.push(s);
    }
  }

  while(!tokens.empty()) {
    cout << tokens.top() << " ";
    tokens.pop();
  }
  cout << endl;

  while(!values.empty()) {
    string *s = values.top();
    cout << *s << " ";
    values.pop();
    delete s;
  }
  cout << endl;

  //tag t = tag("tag1");

  delete[] src_lines;
  delete[] query_lines;
*/
}

void ex2() {
  sparse_bitmap bitmap = sparse_bitmap();
  int S = 1;
  int P = 1;
  int Q = 1;
  int N = 3;

  cin >> N >> S >> P >> Q;

  int prev_val = S % 0x80000000;
  bitmap.set_bit(prev_val);
  cout << prev_val << endl;
  for(int i = 1; i < N; i++) {
    //prev_val = (prev_val*P+Q) % 0x80000000;
    prev_val = (prev_val*P+Q) % 0x80000000;
    bitmap.set_bit(prev_val);
    //cout << prev_val << endl;
  }
  cout << (bitmap.num_bits_set()) << endl;
  //bitmap.print_map();
}

void ex1() {
  D d;
  int new_val;
  cin>>new_val;
  d.check(new_val);
}

void ex3() {
   unordered_map<char, int> letter_counts {{'a', 27}, {'b', 3}, {'c', 1}};
   unordered_map<int, vector<int> > bitmap;
 
    std::cout << "initially:\n";
    for (const auto &pair : letter_counts) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
 
    letter_counts['b'] = 42;  // update an existing value
 
    letter_counts['x'] = 9;  // insert a new value
    
    bitmap[2] = vector<int>(1);  // insert a new value

     cout << bitmap[2][0] << endl;
     cout << (bitmap.find(3) == bitmap.end()) << endl;
 
    std::cout << "after modifications:\n";
    for (const auto &pair : letter_counts) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
}

int hackerank_main(int argc, const char **argv)
{
   //ex1();
   //ex2();
   //ex3();
   ex4();
   return 0;
}
