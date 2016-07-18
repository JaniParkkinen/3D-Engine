#ifndef Engine_NormalMap_h
#define Engine_NormalMap_h

#include <GL/glew.h>

#include <Core/Time.hpp>
#include <Core/Managers/ResourceManager.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {
	class NormalMap : public Component {
	public:
		NormalMap(const char* source);

		virtual void Init() override;
		virtual void Cleanup() override;

		void Bind();
		void Unbind();
	private:
		GLuint texid;
	};
};
#endif