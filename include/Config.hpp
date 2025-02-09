#pragma once

#include <iostream>
#include <filesystem>

namespace Config
{
    inline std::string GetWorkspaceFolder() 
    {
        std::string file_path = std::filesystem::current_path();
        unsigned int last_slash = file_path.rfind('/');
        std::string file_path_2 = file_path.substr(0, last_slash);
        std::cout << "file_path: " << file_path_2 << std::endl;
        unsigned int second_last_slash = file_path_2.rfind('/');
        std::string workspace_path = file_path_2.substr(0, second_last_slash);

        std::cout << "file_path: " << workspace_path << std::endl;
        
        return workspace_path;
    };

    inline const std::string workplace_folder = GetWorkspaceFolder();
}