#pragma once

#include "Internal/ComponentManager.hpp"
#include "Internal/EntityManager.hpp"
#include "Internal/SystemManager.hpp"
#include "Types.h"
#include <memory>
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
		return mEntityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity)
	{
		mEntityManager->DestroyEntity(entity);

		mComponentManager->EntityDestroyed(entity);

		mSystemManager->EntityDestroyed(entity);
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

private:
	std::unique_ptr<SEngine_Internal::ComponentManager> mComponentManager;
	std::unique_ptr<SEngine_Internal::EntityManager> mEntityManager;
	std::unique_ptr<SEngine_Internal::SystemManager> mSystemManager;
};
}