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
		glm::mat4 Draw(Camera *camera, glm::mat4 parent_transf) override;

		void SetPosition(glm::vec3 position);
		float getBoundingSphereRadius(void) const override;
		bool isOutOfRange();


	protected:

		virtual void buildModel();

	private:

		std::string computeProjectileId();

		static int projectileId;

		SceneNode *projectileModel;

		glm::vec3 startingPosition;
		float speed = 0.2f;
		float activeRange = 45.0;
		bool active = true;
	};

} // namespace game

#endif