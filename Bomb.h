#ifndef BOMB_H
#define BOMB_H

#include "Projectile.h"

namespace game {

	class Bomb : public Projectile {

	public:
		// Constructor
		Bomb(glm::vec3 position);

		// Destructor
		~Bomb();

		void move() override;
		float getBoundingSphereRadius(void) const override;
		bool isOutOfRange() override;

	private:

		SceneNode *explosionEffect;

		bool exploding = false;
		bool doneExploding = false;
		double explosionTimer = 0;
		double explosionDuration = 2.0;

		float gravity = 0.0005;
		float velocity = 0.001;
		float terminalVelocity = 0.08;
	};

} // namespace game

#endif