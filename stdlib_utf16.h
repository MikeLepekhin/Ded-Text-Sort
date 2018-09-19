#ifndef TEXT_SORT_STDLIB_UTF16_H
#define TEXT_SORT_STDLIB_UTF16_H

#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>
#include "exceptions.h"

bool file_exists(const char* filename) {
  FILE* file = fopen(filename, "r");

  if (file) {
    fclose(file);
    return true;
  }
  return false;
}

size_t byte_count(const char* file_location) {
  struct stat fileStat = {};
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

size_t textsize(const char16_t* str) {
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
    text_size = textsize(text);
  }
  fwrite(text, sizeof(char16_t), text_size, output_file);
  fclose(output_file);
}

void add_line_to_file(char16_t* str, const char* output_location, size_t len = 0) {
  FILE* output_file = fopen(output_location, "a");

  if (len == 0) {
    len = strlen_utf16(str);
  }
  fwrite(str, sizeof(char16_t), len + 1, output_file);
  fclose(output_file);
}

bool is_separator(char16_t ch) {
  return ch == L'.' || ch == L'!' || ch == L':' || ch == L'"'
      || ch == L',' || ch == L'-' || ch == L';' || ch == L'?'
      || ch == L'(' || ch == L')' || ch == L'[' || ch == L']'
      || ch == L'{' || ch == L'}' || ch == L'«' || ch == L'»';
}

void print_without_separators(char16_t* str, const char* filename) {
  size_t len = strlen_utf16(str) ;
  char16_t buf[len + 1];
  size_t buf_size = 0;

  for (size_t i = 0; i < len; ++i) {
    if (!is_separator(str[i])) {
      buf[buf_size++] = str[i];
    }
  }
  buf[buf_size] = '\0';
  add_line_to_file(buf, filename, buf_size);
}

size_t strcnt_in_text(char16_t* text, size_t text_size = 0) {
  if (text_size == 0) {
    text_size = textsize(text);
  }
  size_t str_cnt = 0;
  for (size_t char_id = 0; char_id < text_size; ++char_id) {
    str_cnt += (text[char_id] == L'\n');
  }
  return str_cnt;
}

void print_file(const char* file_location) {
  printf("# printing file: \t%s\n", file_location);

  FILE* text_file = fopen(file_location, "r");

  char cur_ch = fgetc(text_file);
  while (cur_ch != EOF) {
    printf("%c", cur_ch);
    cur_ch = fgetc(text_file);
  }
  fclose(text_file);
}

void create_empty_file(const char* file_location) {
  FILE* text_file = fopen(file_location, "w");

  fclose(text_file);
}


void print_file_info(const char* file_location) {
  struct stat fileStat;
  assert(stat(file_location, &fileStat) == 0);
  assert(stat(file_location, &fileStat) == 0);

  printf("# information for file: %s\n",file_location);
  printf("# ---------------------------\n");
  printf("# File Size: %ld bytes\n",fileStat.st_size);

  printf("# File Permissions: ");
  printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
  printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
  printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n\n");
}
#endif //TEXT_SORT_STDLIB_UTF16_H
