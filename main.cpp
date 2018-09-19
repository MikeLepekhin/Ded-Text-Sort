/*!
 * \file
 * \brief This program get a text from <input_file> in UTF-16 encoding and writes to <output_file> these 3 version of it:
 *        1) The text sorting in lexicographical order (ignoring separation symbols)
 *        2) The text sorting in lexicographical order of reversed strings (ignoring separation symbols)
 *        3) The text in original order of strings
 * \details The program has options --help and --verbose.
 *
 * \author Mikhail Lepekhin
 * \copyright All rights belong to the author
 * \version 1.0
 */

#include <iostream>
#include <cstdio>
#include <getopt.h>

#include "exceptions.h"
#include "text.h"

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

  try {
    Text text(argv[1]);
    text.sort<DefaultComp>();

    if (argc == 3) {
      text.writeToFile(argv[2]);
    } else {
      text.writeToFile(argv[1]);
    }
    text.sort<ReverseComp>();

    if (argc == 3) {
      text.addToFile(argv[2]);
    } else {
      text.addToFile(argv[1]);
    }
    text.sort<OriginalComp>();

    if (argc == 3) {
      text.addToFile(argv[2]);
    } else {
      text.addToFile(argv[1]);
    }

  } catch (const TextSortException& tsexception) {
    std::cerr << tsexception;
    return 1;
  }
  return 0;
}