/*
        shorthash
            C++11 port, MIT (c)2018 Paul Reilly
            Javscript port, MIT (c)2013 Bibig
            mit-license.org

        This port uses byte chars instead of the UTF-16 codepoints in the
        Javascript bitwise hashing algorithm. The results are the same for
        chars within range.
*/

#include "string.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>


class ShortHash {
  public:
    ShortHash() : charList("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") 
    {};
    
    std::string unique(std::string text) {
        return binaryTransfer(bitwise(text), 61);
    }

  private:
    typedef int32_t int32; // algorithm requires 32 bit ints
    const char* charList;
    
    inline int32 bitwise(std::string str) {
        int32 hash = 0;
        int len = str.length();
        if (len == 0) return hash;
        // just byte chars, original supports Unicode
        for (int i=0; i<len; ++i) {
            hash = ((hash << 5) - hash) + str[i];
        }
        return hash;
    }

    std::string binaryTransfer(int integer, int binary) {
        binary = binary == 0 ? 62 : binary;
        std::vector<char> stack;
        int num;
        bool sign = false;
        if (integer < 0) { sign = true; }

        integer = abs(integer);
        while (integer >= binary) {
            num = integer % binary;
            integer = (integer / binary)|0;
            stack.push_back(charList[num]);
        }

        if (integer > 0) {
            stack.push_back(charList[integer]);
        }

        // minus sign replaced with Z in hash
        if (sign) { stack.push_back('Z'); }
        
        std::reverse(stack.begin(), stack.end());

        std::string str(stack.begin(), stack.end());
        return str;
    }
};