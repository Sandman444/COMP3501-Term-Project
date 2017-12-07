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

	private:

		float gravity = 0.0005;
		float velocity = 0.001;
		float terminalVelocity = 0.08;
	};

} // namespace game

#endif