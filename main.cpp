#include <iostream>
#include <cstdio>
#include "text.h"
#include <getopt.h>

#define MY_CHAR char

void hello() {
  std::cout << "# Text Sorter 1.0\n";
  std::cout << "# Hello! This is quite fast and multifunctional program for text sorting\n";
  std::cout << "# If you want to figure out how to use it, use --help option\n";
}

void help() {
  std::cout << "# usage:\n";
  std::cout << "# text_sort file\n";
}

void parseOptions(int argc, char** argv) {
  const char* const short_opts = "v:h";
  const option long_opts[] = {
    {"verbose", no_argument, nullptr, 'v'},
    {"help", no_argument, nullptr, 'h'},
    {nullptr, no_argument, nullptr, 0}
  };

  int opt = 0;
  while (opt != -1) {
    const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

    switch (opt) {
      case 'h':
        help();
        exit(0);
      case -1:
        return;
      case '?':
      default:
        std::cerr << "!!! unknown option " << opt << "\n";
        return;
    }
  }
}

bool isFileExist(const char* filename){
  FILE *file = fopen(filename, "r");
  if (file) {
    fclose(file);
    return true;
  }
  return false;
}

int main(int argc, char** argv) {
  setlocale(LC_ALL, "ru_RU.UTF-8");

  parseOptions(argc, argv);
  if (argc > 3) {
    std::cerr << "!!! Incorrect number of arguments. You should enter only input and output file location.\n";
    return 1;
  }
  if (argc == 1) {
    help();
    return 1;
  }
  if (!isFileExist(argv[1])) {
    std::cerr << "!!! Input file " << argv[1] << " doesn't exist\n";
    return 1;
  }

  Text text(argv[1]);
  if (argc == 3) {
    text.writeToFile(argv[2]);
  } else {
    text.writeToFile(argv[1]);
  }

  return 0;
}