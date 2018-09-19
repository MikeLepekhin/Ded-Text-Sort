/*!
 * \file
 * \brief This file contains the class StringUtf16 used to keep lines of text in UTF-16.
 *
 * \author Mikhail Lepekhin
 * \copyright All rights belong to the author
 * \version 1.0
 */

#ifndef TEXT_SORT_STRING_UTF16_H
#define TEXT_SORT_STRING_UTF16_H

#include <algorithm>

#include "stdlib_utf16.h"
#include "exceptions.h"

class StringUtf16;

size_t nextNotSepar(const StringUtf16& str, size_t pos);
size_t prevNotSepar(const StringUtf16& str, size_t pos);

/*!
 * \class
 * \briefly This is the class for working with strings in UTF-16
 */
class StringUtf16 {
 private:
  char16_t* begin_{nullptr};
  size_t size_{0};

 public:
  StringUtf16(char16_t* begin = nullptr, size_t size = 0):
    begin_(begin), size_(size) {
    if (size_ == 0) {
      size_ = strlen_utf16(begin_);
    }
  }

  void setPtr(char16_t* another) {
    begin_ = another;
    size_ = strlen_utf16(begin_);
  }

  char16_t* getPtr() const {
    return begin_;
  }

  size_t size() const {
    return size_;
  }

  void swap(StringUtf16& another) {
    std::swap(begin_, another.begin_);
  }

  char16_t& operator[](size_t pos)  {
    if (pos >= size_) {
      throw OutOfRangeException("", __PRETTY_FUNCTION__);
    }
    return begin_[pos];
  }

  const char16_t& operator[](size_t pos) const {
    if (pos >= size_) {
      throw OutOfRangeException("", __PRETTY_FUNCTION__);
    }
    return begin_[pos];
  }

  /*!
* \function
* \briefly This operator is used to sort strings in usual lexicographical order ignoring separation characters
*/
  bool operator<(const StringUtf16& another) const {
    //std::cout << "kek\n";
    size_t char_id1 = 0;
    size_t char_id2 = 0;

    char_id1 = nextNotSepar(*this, char_id1);
    char_id2 = nextNotSepar(another, char_id2);
    for ( ; char_id1 < size_ && char_id2 < another.size_; ++char_id1, ++char_id2) {
      if (htobe16(begin_[char_id1]) < htobe16(another[char_id2])) {
        return true;
      } else if (htobe16(begin_[char_id1]) > htobe16(another[char_id2])) {
        return false;
      }
      char_id1 = nextNotSepar(*this, char_id1);
      char_id2 = nextNotSepar(another, char_id2);
    }
    return char_id1 == size_ && char_id2 != another.size_;
  }

  /*!
* \function
* \briefly This operator is used to sort strings in lexicographical order of reserve strings ignoring separation characters
*/
  bool compReverse(const StringUtf16& another) const {
    size_t char_id1 = 0;
    size_t char_id2 = 0;

    char_id1 = prevNotSepar(*this, char_id1);
    char_id2 = prevNotSepar(another, char_id2);
    for ( ; char_id1 < size_ && char_id2 < another.size_; ++char_id1, ++char_id2) {
      if (htobe16(begin_[size_ - char_id1 - 1]) < htobe16(another.begin_[another.size_ - char_id2 - 1])) {
        return true;
      } else if (htobe16(begin_[size_ - char_id1 - 1]) > htobe16(another.begin_[another.size_ - char_id2 - 1])) {
        return false;
      }
      char_id1 = prevNotSepar(*this, char_id1);
      char_id2 = prevNotSepar(another, char_id2);
    }
    return char_id1 == size_ && char_id2 != another.size_;
  }
};


size_t nextNotSepar(const StringUtf16& str, size_t pos) {
  while (pos < str.size() && is_separator(str[pos])) {
    ++pos;
  }
  return pos;
}

size_t prevNotSepar(const StringUtf16& str, size_t pos) {
  while (pos < str.size() && is_separator(str[str.size() - pos - 1])) {
    ++pos;
  }
  return pos;
}

#endif //TEXT_SORT_STRING_UTF16_H
