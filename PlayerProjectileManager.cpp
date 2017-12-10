#include <stdexcept>
#include <iostream>
#include <glm/gtx/intersect.hpp>

#include "scene_graph.h"
#include "PlayerProjectileManager.h"

namespace game {

	PlayerProjectileManager::PlayerProjectileManager() {
	}


	PlayerProjectileManager::~PlayerProjectileManager() {
	}

	void PlayerProjectileManager::setScene(SceneGraph *sceneGraph) {

		scene = sceneGraph;
	}

	void PlayerProjectileManager::update() {

		for (std::vector<Projectile*>::iterator projectile = projectiles.begin(); projectile != projectiles.end();) {

			bool collisionDetected = false;

			for (std::vector<SceneNode*>::iterator collideable = collideables.begin(); collideable != collideables.end(); ++collideable) {
				if (sphereCollision(*projectile, *collideable)) {
					collisionDetected = true;
					break;
				}
			}

			if ((*projectile)->isOutOfRange()) {
				collisionDetected = true;
			}

			if (!collisionDetected) {
				(*projectile)->move();
				++projectile;
			}
			else {
				(*projectile)->setActive(false);
				(*projectile)->getParent()->removeChild((*projectile)->GetName());
				projectile = projectiles.erase(projectile); // Remove from projectiles list
			}
		}

		for (std::vector<SceneNode*>::iterator collideable = collideables.begin(); collideable != collideables.end(); ++collideable) {
			if (laserOn && glm::intersectLineSphere(laserStart, laserEnd, (*collideable)->GetPosition(), (*collideable)->getBoundingSphereRadius(), glm::vec3(1.0), glm::vec3(1.0))) {
				std::cout << "coll" << std::endl;
			}
		}
	}

	bool PlayerProjectileManager::sphereCollision(SceneNode *projectile, SceneNode *collideable) {
		return glm::distance(projectile->GetPosition(), collideable->GetPosition()) < (projectile->getBoundingSphereRadius() + collideable->getBoundingSphereRadius());
	}

	void PlayerProjectileManager::spawnMissile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation) {
		Missile *newMissile;
		newMissile = new Missile(position, initialForward);
		scene->addNode(newMissile);
		newMissile->SetOrientation(orientation);
		projectiles.push_back(newMissile);
	}

	void PlayerProjectileManager::spawnBomb(glm::vec3 position) {
		Bomb *newBomb;
		newBomb = new Bomb(position);
		scene->addNode(newBomb);
		projectiles.push_back(newBomb);
	}


	void PlayerProjectileManager::addCollideable(SceneNode *collideable) {
		collideables.push_back(collideable);
	}

	void PlayerProjectileManager::setLaserStart(glm::vec3 point) {
		laserStart = point;
	}

	void PlayerProjectileManager::setLaserEnd(glm::vec3 point) {
		laserEnd = point;
	}

	void PlayerProjectileManager::setLaserOn(bool on) {
		laserOn = on;
	}


} // namespace game
