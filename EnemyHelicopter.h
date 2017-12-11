#ifndef ENEMYHELICOPTER_H 
#define ENEMYHELICOPTER_H

#include "Helicopter.h"
#include "EnemyProjectileManager.h"

namespace game {

	class EnemyHelicopter : public Helicopter {

	public:
		// Constructor
		EnemyHelicopter(EnemyProjectileManager *manager);

		// Destructor
		~EnemyHelicopter();

		void Update(void) override;
		void Update(glm::vec3 playerPosition) override;

	private:

		EnemyProjectileManager *projectileManager;
	};

} // namespace game

#endif
