#include <Core/Components/NormalMap.hpp>

namespace Engine {

	NormalMap::NormalMap(const char* source) : Component(NORMALMAP) {
		std::shared_ptr<Engine::Resource> tex = ResourceManager::GetInstance()->LoadResource(source);

		// Create one OpenGL texture
		glGenTextures(1, &texid);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, texid);

		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->getImageData().size.x, tex->getImageData().size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &tex->getImageData().imageData[0]);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	void NormalMap::Init() { }

	void NormalMap::Cleanup() { }

	void NormalMap::Bind() {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texid);
	}

	void NormalMap::Unbind() {
		glDisable(GL_TEXTURE_2D);
	}
}