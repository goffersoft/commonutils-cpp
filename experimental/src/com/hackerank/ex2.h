#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class sparse_bitmap{
  private:
    using vec_type = uint32_t;
    using p_vec_type = vec_type*;

    p_vec_type full_row = new vec_type;
    p_vec_type invalid_key = new vec_type;
    uint32_t uniq_count = 0;

    unordered_map<uint32_t, p_vec_type> bitmap;// = unordered_map<uint32_t, p_vec_type>();
    const uint32_t vector_size = 4096;
    const uint32_t row_size = 4095;
    const uint32_t bits_per_vectype = sizeof(vec_type)*8;
    const uint32_t bits_per_row = row_size*bits_per_vectype;

    inline uint32_t get_rownum(uint32_t bitpos) {
      return bitpos/bits_per_row;
    }

    inline uint32_t get_vec_rownum(uint32_t bitpos) {
      return (bitpos%bits_per_row)/bits_per_vectype + 1;
    }

    inline uint32_t get_vec_colnum(uint32_t bitpos) {
      /*cout << "bitpos=" << bitpos
           << ": bitpos%bits_per_row=" << bitpos%bits_per_row
           << ": bits_per_vectype=" << bits_per_vectype << endl;*/
      return (bitpos%bits_per_row)%bits_per_vectype;
    }

    void set_bit(uint32_t bitpos, p_vec_type r) {
      if(r == invalid_key)
        return;

      if(r == full_row)
        return;

      uint32_t  row = get_vec_rownum(bitpos);
      uint32_t  col = get_vec_colnum(bitpos);
      
      /*cout << "slot " << get_rownum(bitpos)
           << " row=" << row << " col=" << col
           << " 0x" << hex << r[row] << dec << endl;*/

      if(row == 0 || row >= vector_size)
        cout << "bad row value row=" << row << " vec_size=" << vector_size << endl; 

      if(col == 0 || col >= bits_per_vectype)
        cout << "bad col value=" << col << endl;  

      if((r[row] & ((uint32_t)1 << col)) == ((uint32_t)1 << col))
        return;
      
      r[row] |= (1 << col);
      r[0] += 1;
      uniq_count++;
      //cout << "row=" << row << " col=" << col << " *uc=" << uniq_count << endl;
      //cout << " *uc=" << dec << uniq_count << endl;
    }

    int num_calls = 0;

    bool is_bit_set(uint32_t bitpos, p_vec_type r) {
      if(r == invalid_key)
        return false;

      if(r == full_row)
        return true;

      uint32_t row = get_vec_rownum(bitpos);
      uint32_t col = get_vec_colnum(bitpos);

      return ((r[row] & ((uint32_t)1<< col)) == ((uint32_t)1 << col));
    }

    p_vec_type get_or_create_row(uint32_t row, uint32_t bitpos) {
      auto it = bitmap.find(row);
      p_vec_type v;

      if(it == bitmap.end()) {
        v = new vec_type[vector_size]();
        /*cout << ++num_calls 
             << " : bits_per_row=" << bits_per_row
             << " : bitpos=" << bitpos
             << " : row=" << row 
             << " : vec_row=" << get_vec_rownum(bitpos)
             << " : vec_col=" << get_vec_colnum(bitpos)
             << " : Creating vector of size " << vector_size << endl;*/
        v[0] = 0;
        bitmap[row] = v;
        return v;
      }

      v = ((*it).second);

      if((v != full_row) &&
         (v[0] == (bits_per_row - 1)) &&
         (!is_bit_set(bitpos, v))) {
        //cout << "here " << v[0] << endl; 
        bitmap[row] = full_row;
        delete[] v;
        v = full_row;
        uniq_count++;
      }
      return v;
    }

    p_vec_type get_row(int row) {
      auto it = bitmap.find(row);

      if(it == bitmap.end())
        return invalid_key;

      return ((*it).second);
    }

  public:
    sparse_bitmap() {
    }

    void set_bit(uint32_t bitpos) {
      //cout << bitpos << ":"
      //     << get_rownum(bitpos) << ":"
      //     << col << ":"
      //     << get_vec_rownum(col) << ":"
      //     << get_vec_colnum(col) << endl;
      set_bit(bitpos,
              get_or_create_row(get_rownum(bitpos), bitpos));
    }

    bool is_bit_set(uint32_t bitpos) {
      return is_bit_set(bitpos, get_row(get_rownum(bitpos)));
    }

    int num_bits_set() {
      return uniq_count;
  }

  void print_map() {
     cout << "begin" << endl;
    for(auto it : bitmap) {
      cout << it.first << " " << it.second << endl;
    }
    cout << "end" << endl;
  }
  
  ~sparse_bitmap() {
    p_vec_type v;
    //auto itend = bitmap.end();
    for(auto it : bitmap) {
      //cout << hex << &it  << " " << &itend << dec << endl;
      v = it.second;
      if(v == full_row) continue;
      delete[] v;
    }
    delete full_row;
    delete invalid_key;
  }
};
