//
// Created by mike on 18.09.18.
//

#ifndef TEXT_SORT_STRING_UTF16_H
#define TEXT_SORT_STRING_UTF16_H

#include <algorithm>

class StringUtf16 {
 private:
  char* begin_;

 public:
  StringUtf16(char* begin = nullptr) {
    begin_ = begin;
  }

  size_t size() const {
    return strlen(begin_);
  }

  void swap(StringUtf& another) {
    std::swap(begin_, another.begin_);
  }


};

#endif //TEXT_SORT_STRING_UTF16_H
