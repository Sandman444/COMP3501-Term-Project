#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "DirectionalSceneNode.h"

namespace game {

	class Projectile : public DirectionalSceneNode {

	public:
		// Constructor
		Projectile(glm::vec3 position, glm::vec3 forward);

		// Destructor
		~Projectile();

		void setActive(bool activeState);
		void setForward(glm::vec3 newForward);

		virtual void move();
		glm::mat4 Draw(Camera *camera, glm::mat4 parent_transf);

	protected:

		virtual void buildModel();

	private:

		std::string computeProjectileId();

		static int projectileId;

		SceneNode *projectileModel;

		float speed = 0.1f;
		bool active = true;
	};

} // namespace game

#endif