#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include <vector>

std::vector<std::string> list_directories(std::string path);
void scan_filesystem();
void compare_filesystem();
bool is_excluded(std::string, std::vector<std::string> excludes);
