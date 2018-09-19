/*!
 * \file
 * \brief This file contains the general exceptions which may arise.
 *
 * \author Mikhail Lepekhin
 * \copyright All rights belong to the author
 * \version 1.0
 */
#ifndef TEXT_SORT_EXCEPTIONS_H
#define TEXT_SORT_EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>

/*!
 * \class
 * \briefly This is the general struct providing opportunity to catch errors and identify the names of the functions in which they occur
 */
struct TextSortException : public std::exception {
  std::string message;
  std::string function_name;

  TextSortException(const std::string& message = "", const std::string& function_name = ""):
    message(message), function_name(function_name) {}
};

struct IncorrectArgumentException : public TextSortException {
  IncorrectArgumentException(const std::string& message, const std::string& function_name = ""):
    TextSortException(message, function_name) {}
};

struct OutOfRangeException : public TextSortException {
  OutOfRangeException(const std::string& message, const std::string& function_name = ""):
    TextSortException(message, function_name) {}
};

struct NonexistentFileException : public TextSortException {
  NonexistentFileException(const std::string& filename, const std::string& function_name = ""):
      TextSortException("", function_name) { message = "File " + filename + " doesn't exist\n";
  }
};

std::ostream& operator<<(std::ostream& os, const TextSortException& iaexception) {
  os << "!!! Exception: " << iaexception.message;
  if (!iaexception.function_name.empty()) {
    os << "(" << iaexception.function_name << ")";
  }
  os << '\n';
  return os;
}


#endif //TEXT_SORT_EXCEPTIONS_H
