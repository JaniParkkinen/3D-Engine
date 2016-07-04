#ifndef Engine_3DEngine_hpp
#define Engine_3DEngine_hpp

//SYSTEM
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <process.h>
#include <math.h>
#include <memory>

//CORE
#include <Core/Message.hpp>

#include <Core/Window.hpp>
#include <Core/Window.cpp>

#include <Core/Time.hpp>
#include <Core/Time.cpp>

#include <Core/Buffer.hpp>
#include <Core/Buffer.cpp>

#include <Core/Input.hpp>
#include <Core/Input.cpp>

//MANAGERS
#include <Core/Managers/EntityManager.hpp>
#include <Core/Managers/EntityManager.cpp>

#include <Core/Managers/ResourceManager.hpp>
#include <Core/Managers/ResourceManager.cpp>

#include <Core/Managers/SystemManager.hpp>
#include <Core/Managers/SystemManager.cpp>

//SYSTEMS
#include <Core/Systems/PhysicsSystem.hpp>
#include <Core/Systems/PhysicsSystem.cpp>

#include <Core/Systems/RenderingSystem.hpp>
#include <Core/Systems/RenderingSystem.cpp>

//COMPONENTS
#include <Core/Components/AABB.hpp>
#include <Core/Components/AABB.cpp>

#include <Core/Components/Camera.hpp>
#include <Core/Components/Camera.cpp>

#include <Core/Components/LightSource.hpp>
#include <Core/Components/LightSource.cpp>

#include <Core/Components/Material.hpp>
#include <Core/Components/Material.cpp>

#include <Core/Components/Physics.hpp>
#include <Core/Components/Physics.cpp>

#include <Core/Components/Mesh.h>
#include <Core/Components/Mesh.cpp>

#include <Core/Components/NormalMap.hpp>
#include <Core/Components/NormalMap.cpp>

#include <Core/Components/Renderable.hpp>
#include <Core/Components/Renderable.cpp>

#include <Core/Components/Shader.hpp>
#include <Core/Components/Shader.cpp>

#include <Core/Components/Texture.hpp>
#include <Core/Components/Texture.cpp>

#include <Core/Components/Transform.hpp>
#include <Core/Components/Transform.cpp>

#endif