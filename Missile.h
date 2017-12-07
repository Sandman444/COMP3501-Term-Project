#ifndef MISSILE_H
#define MISSILE_H

#include "Projectile.h"

namespace game {

	class Missile : public Projectile {

	public:
		// Constructor
		Missile(glm::vec3 position, glm::vec3 forward);

		// Destructor
		~Missile();

		Projectile* converToMissile(Projectile *projectile);

	private:

	};

} // namespace game

#endif
