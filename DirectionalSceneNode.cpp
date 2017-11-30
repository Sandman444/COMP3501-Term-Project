#include <stdexcept>
#include <iostream>

#include "DirectionalSceneNode.h"

namespace game {

	DirectionalSceneNode::DirectionalSceneNode(const std::string name) : SceneNode(name) {

	}
	DirectionalSceneNode::DirectionalSceneNode(const std::string name, std::string object_name, std::string material_name, ResourceManager* resman) : SceneNode(name, object_name, material_name, resman) {

	}

	glm::vec3 DirectionalSceneNode::getForward(void) const {

		glm::vec3 current_forward = orientation_ * forward_;
		return current_forward;
	}


	glm::vec3 DirectionalSceneNode::getSide(void) const {

		glm::vec3 current_side = orientation_ * side_;
		return current_side;
	}


	glm::vec3 DirectionalSceneNode::getUp(void) const {

		glm::vec3 current_forward = orientation_ * forward_;
		glm::vec3 current_side = orientation_ * side_;
		glm::vec3 current_up = glm::cross(current_forward, current_side);
		current_up = glm::normalize(current_up);
		return current_up;
	}


	void DirectionalSceneNode::pitch(float angle) {

		glm::quat rotation = glm::normalize(glm::angleAxis(angle, getSide()));
		orientation_ = rotation * orientation_;
	}


	void DirectionalSceneNode::yaw(float angle) {

		glm::quat rotation = glm::normalize(glm::angleAxis(angle, getUp()));
		orientation_ = rotation * orientation_;
	}


	void DirectionalSceneNode::roll(float angle) {

		glm::quat rotation = glm::normalize(glm::angleAxis(angle, getForward()));
		orientation_ = rotation * orientation_;
	}


} // namespace game