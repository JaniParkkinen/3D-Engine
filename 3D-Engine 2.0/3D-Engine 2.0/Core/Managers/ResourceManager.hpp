#ifndef Resourcemanager_h
#define Resourcemanager_h
#include <Core/Resource.h>

#include <iostream>
#include <vector>
//#include "Resource.h"
//#include "..\..\Dependencies\include\irrKlang\irrKlang.h"

namespace Engine {
	class ResourceManager
	{
	public:
		ResourceManager() : currentScope(0), resourceCount(0) {};
		virtual ~ResourceManager();

	};
}




//class ResourceManager
//{
//public:
//
//	static ResourceManager* GetInstance();
//	ResourceManager* LoadResource(std::string filepath);
//	//Resource* LoadResource(std::string filepath);
//	void UnLoadResource(int ID);
//	int GetResourceUsers(int ID);
//	//irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
//
//private:
//
//	ResourceManager() {};
//	~ResourceManager() {};
//
//	ResourceManager(ResourceManager const&);
//	void operator=(ResourceManager const&);
//
//	//std::vector<Resource*> _resources;
//	//std::vector<Resource*>::iterator _it;
//	int ID_generator = 0;
//	static ResourceManager* Instance;
//	//irrklang::ISoundSource* source;
//
//	//Resource* LoadTextResource(std::string filepath);
//	//Resource* LoadImageResource(std::string filepath);
//	//Resource* LoadAudioResource(std::string filepath);
//	//Resource* LoadFontResource(std::string filepath);
//	//Resource* LoadObjectResource(std::string filepath);
//	//void dropSoundEngine() { soundEngine->drop(); }; //ft snoop dogg
//
//};

#endif