#ifndef Engine_ResourceManager_hpp
#define Engine_ResourceManager_hpp


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <Core/Components/Material.hpp>

#include <GLM/glm.hpp>

namespace Engine {
	enum eType
	{
		Text = 1,
		Audio = 2,
		Image = 3,
		Font = 4,
		OBJ = 5,
	};

	class Resource
	{
	public:
		Resource() {};
		~Resource() {};

		std::string filepath;
		eType type;
		std::string scope;
		int ID;
		std::vector<int> resourceUsers;

		Material* _material;
		std::vector < glm::vec3 >  _vertices;
		std::vector < glm::vec2 >  _uvs;
		std::vector < glm::vec3 >  _normals;

		std::vector < glm::uvec3 > _indices;

		void setTextData(std::string readFile) { textData = readFile; }
		void setImageData(std::vector<unsigned char> imageFile, unsigned width, unsigned height) { std::cout << "setting image data" << std::endl; imageData = imageFile; iHeight = height; iWidth = width; }
		std::string getTextData() { return textData; }
		std::vector<unsigned char> getImageData() { return imageData; }

		int iHeight, iWidth;
	private:
		std::string textData;
		std::vector<unsigned char> imageData;
	};

	class ResourceManager
	{
	public:

		static ResourceManager* GetInstance() {
			static ResourceManager ResMan;
			return &ResMan;
		};

		Resource* LoadResource(std::string filepath);
		void UnLoadResource(int ID);
		int GetResourceUsers(int ID);

	private:

		ResourceManager() {};
		~ResourceManager() {};

		ResourceManager(ResourceManager const&) {};
		void operator=(ResourceManager const&) {};

		std::vector<Resource*> _resources;
		std::vector<Resource*>::iterator _it;
		int ID_generator = 0;
		static ResourceManager* Instance;

		Resource* LoadTextResource(std::string filepath);
	};
};
#endif
