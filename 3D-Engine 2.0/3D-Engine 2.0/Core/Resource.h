#ifndef Resource_H
#define Resource_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <GLM/glm.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tinyobjloader.h>

//http://gamedev.stackexchange.com/questions/17066/designing-a-resourcemanager-class/17082#17082
namespace Engine {
	typedef enum class Resource_Type
	{
		Resource_Null = 0,
		Resource_Image = 1,
		Resource_Font = 2,
		Resource_Audio = 3,
		Resource_Text = 4,
		Resource_Obj = 5,
		Resource_Fbx = 6,
	}Resource_Type;

	struct Image {
		std::vector<unsigned char> imageData;
		glm::uvec2 size;
	};

	class Resource //: public EngineObject
	{
	public:
		Resource() : resourceID(0), _scope(0), _type(Resource_Type::Resource_Null) {}
		~Resource() {}

		void Load();
		void Unload();
		void setTextData(std::string readFile) { textData = readFile; }
		void setImageData(Image img) { _image = img; }
		//void setAudioData(irrklang::ISoundSource* audioFile) { std::cout << "Setting audio data " << std::endl; audioData = audioFile; }
		//void setAudioEngine(irrklang::ISoundEngine* engine) { audio->setEngine(engine); }
		//void setAudio(std::string filename) { audio->includeAudio(filename); }
		void pushResourceUsers(int i) { resourceUsers.push_back(i); };
		void popResourceUsers() { resourceUsers.pop_back(); }
		void setType(Resource_Type type) { _type = type; }

		void setFilePath(std::string filepath) { this->filepath = filepath; }
		void setShapes(std::vector<tinyobj::shape_t> shapes) { _shapes.insert(_shapes.begin(), shapes.begin(), shapes.end()); }
		void setMaterials(std::vector<tinyobj::material_t> materials) { _materials.insert(_materials.begin(), materials.begin(), materials.end()); }
		bool setID(unsigned id) { resourceID = id; return true; }
		
		Image getImageData() { return _image; }
		std::vector<tinyobj::shape_t> getShapes() { return _shapes; }
		std::vector<tinyobj::material_t> getMaterial() { return _materials; }

		std::string getFilePath() { return filepath; }
		std::string getTextData() { return textData; }
		
		int sizeResourceUsers() { return resourceUsers.size(); }

	protected:
		std::string filepath;
		std::string _filename;
		Resource_Type _type;
		unsigned _scope;
		unsigned resourceID;
		std::vector<int> resourceUsers;
		bool _loaded;
		//int iHeight, iWidth;
		std::vector<tinyobj::shape_t> _shapes;
		std::vector<tinyobj::material_t> _materials;
		
	private:
		std::string textData;
		Image _image;
		//std::vector<unsigned char> imageData;
		
	};
}

#endif // !Resource_H