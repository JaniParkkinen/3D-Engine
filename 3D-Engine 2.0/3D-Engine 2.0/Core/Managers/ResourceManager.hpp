#ifndef Resourcemanager_h
#define Resourcemanager_h
#include <Core/Resource.h>
#include <map>
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
		Resource* FindResourceByID(unsigned ID);
		//void Clear();
		void SetCurrentScope(unsigned scope);
		const unsigned GetResourceCount() const { return resourceCount; }

		static ResourceManager* GetInstance() {return instance;};
		ResourceManager* LoadResource(std::string filepath);
		void unLoadResource(int ID);
		int GetResourceUsers(int ID);
		//irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();

	protected:
		unsigned currentScope;
		unsigned resourceCount;
		std::map<unsigned, std::list<Resource*>> _resources;
	
	private:
		ResourceManager(ResourceManager const&);
		void operator=(ResourceManager const&);

		std::vector<Resource*> _resources;
		std::vector<Resource*>::iterator _it;
		int ID_generator = 0;
		static ResourceManager* instance;
		//irrklang::ISoundSource* source;

		Resource* LoadTextResource(std::string filepath);
		Resource* LoadImageResource(std::string filepath);
		Resource* LoadAudioResource(std::string filepath);
		Resource* LoadFontResource(std::string filepath);
		Resource* LoadObjectResource(std::string filepath);
	};
}

#endif