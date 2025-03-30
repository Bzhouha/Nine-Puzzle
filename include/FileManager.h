//
// Created by 毕洲华 on 25-3-30.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <GlobalVars.h>


class FileManager
{
public:
    static int parseArgument(int argc, char * argv[])
    {
        // 遍历所有参数（argv[0] 是程序名，如 ./a.out）
        for (int i = 1; i < argc; ++i)
            {
                if (std::string arg = argv[i]; arg == "-f" || arg == "--file")
                    {
                        if (i + 1 < argc)
                            {
                                // 确保选项后还有一个参数
                                config_file = argv[i + 1];
                                i++; // 跳过已处理的参数
                            } else
                            {
                                std::cerr << "Error: Missing filename after -f" << std::endl;
                                return 1;
                            }
                    }
            }
        if (!config_file.empty())
            {
                std::cout << "Using config file: " << config_file << std::endl;
            } else
            {
                std::cerr << "Error: No config file specified (use -f <file>)" << std::endl;
                return 1;
            }
        return 0;
    }
};

int loadConfigFromFile();


#endif //FILEMANAGER_H
