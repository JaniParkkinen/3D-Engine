#include <Core/Managers/ResourceManager.hpp>
#include <string>
#include <fstream>
#include <Windows.h>
#include <lodepng/lodepng.h>
#include <Core/Components/Material.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>

namespace Engine {

	ResourceManager* ResourceManager::instance = nullptr;

	ResourceManager* ResourceManager::GetInstance()
	{
		if (instance == nullptr)
		{
			std::cout << "Creating a new resourcemanager" << std::endl;
			instance = new ResourceManager;
		}
		return instance;
	}
	ResourceManager* ResourceManager::LoadResource(std::string filepath)
	{
		try {
			for (auto i : _resources)
			{
				if (i->GetFilename == filepath)
				{
					std::cout << "resource already loaded" << std::endl;
					i->GetResourceID.push_back(1);
					return i;
				}
			}

			//Textfile
			if (filepath.substr(filepath.size() - 4) == ".txt" || filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
			{
				if (filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
				{
					std::cout << "Loading shader file" << std::endl;
					//load shader file
				}
				std::cout << "A text file" << std::endl;
				Resource* res = new Resource();
				res = ResourceManager::LoadResourceType(filepath);
				return res;
			}

		}
	}



}
	
