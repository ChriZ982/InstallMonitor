#pragma once

#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <filesystem>
#include <time.h>

std::vector<std::string> list_directories(std::string path);
void scan_filesystem();
void compare_filesystem();
bool is_excluded(std::string, std::vector<std::string> excludes);
