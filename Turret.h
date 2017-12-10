#ifndef TURRET_H 
#define TURRET_H

#include "DirectionalSceneNode.h"
#include "EnemyProjectileManager.h"

namespace game {

	class Turret : public DirectionalSceneNode {

	public:
		// Constructor
		Turret(EnemyProjectileManager *manager);

		// Destructor
		~Turret();

		void Update(glm::vec3 playerPosition) override;

		void turnLeft();
		void turnRight();

		float getLevel();
		float getBoundingSphereRadius(void) const override;

	private:

		EnemyProjectileManager *projectileManager;
		SceneNode *body, *gun_housing, *barrel;

		glm::vec3 velocity;
		glm::vec3 accelerationDirection;
		float accelerationSpeed;

		float turnVelocity = 0;
		int turnDirection = 0;
		float turnSpeed;
	};

} // namespace game

#endif