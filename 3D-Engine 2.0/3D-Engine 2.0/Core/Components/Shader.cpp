#include <Core/Components/Shader.hpp>

namespace Engine {
	Shader::Shader( const char* vertexSource, const char* fragmentSource ) :  Component( SHADER ) {
		_programID = glCreateProgram( );

		CompileShader( vertexSource, GL_VERTEX_SHADER );
		CompileShader( fragmentSource, GL_FRAGMENT_SHADER );

		GLAssert( );
	};

	Shader::~Shader( ) { };

	void Shader::Init( ) { };

	void Shader::Cleanup( ) {
		glDeleteShader( _programID );
	};

	void Shader::CompileShader( const char* source, GLenum shaderType ) {
		std::shared_ptr<Resource> shader = ResourceManager::GetInstance()->LoadResource(source);

		std::string temp = shader->getTextData();
		const char* fuck = temp.c_str();

		GLuint shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &fuck, 0);

		glCompileShader(shaderID);

		glAttachShader(_programID, shaderID);

		glLinkProgram(_programID);
	};

	void Shader::SetBinding( std::string name, void* value, eValue type ) {
		_bindings.push_back( new Binding( name, value, type ) );
	};

	void Shader::BindShader( ) {
		for ( Binding* binding : _bindings ) {
			GLint location;
			switch ( binding->_type ) {
				case eValue::UNIFORM_MAT4:
				{
					location = glGetUniformLocation( _programID, binding->_name.c_str( ) );
					if ( location != -1 ) {
						glUniformMatrix4fv( location, 1, GL_FALSE, ( GLfloat* )binding->_value );
					};
					break;
				};
				case eValue::UNIFORM_VEC2:
				{
					location = glGetUniformLocation( _programID, binding->_name.c_str( ) );
					if ( location != -1 ) {
						glUniform2fv( location, 1, ( GLfloat* )binding->_value );
					};
					break;
				};
				case eValue::UNIFORM_VEC3:
				{
					location = glGetUniformLocation( _programID, binding->_name.c_str( ) );
					if ( location != -1 ) {
						glUniform3fv( location, 1, ( GLfloat* )binding->_value );
					};
					break;
				};
				case eValue::UNIFORM_VEC4:
				{
					location = glGetUniformLocation( _programID, binding->_name.c_str( ) );
					if ( location != -1 ) {
						glUniform3fv( location, 1, ( GLfloat* )binding->_value );
					};
					break;
				};
				case eValue::UNIFORM_FLOAT:
				{
					location = glGetUniformLocation( _programID, binding->_name.c_str( ) );
					if ( location != -1 ) {
						glUniform1fv( location, 1, ( GLfloat* )binding->_value );
					};
					break;
				};
				default:
				{
					break;
				};
			};
		};
	};
};