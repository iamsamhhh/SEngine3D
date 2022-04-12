#pragma once

#include "Internal/ComponentManager.hpp"
#include "Internal/EntityManager.hpp"
#include "Internal/SystemManager.hpp"
#include "Name.hpp"
#include "Types.h"
#include <memory>
#include <string>
namespace SEngine{
class ECS_Manager
{
public:

	static std::shared_ptr<ECS_Manager> ecsManager;

	void Init()
	{
		// Create pointers to each manager
		mComponentManager 	= std::make_unique<	SEngine_Internal::ComponentManager>();
		mEntityManager 		= std::make_unique<	SEngine_Internal::EntityManager>();
		mSystemManager 		= std::make_unique<	SEngine_Internal::SystemManager>();
	}


	// Entity methods
	Entity CreateEntity()
	{
		Entity entity = mEntityManager->CreateEntity();
		AddComponent<Name>(entity, Name {.name = "Entity(" + std::to_string(entity) + ")"});
		return entity;
	}

	Entity CreateEntity(std::string name)
	{
		Entity entity = mEntityManager->CreateEntity();
		AddComponent<Name>(entity, Name {.name = name});
		return entity;
	}

	void DestroyEntity(Entity entity)
	{
		mEntityManager->DestroyEntity(entity);

		mComponentManager->EntityDestroyed(entity);

		mSystemManager->EntityDestroyed(entity);
	}

	const char* GetTypeName(ComponentType id){
		return mComponentManager->GetTypeName(id);
	}

	uint32_t GetEntityCount(){
		return mEntityManager->GetEntityCount();
	}

	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		mComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return mComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return mComponentManager->GetComponentType<T>();
	}
	template<typename T>
	bool ComponentExistForEntity(Entity id){
		return mComponentManager->ComponentExistForEntity<T>(id);
	}

	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return mSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		mSystemManager->SetSignature<T>(signature);
	}

	Signature GetEntitySignature(Entity id){
		return mEntityManager->GetSignature(id);
	}

private:
	std::unique_ptr<SEngine_Internal::ComponentManager> mComponentManager;
	std::unique_ptr<SEngine_Internal::EntityManager> mEntityManager;
	std::unique_ptr<SEngine_Internal::SystemManager> mSystemManager;
};
}