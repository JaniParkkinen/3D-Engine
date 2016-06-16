#include <Core/Managers/ResourceManager.hpp>
#include <iostream>
#include <Windows.h>
#include <lodepng/lodepng.h>
#include <lodepng/lodepng.cpp>
#include <Core/Components/Material.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>

namespace Engine {

	ResourceManager* ResourceManager::instance = nullptr;

	ResourceManager* ResourceManager::GetInstance()
	{
		if (instance == nullptr)
		{
			std::cout << "Creating a new resource manager. " << std::endl;
			instance = new ResourceManager;

		}
		return instance;
	}
	std::shared_ptr<Resource> ResourceManager::LoadResource(std::string filepath)
	{
		try {
			for (auto i : _resources)
			{
				if (i->getFilePath() == filepath)
				{
					std::cout << "resource already loaded" << std::endl;
					i->pushResourceUsers(1);
					
					return i;
				}
			}

			std::shared_ptr<Resource> res = nullptr;
			
			//TextFile
			if (filepath.substr(filepath.size() - 4) == ".txt" || filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
			{
				if (filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
				{
					std::cout << "Loading shader file" << std::endl;
					// load shader file
				}
				std::cout << "A text file" << std::endl;
				res = ResourceManager::LoadTextResource(filepath);
				return res;
			}
			//ImageFile
			else if (filepath.substr(filepath.size() - 4) == ".png")
			{
				std::cout << "An image file" << std::endl;
				res = ResourceManager::LoadImageResource(filepath);
				return res;
			}
			//AudioFile
			else if (filepath.substr(filepath.size() - 4) == ".wav")
			{
				std::cout << "An audio file" << std::endl;
				res = ResourceManager::LoadAudioResource(filepath);

				return res;
			}
			//FontFile
			else if (filepath.substr(filepath.size() - 4) == ".ttf")
			{
				std::cout << "a font file" << std::endl;


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
				std::cout << "An object file" << std::endl;
				res = ResourceManager::LoadObjectResource(filepath);

				return res;
			}
			//UnknownFile
			else
			{
				std::cout << "filetype not regognized" << std::endl;
				return 0;
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
				std::cout << "Deleting resource" << std::endl;
				(*_it)->popResourceUsers();
				if ((*_it)->sizeResourceUsers() <= 0)
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
	}
	int ResourceManager::GetResourceUsers(int ID)
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
		std::cout << "Resource not found" << std::endl;
		return 0;
	}

	std::shared_ptr<Resource> ResourceManager::LoadTextResource(std::string filepath)
	{
		std::cout << "Loading Resource" << std::endl;
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
		_resources.push_back(res);
		return res;
	}
	std::shared_ptr<Resource> ResourceManager::LoadImageResource(std::string filepath)
	{

		std::cout << "Loading resource" << std::endl;
		unsigned width, height;

		std::shared_ptr<Resource> res = std::make_shared<Resource>();
		res->setFilePath(filepath);
		res->setType(Resource_Type::Resource_Image);
		res->setID(++ID_generator);
		res->pushResourceUsers(1);

		std::vector<unsigned char> image;
		unsigned error = lodepng::decode(image, width, height, filepath);

		res->setImageData(image, width, height);

		_resources.push_back(res);
		return res;
	}
	std::shared_ptr<Resource> ResourceManager::LoadAudioResource(std::string filepath)
	{
		std::cout << "Loading Resource" << std::endl;

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
		std::cout << "Loading Resource" << std::endl;

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

		std::cout << "Loading Resource" << std::endl;

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
			std::cout << err << std::endl;
		}

		//!shapes->texcoordinates.empty()
		
		//for (size_t i = 0; i < shapes.size(); i++) {
		//	size_t offset = res->_vertices.size();
		//	for (size_t j = 0; j < shapes[i].mesh.positions.size() / 3; j++)
		//	{
		//		res->_vertices.push_back(glm::vec3(shapes[i].mesh.positions[3 * j + 0], shapes[i].mesh.positions[3 * j + 1], shapes[i].mesh.positions[3 * j + 2]));
		//		res->_vertices.push_back(glm::vec3(shapes[i].mesh.texcoords[2 * j + 0], shapes[i].mesh.texcoords[2 * j + 1], 0.0f));
		//		res->_vertices.push_back(glm::vec3(shapes[i].mesh.normals[3 * j + 0], shapes[i].mesh.normals[3 * j + 1], shapes[i].mesh.normals[3 * j + 2]));
		//	}
		//	for (size_t j = 0; j < shapes[i].mesh.indices.size() / 3; j++) {
		//		res->_indices.push_back(glm::uvec3(shapes[i].mesh.indices[3 * j + 0] + offset, shapes[i].mesh.indices[3 * j + 1] + offset, shapes[i].mesh.indices[3 * j + 2] + offset));
		//	}
		//}


		//for (size_t i = 0; i < materials.size(); i++) {
		//	res->_material = new Engine::Material(glm::vec3(materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]),
		//		glm::vec3(materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]),
		//		glm::vec3(materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]),
		//		glm::vec3(materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]),
		//		glm::vec3(materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]),
		//		materials[i].ior, materials[i].shininess, materials[i].dissolve, materials[i].illum, materials[i].dummy);
		//}

		_resources.push_back(res);
		return res;
	}
}