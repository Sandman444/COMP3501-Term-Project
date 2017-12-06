#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <stdexcept>
#include <iostream>

#include "Ground.h"

namespace game{
	Ground::Ground(std::string object_name, std::string material_name, ResourceManager* resman) : DirectionalSceneNode("helicopter", object_name, material_name, resman) {
	
	}
	Ground::~Ground(){}
}