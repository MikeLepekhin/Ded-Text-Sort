/*!
 * \file
 * \brief This file contains the class Text used to keep and sort texts in UTF-16.
 *
 * \author Mikhail Lepekhin
 * \copyright All rights belong to the author
 * \version 1.0
 */

#ifndef TEXT_SORT_TEXT_H
#define TEXT_SORT_TEXT_H

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cwchar>

#include "stdlib_utf16.h"
#include "string_utf16.h"
#include "exceptions.h"

/*!
 * \briefly This comparator is used to sort strings in the
 * file in usual lexicographical order (ignoring separation symbols)
 */
struct DefaultComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str1 < str2;
  }
};

/*!
 * \briefly This comparator is used to sort strings in the
 * file in lexicographical order of reverse strings (ignoring separation symbols)
 */
struct ReverseComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str1.compReverse(str2);
  }
};


/*!
 * \briefly This comparator is used to sort strings in the
 * file in inverted usual lexicographical order (ignoring separation symbols)
 */
struct InvComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str2 < str1;
  }
};


/*!
 * \briefly This comparator is used to sort strings in the
 * file in inverted lexicographical order of reverse strings (ignoring separation symbols)
 */
struct InvReverseComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str2.compReverse(str1);
  }
};

/*!
 * \briefly This comparator returns the primordial order of strings
 */
struct OriginalComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str1.getPtr() < str2.getPtr();
  }
};

/*!
 * \class
 * \briefly This is the class for working with texts in UTF-16
 */
class Text {
 private:
  char16_t* bytes_{nullptr};
  size_t size_{0};
  StringUtf16* lines_{nullptr};
  size_t line_cnt_{0};

  void setLinePointers() {
    if (line_cnt_ == 0) {
      return;
    }

    lines_[0].setPtr(bytes_);
    size_t cur_line = 0;
    for (size_t ch_id = 0; ch_id < size_ && bytes_[ch_id] != L'\0'; ++ch_id) {
      if (bytes_[ch_id] == L'\n') {
        lines_[++cur_line].setPtr(&bytes_[ch_id + 1]);
      }
    }
  }

 public:
  Text() {}

  Text(const char* file_location) {
    if (!file_exists(file_location)) {
      throw NonexistentFileException(file_location, __PRETTY_FUNCTION__);
    }
    printFileInfo(file_location);
    size_ = byte_count(file_location);
    read_file(&bytes_, file_location, size_);
    line_cnt_ = strcnt_in_text(bytes_, size_);
    printf("# Count of lines in the file: \t%ld\n", line_cnt_);
    lines_ = new StringUtf16[line_cnt_ + 1];
    setLinePointers();
  }

  const StringUtf16* operator[](size_t pos) const {
    if (pos >= line_cnt_) {
      throw OutOfRangeException("", __PRETTY_FUNCTION__);
    }
    return lines_ + pos;
  }

  StringUtf16* operator[](size_t pos) {
    if (pos >= line_cnt_) {
      throw OutOfRangeException("", __PRETTY_FUNCTION__);
    }
    return lines_ + pos;
  }

  size_t size() const {
    return line_cnt_;
  }

  /*!
 * \function
 * \briefly This method is used to find out the size of file and its access rights
 */
  void printFileInfo(const char* file_location) {
    print_file_info(file_location);
  }

  /*!
* \function
* \briefly This method prints the text to the empty file
*/
  void writeToFile(FILE* file, const char* output_location = "") {
    printf("# writing text to: \t%s\n", output_location);
    for (size_t line_id = 0; line_id < line_cnt_; ++line_id) {
      add_line_to_file(lines_[line_id].getPtr(), file, lines_[line_id].size());
    }
  }

  ~Text() {
    delete bytes_;
  }
};

#endif //TEXT_SORT_TEXT_H
