#include "BarrierGroup.hpp"

BarrierGroup::BarrierGroup() {
	for (auto coord : COORDS) {
		barrierVector.emplace_back(coord.first * 8, coord.second * 8 - 4);
	}
}

bool BarrierGroup::testOneForCollision(GameObject* obj, bool deleteMine) {
	for (auto barrier = barrierVector.begin(); barrier < barrierVector.end(); barrier++) {
		if (barrier->testCollision(*obj)) {
			if (deleteMine) {
				barrierVector.erase(barrier--);
			}
			return true;
		}
	}
	return false;
}

bool BarrierGroup::testManyForCollisionWithBaddieBullet(vector<BaddieBullet>& objs, bool deleteMine, bool deleteTheirs) {
	for (auto obj = objs.begin(); obj < objs.end(); obj++) {
		if (testOneForCollision(&(*obj), deleteMine)) {
			if (deleteTheirs) {
				objs.erase(obj--);
			}
			return true;
		}
	}
	return false;
}

void BarrierGroup::animateIntro(int framesElapsed) {
	for (auto barrier = barrierVector.begin(); barrier < barrierVector.end(); barrier++) {
		Vector2f start = barrier->startingPosition;
		Vector2f destination = barrier->destination;
		float percentage = ((float)framesElapsed) / 330;
		barrier->setPosition(util::tween(start, destination, percentage));
	}
}

void BarrierGroup::draw(RenderWindow& window) {
	for (Barrier& barrier : barrierVector) {
		barrier.draw(window);
	}
}

BarrierGroup::~BarrierGroup() {}
