#include <stdexcept>
#include <iostream>
#include <glm/gtx/intersect.hpp>

#include "scene_graph.h"
#include "ProjectileManager.h"

namespace game {

	ProjectileManager::ProjectileManager() {
	}


	ProjectileManager::~ProjectileManager() {
	}

	void ProjectileManager::setScene(SceneGraph *sceneGraph) {

		scene = sceneGraph;
	}

	void ProjectileManager::update() {

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

	bool ProjectileManager::sphereCollision(SceneNode *projectile, SceneNode *collideable) {
		return glm::distance(projectile->GetPosition(), collideable->GetPosition()) < (projectile->getBoundingSphereRadius() + collideable->getBoundingSphereRadius());
	}

	void ProjectileManager::spawnMissile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation) {
		Missile *newMissile;
		newMissile = new Missile(position, initialForward);
		scene->addNode(newMissile);
		newMissile->SetOrientation(orientation);
		projectiles.push_back(newMissile);
	}

	void ProjectileManager::spawnBomb(glm::vec3 position) {
		Bomb *newBomb;
		newBomb = new Bomb(position);
		scene->addNode(newBomb);
		projectiles.push_back(newBomb);
	}


	void ProjectileManager::addCollideable(SceneNode *collideable) {
		collideables.push_back(collideable);
	}

	void ProjectileManager::setLaserStart(glm::vec3 point) {
		laserStart = point;
	}

	void ProjectileManager::setLaserEnd(glm::vec3 point) {
		laserEnd = point;
	}

	void ProjectileManager::setLaserOn(bool on) {
		laserOn = on;
	}


} // namespace game
