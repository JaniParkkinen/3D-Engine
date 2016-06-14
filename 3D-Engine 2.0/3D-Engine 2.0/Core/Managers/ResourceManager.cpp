#include <Core/Managers/ResourceManager.hpp>

namespace Engine {
	Resource* ResourceManager::LoadResource(std::string filepath)
	{
		for (auto i : _resources)
		{
			if (i->filepath == filepath)
			{
				std::cout << "resource already loaded" << std::endl;
				i->resourceUsers.push_back(1);
				return i;
			}
		}

		//TextFile
		if (filepath.substr(filepath.size() - 4) == ".txt" || filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
		{
			if (filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
			{
				std::cout << "Loading shader file" << std::endl;
				// load shader file
			}
			std::cout << "A text file" << std::endl;
			Resource* res = new Resource();
			res = ResourceManager::LoadTextResource(filepath);
			return res;
		}
		//UnknownFile
		else
		{
			std::cout << "filetype not regognized" << std::endl;
			return 0;
		}
	};

	void ResourceManager::UnLoadResource(int ID)
	{

		_it = _resources.begin();
		while (_it != _resources.end())
		{
			if ((*_it)->ID == ID)
			{
				std::cout << "Deleting resource" << std::endl;
				(*_it)->resourceUsers.pop_back();
				if ((*_it)->resourceUsers.size() <= 0)
				{
					std::cout << "unloading resource" << std::endl;
					_it = _resources.erase(_it);
				}
				else
					_it++;
			}
			else
				_it++;
		}
	};

	int ResourceManager::GetResourceUsers(int ID)
	{
		_it = _resources.begin();
		while (_it != _resources.end())
		{
			if ((*_it)->ID == ID)
			{
				return (*_it)->resourceUsers.size();
			}
			_it++;
		}
		std::cout << "Resource not found" << std::endl;
		return 0;
	};

	Resource* ResourceManager::LoadTextResource(std::string filepath) {
		std::cout << "Loading Resource" << std::endl;
		Resource * res = new Resource;
		res->filepath = filepath;
		res->type = Text;
		res->ID = ++ID_generator;
		res->resourceUsers.push_back(1);

		std::ifstream file(filepath, std::ifstream::binary);
		if (file.is_open())
		{
			// Get size of file///////////
			file.seekg(0, file.end);	//
			int size = file.tellg();	//
			file.seekg(0, file.beg);	//

										// Allocate buffer for text/////
			char* buffer = new char[size];//

										  // Read file//////////////////
			file.read(buffer, size);	// 
			buffer[size] = NULL;		//
			file.close();				//

										//Change text into string/////
			std::string readFile;		//
			readFile = buffer;			//

										//Set text to resource////////
			res->setTextData(readFile);//

		}
		_resources.push_back(res);
		return res;
	};
};
