/*
 * package for black red binary tree
 */

#ifndef STRUCT_BASIC_UTILS_H_
#define STRUCT_BASIC_UTILS_H_
#include <string>
#include <sstream>
namespace utils {
std::string padding(int n, char c) {
    std::ostringstream oss;
	for (int i = 0; i < n; ++i) {
		oss << c;
	}
	return oss.str();
}
}
#endif // STRUCT_BASIC_UTILS_H_
