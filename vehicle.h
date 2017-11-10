#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "resource.h"
#include "scene_node.h"

namespace game {

	// Abstraction of an asteroid
	class Vehicle : public SceneNode {

	public:
		// Create asteroid from given resources
		Vehicle(const std::string name, const Resource *geometry, const Resource *material);

		// Destructor
		~Vehicle();

		// Update geometry configuration
		void Update(void);

	}; // class Asteroid

} // namespace game

#endif // ASTEROID_H_
