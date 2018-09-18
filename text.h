#ifndef TEXT_SORT_TEXT_H
#define TEXT_SORT_TEXT_H

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cwchar>

#include "stdlib_utf16.h"
#include "string_utf16.h"

struct DefaultComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str1 < str2;
  }
};

struct ReverseComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str1.compReverse(str2);
  }
};

struct InvComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str2 < str1;
  }
};

struct InvReverseComp {
  bool operator()(const StringUtf16& str1, const StringUtf16& str2) {
    return str2.compReverse(str1);
  }
};

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
    printFileInfo(file_location);
    size_ = byte_count(file_location);
    read_file(&bytes_, file_location, size_);
    line_cnt_ = strcnt_in_text(bytes_, size_);
    printf("# Count of lines in the file: \t%ld\n", line_cnt_);
    lines_ = new StringUtf16[line_cnt_ + 1];
    setLinePointers();
  }

  void printFileInfo(const char* file_location) {
    print_file_info(file_location);
  }

  template<class Comp = DefaultComp>
  void sort() {
    std::cout << "# i'm sorting your file\n";
    std::sort(&lines_[0], &lines_[line_cnt_], Comp());
    std::cout << "# it's ok\n";
  }

  void writeToFile(const char* output_location) {
    printf("# writing file to: \t%s\n", output_location);
    create_empty_file(output_location);
    for (size_t line_id = 0; line_id < line_cnt_; ++line_id) {
      add_line_to_file(lines_[line_id].getPtr(), output_location, lines_[line_id].size());
    }
  }

  ~Text() {
    delete bytes_;
  }
};

#endif //TEXT_SORT_TEXT_H
