#include <iostream>
#include <sstream>
#include<unordered_map>
#include <stack>
using namespace std;

class hrml_parser_exception : public exception {
  private:
    const string& reason;

  public:
    hrml_parser_exception(const string& r) : reason(r) {}
    
    virtual const char* what() const throw() {
      return reason.c_str();
    }
};

template<typename T>
class token {
  private:
    T tok;

  protected:
    token(const T& t) { tok = t; }

  public:
    const char get_token() const { return tok; }
    virtual const T& get_pair() const { return tok; }
    virtual bool is_unary() const { return false; };
    virtual bool is_binary() const { return false; };
    virtual bool is_pair() const { return false; };
};

template<typename T>
class unary_token : public token<T> {
  public:
    unary_token(const T& tok) : token<T>(tok) { }
    bool is_unary() const { return true; }
};

template<typename T>
class binary_token : public token<T> {
  public:
    binary_token(const T& tok) : token<T>(tok) { }
    bool is_binary() const { return true; }
};

template<typename T>
class pair_token : public token<T> {
  private:
    const T& pair;
    int order;

  public:
    pair_token(const T& tok,
               const T& pair,
               int order) : token<T>(tok),pair(pair) {
      this->order = order;
    }
    bool is_pair() const { return true; }
    const T& get_pair() const { return pair; }
    int get_order() const { return order; } 
};

template <typename K, typename V>
class attr {
  private: 
    K key;
    V value;
   
  public: 
    attr(const K& key, const V& value) {
        this->key = key;
        this->value = value;
    }
    
    const K& get_key() const { return key; }
    const V& get_value() const { return value; }
};

class tag {
  public:
    typedef attr<string*, string*> attr_type;
    typedef unordered_map<string, attr_type*> attr_map_type;
    static tag& root_tag;
    static const string& bad_key;
    static const tag& tag_not_found;
    static const attr_type& attr_not_found;

  private:    
    const string name;
    attr_map_type hashmap = attr_map_type();

    tag* parent;

    tag(const string& n, tag* p) : name(n), parent(p) {
    }

  public:
    tag(const string& n, tag& p) : name(n), parent(&p) {
    }

    void add_attr(string& key, attr_type& value) {
      hashmap[key] = &value;
    }

    const string& get_attr_value(string& name) {
      const attr_type& a = get_attr(name);
      
      if(&a == &attr_not_found)
        return bad_key;

      return *(a.get_value());
    }

    const attr_type& get_attr(string& name) {
      auto it = hashmap.find(name);

      if(it == hashmap.end())
        return attr_not_found;

      attr_type* a = (*it).second;

      return *a;
    }

    const string& get_name() {
      return name;
    }

    tag& get_parent() {
      if(parent == nullptr) return root_tag;
      return *parent;
    }

    attr_map_type& get_attr_list() {
      return hashmap;
    }
};

class hrml_parser {

  private:
    int num_src_lines = 0;
    int num_query_lines = 0;
    istream& is;
    ostream& os;
    stack<token<char>* > tokens = stack<token<char>* >();
    stack<string*> values = stack<string*>();
    unordered_map<string, tag*> objectmap;

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

    static bool is_token(char c, vector<token<char> >& tarray, token<char>*& tok) {
      for(uint32_t i = 0; i < tarray.size(); i++) {
        if(tarray[i].get_token() == c) {
          tok = &tarray[i];
          //cout << "?*" << tok->get_token() << " "; 
          return true;
        }
      }
      return false;
    }

    tag* get_object(string& objname) {
      auto it = objectmap.find(objname);
      if(it == objectmap.end())
        return nullptr;

      return (*it).second;
    }
   
    void clear_tokens_stack() {
      while(!tokens.empty()) {
        tokens.pop();
      }
    }

    void clear_values_stack() {
      string *s;
      while(!values.empty()) {
        s = values.top();
        delete s;
        values.pop();
      }
    }

    bool is_query_token(char c, token<char>*& tok) {
      return is_token(c, query_tokens, tok);
    }

    bool  is_src_token(char c, token<char>*& tok) {
      return is_token(c, src_tokens, tok);
    }

    bool get_next_token_or_value(const string& input, uint32_t& offset,
                                 token<char>*& tok, string*& val,
                                 vector<token<char> >& tarray)
    {
      char c;
      int start_index = -1;
      int stop_index; 
      for(; offset < input.size(); offset++) {
        c = input.at(offset); 
        if(isspace(c) || c == '"') {
          if(start_index >= 0) {
            val = new string();
            *val = input.substr(start_index,
                                   stop_index - start_index + 1);
            tok = nullptr;     
            //cout << "?" << *val << " ";
            return true;
          }
        } else if(is_token(c, tarray, tok)) {
          if(start_index >= 0) {
            val = new string();
            *val = input.substr(start_index,
                                   stop_index - start_index + 1);
            //cout << "?" << *val << " "; 
            tok = nullptr;
            return true; 
          }
          val = nullptr;
          offset++;
          //cout << "?*" << tok->get_token() << " "; 
          return true; 
        } else {
          if(start_index < 0)  
            start_index = offset;
            stop_index = offset;
        }
      }
      if(start_index >= 0) {
        val = new string();
        *val = input.substr(start_index,
                               stop_index - start_index + 1);
        tok = nullptr;     
        //cout << "?" << *val << " ";
        return true;
      }
      return false;
    }

    void parse_line(const string& input,
                    vector<token<char> >& tarray,
                    int linenum,
                    tag*& parent) {
      token<char>* tok = nullptr;
      token<char>* tmp = nullptr;
      string *expstr = new string();
      ostringstream oss = ostringstream(*expstr);
      string* val = nullptr;
      const string* attrval;
      string* k;
      string* v;
      uint32_t offset = 0;
      tag *child;
      tag *thistag;
      tag::attr_type *a;
      //cout << tokens.empty() << " " << values.empty() << endl;

      if(parent == nullptr)
        parent = &tag::root_tag;

      while(get_next_token_or_value(input, offset,
                                     tok, val, tarray)) {
        //cout << endl;
        if(tok != nullptr) {
          switch(tok->get_token()) {
            case '<' :
              tokens.push(tok);
              break;
            case '>' :
              if(tokens.empty()) {
                if(thistag == nullptr) {
                  oss << linenum << " '<' expected before '>'" << endl;
                  //cout << oss.str() << endl;
                  throw new hrml_parser_exception(oss.str());
                }
                //cout << "*" << parent->get_name() << endl;
                parent = thistag;
                //cout << "*" << parent->get_name() << endl;
                //cout << "*" << thistag->get_name() << endl;
                //cout << "*" << thistag->get_parent().get_name() << endl;
                objectmap[thistag->get_name()] = thistag;
              } else {
                tmp = tokens.top();
                if(tmp->get_token() == '/') {
                  k = values.top();
                  thistag = get_object(*k);
                  if(*k != thistag->get_name()) {
                    oss << linenum << " mismatched tags expected "
                        << thistag->get_name() << " got " << *k << endl;
                    //cout << oss.str() << endl;
                    throw new hrml_parser_exception(oss.str());
                  }
                  //cout << thistag->get_name() << endl;
                  //cout << thistag->get_parent().get_name() << endl;
                  thistag = &thistag->get_parent();;
                  parent = &thistag->get_parent();
                  //cout << thistag->get_name() << endl;
                  //cout << thistag->get_parent().get_name() << endl;
                  values.pop();
                  tokens.pop();
                  tokens.pop();
                }
              }
              break;
            case '/' :
              tmp = tokens.top();
              if(tmp->get_token() != '<') {
                oss << linenum << " : expected '<' before '/'" << endl;
                //cout << oss.str() << endl;
                throw new hrml_parser_exception(oss.str());
              }
              tokens.push(tok);
              break;
            case '=' :
              tokens.push(tok);
              break;
            case '~' :
              tokens.push(tok);
              break;
            case '.' :
              tokens.push(tok);
              break;
            default  :
              oss << "internal error : invalid token : '"
                  << tok->get_token() << "'" << endl;
              //cout << oss.str() << endl;
              throw new hrml_parser_exception(oss.str());
          }
          //cout << "*" << tok->get_token() << " "; 
        }
        if(val != nullptr) {
          if (!tokens.empty() &&
              tokens.top()->get_token() == '<') {
              thistag = new tag(*val, *parent);
              delete val;
              tokens.pop();
          } else if (!tokens.empty() &&
                    tokens.top()->get_token() == '=') {
             k = values.top();
             values.pop();
             v = val;
             tokens.pop();
             //cout << *k << *v << endl;
             a = new attr<string*, string*>(k, v);
             thistag->add_attr(*k, *a);
          } else if (!tokens.empty() &&
                    tokens.top()->get_token() == '.') {
             parent = get_object(*values.top());
             values.pop();
             child = get_object(*val);
             tokens.pop();
             if(parent == nullptr || 
                child == nullptr ||
                &child->get_parent() != parent) {
               os << "Not Found!" << endl;
               break;
             }
             values.push(val);
          } else if (!tokens.empty() &&
                    tokens.top()->get_token() == '~') {
             //cout << tokens.empty() << " " << values.empty() << endl;
             parent = get_object(*values.top());
             if(parent == nullptr) {
               os << "Not Found!" << endl; 
               break;
             }
             attrval = &parent->get_attr_value(*val);
             if(*attrval == tag::bad_key) {
               os << "Not Found!" << endl; 
               break;
             } else {
               os << *attrval << endl; 
               break;
             }
          } else {
             values.push(val);
          }
          //cout << *val << " "; 
        }
        tok = nullptr;
        val = nullptr;
      }
      clear_tokens_stack();
      clear_values_stack();
    }

    void parse_query_line(const string& input, int linenum,
                          tag*& parent) {
      parse_line(input, query_tokens, linenum, parent);
    }

    void parse_src_line(const string& input, int linenum,
                        tag*& parent) {
      parse_line(input, src_tokens, linenum, parent);
    }

  public:
    hrml_parser(istream& istr, ostream& ostr): is(istr), os(ostr) {}

    void parse() {
      tag* parent = nullptr;
      string line = string();
      int linenum = 0;
      while(!is.eof() && getline(is, line)) {
        if(linenum == 0) {
          istringstream ss = istringstream(line);
          ss >> num_src_lines  >> num_query_lines;
          //cout << "num_src_lines:" << num_src_lines << endl;
          //cout << "num_query_lines:" << num_query_lines << endl;
        } else if (linenum <= num_src_lines) {
          //cout << "src:" << line << endl;
          parse_src_line(line, linenum+1, parent);
        } else {
          //cout << "query:" << line << endl;
          parse_query_line(line, linenum+1, parent);
        }
        linenum++;
      }
    }

    void print(ostream& os) {
    }
    
    ~hrml_parser() {
      
      string *s;
      while(!values.empty()) {
        s = values.top();
        values.pop();
        delete s;
      }
    
      tag *t;
      for(auto it : objectmap) {
        t = it.second;
        tag::attr_map_type& m =
                t->get_attr_list();
        for(auto it1 : m) {
          tag::attr_type* a = it1.second;
          delete a->get_key(); 
          delete a->get_value(); 
          delete a;
        }
        delete t;
      }
    }
};
