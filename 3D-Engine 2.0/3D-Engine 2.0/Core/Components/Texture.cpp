#include <Core/Components/Texture.hpp>

namespace Engine {

	Texture::Texture(const char* source)
	{
		//tex = ResourceManager::GetInstance()->LoadResource(source);

		// Create one OpenGL texture
		glGenTextures(1, &texid);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, texid);

		// Give the image to OpenGL
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->iWidth, tex->iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &tex->getImageData()[0]);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	};

	void Texture::Init() {};

	void Texture::Cleanup() {};

	void Texture::Update(DeltaTime deltaTime) {};

	void Texture::BindTexture(GLint id) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texid);
	};
};