#include <iostream>
#include <Windows.h>

#include <lodepng/lodepng.h>
#include <lodepng/lodepng.cpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>

#include <Core/Message.hpp>
#include <Core/Components/Material.hpp>
#include <Core/Managers/ResourceManager.hpp>

namespace Engine {

	std::shared_ptr<Resource> ResourceManager::LoadResource(std::string filepath)
	{
		try {
			for (auto i : _resources)
			{
				if (i->getFilePath() == filepath)
				{
					Message("Resource already loaded.", Engine::MessageType::Info);
					i->pushResourceUsers(1);
					
					return i;
				}
			}

			std::shared_ptr<Resource> res = nullptr;
			
			//TextFile
			if (filepath.substr(filepath.size() - 4) == ".txt" || filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
			{
				Message("Loading text file.", Engine::MessageType::Info);
				res = ResourceManager::LoadTextResource(filepath);
				return res;
			}
			//ImageFile
			else if (filepath.substr(filepath.size() - 4) == ".png")
			{
				Message("Loading image file.", Engine::MessageType::Info);
				res = ResourceManager::LoadImageResource(filepath);
				return res;
			}
			//AudioFile
			else if (filepath.substr(filepath.size() - 4) == ".wav")
			{
				Message("Loading audio file.", Engine::MessageType::Info);
				res = ResourceManager::LoadAudioResource(filepath);

				return res;
			}
			//FontFile
			else if (filepath.substr(filepath.size() - 4) == ".ttf")
			{
				Message("Loading font file.", Engine::MessageType::Info);


				size_t size = strlen(filepath.c_str()) + 1; // +1 to include NULL
				wchar_t* wc = new wchar_t[size];
				size_t outSize;
				mbstowcs_s(&outSize, wc, size, filepath.c_str(), size - 1);

				AddFontResourceEx(wc, FR_PRIVATE, 0);

				res = ResourceManager::LoadFontResource(filepath);
				return res;
			}
			else if (filepath.substr(filepath.size() - 4) == ".obj")
			{
				Message("Loading obj file.", Engine::MessageType::Info);
				res = ResourceManager::LoadObjectResource(filepath);

				return res;
			}
			//UnknownFile
			else
			{
				Message("Filetype not recognized.", Engine::MessageType::Error);
			}
		}
		catch (...) {
			return nullptr;
		};
	}
	void ResourceManager::unLoadResource(int ID)
	{

		_it = _resources.begin();
		while (_it != _resources.end())
		{
			if ((*_it)->setID(ID))
			{
				Message("Deleting resource user.", Engine::MessageType::Info);
				(*_it)->popResourceUsers();
				if ((*_it)->sizeResourceUsers() <= 0)
				{
					Message("Unloading resource.", Engine::MessageType::Info);
					_it = _resources.erase(_it);
				}
				else
					_it++;
			}
			else
				_it++;
		}
	}
	int ResourceManager::GetResourceUsers(int ID)
	{
		try
		{
			_it = _resources.begin();
			while (_it != _resources.end())
			{
				if ((*_it)->setID(ID))
				{
					return (*_it)->sizeResourceUsers();
				}
				_it++;
			}
			Message("Resource not found.", Engine::MessageType::Error);
		}
		catch (int i) {
			return i;
		}
		catch (...) {
			return -1;
		}
	}

	std::shared_ptr<Resource> ResourceManager::LoadTextResource(std::string filepath)
	{
		std::shared_ptr<Resource> res = std::make_shared<Resource>();
		res->setFilePath(filepath);
		res->setType(Resource_Type::Resource_Text);
		res->setID(++ID_generator);
		res->pushResourceUsers(1);

		std::ifstream file(filepath, std::ifstream::binary);
		if (file.is_open())
		{
			// Get size of file///////////////
			file.seekg(0, file.end);		//
			int size = file.tellg();		//
			file.seekg(0, file.beg);		//

											// Allocate buffer for text/////
			char* buffer = new char[size];	//

											// Read file//////////////////
			file.read(buffer, size);		// 
			buffer[size] = NULL;			//
			file.close();					//

											//Change text into string/////
			std::string readFile;			//
			readFile = buffer;				//

											//Set text to resource////////
			res->setTextData(readFile);		//

		}
		else {
			Message("Couldn't open text file.", Engine::MessageType::Error);
		}
		_resources.push_back(res);
		return res;
	}
	std::shared_ptr<Resource> ResourceManager::LoadImageResource(std::string filepath)
	{
		std::shared_ptr<Resource> res = std::make_shared<Resource>();
		res->setFilePath(filepath);
		res->setType(Resource_Type::Resource_Image);
		res->setID(++ID_generator);
		res->pushResourceUsers(1);
		Image img;
		unsigned error = lodepng::decode(img.imageData, img.size.x, img.size.y, filepath);

		if (error) {
			Message("Error loading image file.", Engine::MessageType::Error);
		}

		res->setImageData(img);

		_resources.push_back(res);
		return res;
	}
	std::shared_ptr<Resource> ResourceManager::LoadAudioResource(std::string filepath)
	{

		std::shared_ptr<Resource> res = std::make_shared<Resource>();
		res->setFilePath(filepath);
		res->setType(Resource_Type::Resource_Audio);
		res->setID(++ID_generator);
		res->pushResourceUsers(1);


		//res->setAudioEngine(soundEngine);

		//res->setAudio(filepath);
		_resources.push_back(res);
		return res;
	}
	std::shared_ptr<Resource> ResourceManager::LoadFontResource(std::string filepath)
	{

		std::shared_ptr<Resource> res = std::make_shared<Resource>();
		res->setFilePath(filepath);
		res->setType(Resource_Type::Resource_Font);
		res->setID(++ID_generator);
		res->pushResourceUsers(1);

		_resources.push_back(res);
		return res;
	}
	std::shared_ptr<Resource> ResourceManager::LoadObjectResource(std::string filepath)
	{

		std::shared_ptr<Resource> res = std::make_shared<Resource>();
		res->setFilePath(filepath);
		res->setType(Resource_Type::Resource_Obj);
		res->setID(++ID_generator);
		res->pushResourceUsers(1);

		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_vertices;
		std::vector< glm::vec2 > temp_uvs;
		std::vector< glm::vec3 > temp_normals;

		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string err;
		std::string filedir = filepath.substr(0, filepath.find_last_of('/') + 1);
		tinyobj::LoadObj(shapes, materials, err, filepath.c_str(), filedir.c_str());

		if (!err.empty()) {
			Message(std::string("Error loading obj file. ").append(err), Engine::MessageType::Error);
		}

		res->setShapes(shapes);
		res->setMaterials(materials);
		
		_resources.push_back(res);
		return res;
	}
}