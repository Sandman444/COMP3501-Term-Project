#ifndef LASER_H_
#define LASER_H_

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

	// Abstraction of the laser
	class Laser : public SceneNode {

	public:
		// Create laser from given resources
		Laser(glm::vec3 forward, const std::string name, const Resource *geometry, const Resource *material);

		// Destructor
		~Laser();

		// Update geometry configuration
		void Update(void);

	private:
		glm::vec3 forward_;
	}; // class Laser

} // namespace game

#endif // LASER_H_
