//
// Created by mike on 17.09.18.
//

#ifndef TEXT_SORT_TEXT_H
#define TEXT_SORT_TEXT_H

#include <unistd.h>
#include <cstdio>
#include <sys/stat.h>
#include <cassert>
#include <cwchar>

#include "stdlib_utf16.h"

class Text {
 private:
  char16_t* bytes_{nullptr};
  size_t size_{0};

 public:
  Text() {}

  Text(const char* file_location) {
    printFileInfo(file_location);
    size_ = byte_count(file_location);
    read_file(&bytes_, file_location, size_);

    //std::wcout << bytes_ << '\n';
    //std::cout << strlen_utf16(bytes_) << '\n';
  }

  void printFileInfo(const char* file_location) {
    struct stat fileStat;
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

  void printFile(const char* file_location) {
    printf("# printing file: \t%s\n", file_location);

    FILE* text_file = fopen(file_location, "r");

    char cur_ch = fgetc(text_file);
    while (cur_ch != EOF) {
      printf("%c", cur_ch);
      cur_ch = fgetc(text_file);
    }
    fclose(text_file);
  }

  void writeToFile(const char* output_location) {
    printf("# writing file to: \t%s\n", output_location);
    write_to_file(bytes_, output_location);
  }

  ~Text() {
    delete bytes_;
  }
};

#endif //TEXT_SORT_TEXT_H
