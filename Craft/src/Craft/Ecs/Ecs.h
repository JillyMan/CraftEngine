#pragma once
namespace Craft { namespace Ecs {

	struct BaseComponent 
	{
		s32 ownderId;
		s32 componentId;
	};

}}