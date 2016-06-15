#include <Core/Managers/EntityManager.hpp>

namespace Engine {
	//ENTITY
	std::vector<std::shared_ptr<Component>> Entity::GetComponents() {
		return _components;
	};

	void Entity::AddChild(std::shared_ptr<Entity> child) {
		_children.push_back(child);
		child->_parent = std::shared_ptr<Entity>(shared_from_this());
	};

	//ENTITY MANAGER
	std::shared_ptr<Entity> EntityManager::AddEntity(std::string name, std::shared_ptr<Entity> entity) {
		_entities.insert(std::make_pair(name, entity));
		entity->SetName(name.c_str());
		entity->Init();
		return entity;
	};

	void EntityManager::RemoveEntity(std::string name) {
		_entities.find(name)->second->Cleanup();
		_entities.erase(name);
	};

	void EntityManager::Update(DeltaTime deltaTime) {
		for (auto it : _entities) {
			it.second->Update(deltaTime);
		};
	};

	void EntityManager::Clear() {
		while (!_entities.empty()) {
			_entities.begin()->second->Cleanup();
			_entities.erase(_entities.begin());
		};
	};

	std::shared_ptr<Entity> EntityManager::GetEntity(std::string name) {
		return _entities.find(name)->second;
	};

	std::vector<std::shared_ptr<Entity>> EntityManager::GetEntities() {
		std::vector<std::shared_ptr<Entity>> temp;
		for (auto it : _entities) {
			temp.push_back(it.second);
		};
		return temp;
	};

	std::vector<std::shared_ptr<Component>> EntityManager::GetComponents() {
		std::vector <std::shared_ptr<Component>> tempCompVec;
		for (auto it : _entities) {
			std::vector<std::shared_ptr<Component>> temp = it.second->GetComponents();
			tempCompVec.insert(tempCompVec.end(), temp.begin(), temp.end());
		};
		return tempCompVec;
	};

	std::vector<std::shared_ptr<Component>> EntityManager::GetComponents(std::string name) {
		std::vector <std::shared_ptr<Component>> tempCompVec;
		std::vector<std::shared_ptr<Component>> temp = _entities.find(name)->second->GetComponents();
		tempCompVec.insert(tempCompVec.end(), temp.begin(), temp.end());
		return tempCompVec;
	};

};