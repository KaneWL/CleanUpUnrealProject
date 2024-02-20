#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>

int main()
{
	std::string currendPath = std::filesystem::current_path().string();
	std::cout << "Current path is: " << currendPath << std::endl;

	std::vector<std::string> filesExtentions;
	std::vector<std::string> directoriesNames;

	// 读取gitignore文件
	std::string gitignorePath = currendPath + "/.gitignore";
	std::ifstream gitignoreFile(gitignorePath);
	std::string line;
	while (std::getline(gitignoreFile, line))
	{
		std::string::size_type pos = line.find_first_of("*");
		if (pos != std::string::npos)
		{
			line.erase(0, 1);
			std::cout << "file extention:" << line << std::endl;
			filesExtentions.push_back(line);
		}
		else
		{
			std::cout << "directory name:" << line << std::endl;
			directoriesNames.push_back(line);
		}
	}

	// 读取到的文件和目录
	std::vector<std::string> files;
	std::vector<std::string> directories;

	// 遍历文件夹
	for (auto& p : std::filesystem::recursive_directory_iterator(currendPath))
	{
		if (p.is_regular_file())
		{
			std::string fileExtention = p.path().extension().string();
			for (auto& extention : filesExtentions)
			{
				if (fileExtention == extention)
				{
					files.push_back(p.path().string());
				}
			}
		}
		else if (p.is_directory())
		{
			std::string directoryName = p.path().filename().string();
			for (auto& directory : directoriesNames)
			{
				if (directoryName == directory)
				{
					directories.push_back(p.path().string());
				}
			}
		}
	}

	for (auto directory : directories)
	{
		std::cout << "delete directory:" << directory << std::endl;
		std::filesystem::remove_all(directory);
	}

	for (auto file : files)
	{
		std::cout << "delete file:"<<file << std::endl;
		std::filesystem::remove_all(file);
	}
	std::cout << "clean up complete!!!" << std::endl;
	system("pause");
	return 0;
}