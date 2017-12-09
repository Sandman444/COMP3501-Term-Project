#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "DirectionalSceneNode.h"

namespace game {

	class Projectile : public DirectionalSceneNode {

	public:
		// Constructor
		Projectile();
		Projectile(glm::vec3 position, glm::vec3 forward);

		// Destructor
		~Projectile();

		void setActive(bool activeState);
		void setForward(glm::vec3 newForward);
		void setSpeed(float speed);

		virtual void move();
		glm::mat4 Draw(Camera *camera, glm::mat4 parent_transf) override;

		void SetPosition(glm::vec3 position);
		float getBoundingSphereRadius(void) const override;
		bool isOutOfRange();

		SceneNode *projectileModel, *projectileEffect;


	protected:

		float speed = 0.2f;

	private:

		std::string computeProjectileId();

		static int projectileId;

		glm::vec3 startingPosition;
		float activeRange = 45.0;
		bool active = true;
	};

} // namespace game

#endif