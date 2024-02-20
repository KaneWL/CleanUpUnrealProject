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
	// 检查文件是否存在
	if (!gitignoreFile.is_open())
	{
		std::cout << "gitignore file not found!!!" << std::endl;
		system("pause");
		return 0;
	}
	std::string line;
	std::string fileExtentionString;
	std::string directoryString;
	while (std::getline(gitignoreFile, line))
	{
		std::string::size_type pos = line.find_first_of("*");
		if (pos != std::string::npos)
		{
			line.erase(0, 1);
			fileExtentionString += line;
			filesExtentions.push_back(line);
		}
		else
		{
			directoryString += line + " ";
			directoriesNames.push_back(line);
		}
	}
	std::cout << "load file extention:" << fileExtentionString << std::endl;
	std::cout << "load directory     :"<<directoryString << std::endl;

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
		std::cout << "delete file:" << file << std::endl;
		std::filesystem::remove_all(file);
	}
	std::cout << "clean up complete!!!" << std::endl;
	system("pause");
	return 0;
}