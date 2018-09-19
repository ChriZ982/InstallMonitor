#pragma once

std::vector<std::string> list_directories(std::string path);
void scan_filesystem();
void compare_filesystem();
bool is_excluded(std::string, std::vector<std::string> excludes);
