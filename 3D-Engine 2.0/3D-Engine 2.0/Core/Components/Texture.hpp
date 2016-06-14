#ifndef Engine_Texture_h
#define Engine_Texture_h

#include <GL/glew.h>
#include <Core/ResourceManager.hpp>

namespace Engine
{
	class Texture : public Component
	{
	public:
		Texture(const char* source);

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void BindTexture(GLint id);
		void RenderReflection();
	private:
		Resource* tex;
		GLuint texid;
	};
};
#endif