#ifndef DIRECTIONALSCENENODE_H_
#define DIRECTIONALSCENENODE_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "scene_node.h"

namespace game {

	class DirectionalSceneNode : public SceneNode {

	public:
		
		DirectionalSceneNode(const std::string name);
		DirectionalSceneNode(const std::string name, std::string object_name, std::string material_name, std::string texture_name);

		// Get relative attributes of node
		glm::vec3 getForward(void) const;
		glm::vec3 getSide(void) const;
		glm::vec3 getUp(void) const;

		// Perform relative transformations of node
		void pitch(float angle);
		void yaw(float angle);
		void roll(float angle);

	protected:
		glm::vec3 forward_; // Initial forward vector
		glm::vec3 side_; // Initial side vector

	};

} // namespace game

#endif
