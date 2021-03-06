#ifndef Engine_RenderingSystem_hpp
#define Engine_RenderingSystem_hpp

#include <chrono>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <Core/Window.hpp>
#include <Core/Buffer.hpp>

#include <Core/Managers/SystemManager.hpp>

#include <Core/Components/AABB.hpp>
#include <Core/Components/Camera.hpp>
#include <Core/Components/Material.hpp>
#include <Core/Components/Renderable.hpp>
#include <Core/Components/Shader.hpp>
#include <Core/Components/Texture.hpp>
#include <Core/Components/Transform.hpp>

namespace Engine {
	class RenderingSystem : public System {
	public:
		RenderingSystem( Window* window, const char* vertexShaderPath = "Resources/Vert.txt", const char* fragmentShaderPath = "Resources/Frag.txt" )
			: _window( window ), System( RENDER ) { };

		virtual ~RenderingSystem( ) { };

		virtual void Init( ) override;
		virtual void Cleanup( ) override;

		virtual void Pause( ) override;
		virtual void Resume( ) override;

		virtual void Update( DeltaTime deltaTime ) override;

		void SetCamera( std::shared_ptr<Camera> cam ) { _cam = cam; };

	private:
		EntityManager* _entityManager;
		Window* _window;

		Buffer _vertexBuffer;
		Buffer _indiceBuffer;

		std::shared_ptr<Camera> _cam;
	};
};

#endif