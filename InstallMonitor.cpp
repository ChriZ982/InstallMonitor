#include "InstallMonitor.h"

int main()
{
    std::cout << "-------------------------\n"
			  << "|    INSTALL MONITOR    |\n"
			  << "-------------------------\n\n"
			  << "(1) Scan filesystem\n"
			  << "(2) Compare filesystems\n";

	int action;
	std::cin >> action;

	switch (action)	{
		case 1:
			scan_filesystem();
			break;
		case 2:
			compare_filesystem();
			break;
		default:
			std::cout << "Error: Action '" << action << "' not existing.\n";
	}

	std::cout << "\nProgram finished!\n";
}

void scan_filesystem() {
	std::cout << "\nScanning filesystem...\n";
	time_t raw_time;
	struct tm time_info;
	char buffer[80];

	time(&raw_time);
	localtime_s(&time_info, &raw_time);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &time_info);
	const std::string str(buffer);

	std::vector<std::string> fs = list_directories("C:\\");

	std::ofstream output_file("./records/files_" + str + ".txt");
	const std::ostream_iterator<std::string> output_iterator(output_file, "\n");
	std::copy(fs.begin(), fs.end(), output_iterator);
}

void compare_filesystem() {
	std::cout << "\nAvailable scans:\n";

	int i = 1;
	std::vector<std::string> files;
	for (auto & p : std::experimental::filesystem::directory_iterator("./records"))	{
		files.push_back(p.path().string());
		std::cout << "(" << i++ << ") " << p.path().filename().string() << "\n";
	}

	std::cout << "\nSelect source scan:\n";
	int select1;
	std::cin >> select1;

	std::cout << "Select target scan:\n";
	int select2;
	std::cin >> select2;

	std::cout << "\nComparing files...\n";
	std::ifstream file1(files[select1 - 1]);
	std::ifstream file2(files[select2 - 1]);
	std::ifstream file_exclude("excludes.txt");

	std::vector<std::string> lines1;
	std::vector<std::string> lines2;
	std::vector<std::string> lines_exclude;

	std::string line;
	while (std::getline(file1, line)) {
		lines1.push_back(line);
	}
	while (std::getline(file2, line)) {
		lines2.push_back(line);
	}
	while (std::getline(file_exclude, line)) {
		lines_exclude.push_back(line);
	}

	int i1 = 0;
	int i2 = 0;
	while (i1 < lines1.size() && i2 < lines2.size()) {
		std::string line1 = lines1[i1];
		std::string line2 = lines2[i2];

		if(is_excluded(lines1[i1], lines_exclude)) {
			++i1;
			continue;
		}
		if (is_excluded(lines2[i2], lines_exclude)) {
			++i2;
			continue;
		}

		std::transform(line1.begin(), line1.end(), line1.begin(), ::tolower);
		std::transform(line2.begin(), line2.end(), line2.begin(), ::tolower);

		if (line1 < line2) {
			std::cout << "removed: " << lines1[i1++] << std::endl;
		} else if(line1 > line2) {
			std::cout << "added  : " << lines2[i2++] << std::endl;
		} else {
			++i1;
			++i2;
		}
	}
	while (i1 < lines1.size()) {
		std::cout << "removed: " << lines1[i1++] << std::endl;
	}
	while (i2 < lines2.size()) {
		std::cout << "added  : " << lines2[i2++] << std::endl;
	}
}

bool is_excluded(std::string path, std::vector<std::string> excludes) {
	for(auto ex : excludes)	{
		if(!path.compare(0, ex.size(), ex)) {
			return true;
		}
	}
	return false;
}


std::vector<std::string> list_directories(std::string path) {
	std::vector<std::string> directories;
	for (auto & p : std::experimental::filesystem::directory_iterator(path)) {
		const std::string sub_path = p.path().string();

		directories.push_back(sub_path);

		if (is_directory(p)) {
			try {
				std::vector<std::string> sub_directories = list_directories(sub_path);
				directories.insert(directories.end(), sub_directories.begin(), sub_directories.end());
			} catch(std::invalid_argument ex)
			{
				std::cerr << "ERROR at "<< sub_path << std::endl;
			}
		}
	}
	return directories;
}
