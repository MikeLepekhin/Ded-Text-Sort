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
    return strcmp_utf16(this->begin_, another.begin_, size_, another.size_);
  }

  /*!
* \function
* \briefly This operator is used to sort strings in lexicographical order of reserve strings ignoring separation characters
*/
  bool compReverse(const StringUtf16& another) const {
    return strcmp_rev(this->begin_, another.begin_, size_, another.size_);
  }
};


#endif //TEXT_SORT_STRING_UTF16_H
