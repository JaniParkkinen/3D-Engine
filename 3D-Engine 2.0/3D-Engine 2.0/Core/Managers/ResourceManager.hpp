#ifndef Resourcemanager_h
#define Resourcemanager_h
#include <Core/Resource.h>
#include <string>
#include <iostream>
#include <vector>

namespace Engine {
		class ResourceManager
		{
		public:

			static ResourceManager* GetInstance() {
				static ResourceManager resourceManager;
				return &resourceManager;
			}

			std::shared_ptr<Resource> LoadResource(std::string filepath);
			void unLoadResource(int ID);
			int GetResourceUsers(int ID);
			//irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();

		private:

			ResourceManager() {}

			ResourceManager( ResourceManager const& );
			void operator=( ResourceManager const& );

			std::vector<std::shared_ptr<Resource>> _resources;
			std::vector<std::shared_ptr<Resource>>::iterator _it;
			int ID_generator = 0;
			//irrklang::ISoundSource* source;

			std::shared_ptr<Resource> LoadTextResource(std::string filepath);
			std::shared_ptr<Resource> LoadImageResource(std::string filepath);
			std::shared_ptr<Resource> LoadAudioResource(std::string filepath);
			std::shared_ptr<Resource> LoadFontResource(std::string filepath);
			std::shared_ptr<Resource> LoadObjectResource(std::string filepath);
			//void dropSoundEngine() { soundEngine->drop(); }; //ft snoop dogg

	};
}

#endif