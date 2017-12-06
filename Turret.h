#ifndef TURRET_H 
#define TURRET_H

#include "DirectionalSceneNode.h"

namespace game {

	class Turret : public DirectionalSceneNode {

	public:
		// Constructor
		Turret(ResourceManager* resman);

		// Destructor
		~Turret();

		void Update(void) override;

		void turnLeft();
		void turnRight();

	private:
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