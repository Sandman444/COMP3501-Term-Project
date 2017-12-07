#ifndef GROUND_H 
#define GROUND_H

#include "DirectionalSceneNode.h"

namespace game {
	class Ground : public DirectionalSceneNode
	{
	public:
		Ground(std::string object_name, std::string material_name, std::string texture_name, ResourceManager* resman);
		~Ground();
	};
} //namespace game

#endif