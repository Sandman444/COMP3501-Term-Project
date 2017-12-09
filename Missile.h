#ifndef MISSILE_H
#define MISSILE_H

#include <ctime>

#include "Projectile.h"
#include "resource_manager.h"

namespace game {

	class Missile : public Projectile {
	
	static const int TIMER_INTERVAL = 4; //the amount of time until a new spline is created

	public:
		// Constructor
		Missile(glm::vec3 position, glm::vec3 forward);

		// Destructor
		~Missile();

		
		Projectile* convertToMissile(Projectile *projectile);
		void move();

	private:
		//spline stuff
		glm::vec3 p0, p1, p2, p3;
		float timer;
		clock_t startTime;
		bool timerStarted;
	};

} // namespace game

#endif
