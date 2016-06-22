#include <Core/Components/Material.hpp>

namespace Engine {
	void Material::Init( ) { };

	void Material::bind(GLuint shaderID)
	{
		for (size_t i = 0; i < _materials.size(); i++) {
			GLint location;
			location = glGetUniformLocation(shaderID, "ambient");
			if (location != -1)
			{
				glUniform3fv(location, 1, &_materials[i].ambient[0]);
			}
			location = glGetUniformLocation(shaderID, "diffuse");
			if (location != -1)
			{
				glUniform3fv(location, 1, &_materials[i].diffuse[0]);
			}
			location = glGetUniformLocation(shaderID, "specular");
			if (location != -1)
			{
				glUniform3fv(location, 1, &_materials[i].specular[0]);
			}
			location = glGetUniformLocation(shaderID, "transmittance");
			if (location != -1)
			{
				glUniform3fv(location, 1, &_materials[i].transmittance[0]);
			}
			location = glGetUniformLocation(shaderID, "emission");
			if (location != -1)
			{
				glUniform3fv(location, 1, &_materials[i].emission[0]);
			}
			location = glGetUniformLocation(shaderID, "shininess");
			if (location != -1)
			{
				glUniform3fv(location, 1, &_materials[i].shininess);
			}
			location = glGetUniformLocation(shaderID, "ior");
			if (location != -1)
			{
				glUniform3fv(location, 1, &_materials[i].ior);
			}
			location = glGetUniformLocation(shaderID, "dissolve");
			if (location != -1)
			{
				glUniform3fv(location, 1, &_materials[i].dissolve);
			}
		}
	}

	void Material::Cleanup( ) { };
};