#ifndef SPLINEMISSILE_H
#define SPLINEMISSILE_H

#include <ctime>

#include "Missile.h"

namespace game {
	class SplineMissile : public Missile {
		const static int TIMER_INTERVAL = 4;
	public:
		// Constructor
		SplineMissile(std::string material, glm::vec3 position, glm::vec3 forward, glm::vec3 target);

		// Destructor
		~SplineMissile();

		void move();

	private:
		glm::vec3 target_;

	private:
		//spline stuff
		glm::vec3 p0, p1, p2, p3;
		float timer;
		clock_t startTime;
		bool timerStarted;
	};

} // namespace game

#endif
