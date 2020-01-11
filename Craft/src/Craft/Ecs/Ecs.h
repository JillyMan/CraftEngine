#pragma once

#include <Craft/Ecs/Components/BaseComponents.h>

namespace Craft { namespace Ecs {
	class Ecs
	{
	private: 
	/*	static u32 counter;
		static std::map < u32, std::vector<BaseComponent*>> objectComponents;
		*/

	public:
		static u32 CreateEntity()
		{
//			return counter++;
		}

		static void AddComponent(u32 gameObjectId, BaseComponent* component)
		{
//			objectComponents[gameObjectId].push_back(component);
		}

		template<typename T>
		static T* GetComponentById(u32 gameObjectId)
		{
			return nullptr;
		}
	};

	//u32 Ecs::counter = 0;
	//std::map < u32, std::vector<BaseComponent*>> Ecs::objectComponents;

}}