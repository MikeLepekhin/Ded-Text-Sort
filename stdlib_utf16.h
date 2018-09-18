//
// Created by mike on 18.09.18.
//

#ifndef TEXT_SORT_STDLIB_UTF16_H
#define TEXT_SORT_STDLIB_UTF16_H

#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>

size_t byte_count(const char* file_location) {
  struct stat fileStat;
  assert(stat(file_location, &fileStat) == 0);

  return fileStat.st_size;
}

void read_file(char16_t** destination, const char* filename, size_t byte_cnt = 0) {
  if (byte_cnt == 0) {
    byte_cnt = byte_count(filename);
  }
  *destination = new char16_t[byte_cnt + 1];

  FILE* text_file = fopen(filename, "r");
  fread(*destination, sizeof(char16_t), byte_cnt, text_file);
  fclose(text_file);
}

size_t strlen_utf16(const char16_t* str) {
  if (str == NULL) {
    return 0;
  }
  size_t cur_len = 0;
  while (str[cur_len] != L'\0' && str[cur_len] != L'\n') {
    ++cur_len;
  }
  return cur_len;
}

size_t textsize_utf16(const char16_t* str) {
  if (str == NULL) {
    return 0;
  }
  size_t cur_len = 0;
  while (str[cur_len] != L'\0') {
    ++cur_len;
  }
  return cur_len;
}

void write_to_file(char16_t* text, const char* output_location, size_t text_size = 0) {
  FILE* output_file = fopen(output_location, "w");

  if (text_size == 0) {
    text_size = textsize_utf16(text);
  }
  fwrite(text, sizeof(char16_t), text_size, output_file);
  fclose(output_file);
}

bool is_separator(char16_t ch) {
  return ch == L'.' || ch == L',' || ch == L'-' || ch == L';' || ch == L'?' || ch == L'!' || ch == L':';
}

void print_without_separators(char16_t* str) {
  size_t len = strlen_utf16(str) ;
  char16_t buf[len + 1];
  size_t buf_size = 0;

  for (size_t i = 0; i < len; ++i) {
    if (!is_separator(str[i])) {
      buf[buf_size++] = str[i];
    }
  }
}

#endif //TEXT_SORT_STDLIB_UTF16_H
