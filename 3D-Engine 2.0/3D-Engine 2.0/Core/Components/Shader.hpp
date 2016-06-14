#ifndef Engine_Shader_hpp
#define Engine_Shader_hpp

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/GL.h>

#include <Core/Time.hpp>
#include <Core/ResourceManager.h>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {
	enum class eValue
	{
		UNIFORM_MAT4,
		UNIFORM_VEC2,
		UNIFORM_VEC3,
		UNIFORM_VEC4,
		UNIFORM_FLOAT
	};

	struct Binding
	{
		Binding(std::string name, void* value, eValue type) : _name(name), _value(value), _type(type) {};
		std::string _name;
		void* _value;
		eValue _type;
	};

	class Shader : public Component
	{
	public:
		Shader(const char* vertexSource, const char* fragmentSource);
		Shader();
		virtual ~Shader();

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void CompileShader(const char* source, GLenum shaderType);

		void SetBinding(std::string name, void* value, eValue type);
		void BindShader();

		GLuint GetProgramID() { return _programID; }

	private:
		GLuint _programID;

		std::vector<Binding*> _bindings;
	};
};

#endif