#include "BaddieGroup.hpp"

/* Builds all baddies and assigns texture based off the row its in
*/
BaddieGroup::BaddieGroup(ParticleGroup& particleGroup)
	: particleGroup(particleGroup)
{
	Texture* textureArray[ROWS];
	textureArray[0] = &resources::textures["invader3"];
	textureArray[1] = &resources::textures["invader2"];
	textureArray[2] = &resources::textures["invader1"];
	baddiepew.setBuffer(resources::soundFile["baddiepew"]);
	baddieMoveOne.setBuffer(resources::soundFile["baddiemove1"]);
	baddieMoveTwo.setBuffer(resources::soundFile["baddiemove2"]);
	baddieDeath.setBuffer(resources::soundFile["baddieboom"]);
	baddiesAdvanceSound.setBuffer(resources::soundFile["baddieadvance"]);

	for (int x = 0; x < COLUMNS; x++) {
		for (int y = 0; y < ROWS; y++) {
			baddies[x][y] = new Baddie(*textureArray[y], 0, 0);
			baddies[x][y]->speed += score::speedModifier;
		}
	}
}

bool BaddieGroup::isBaddiesAdvance() {
	if (allMoveRight) {
		/*
		18 15 12  9  6  3  0
		19 16 13 10  7  4  1
		20 17 14 11  8  5  2
		*/
		for (int x = COLUMNS - 1; x >= 0; x--) {
			for (int y = 0; y < ROWS; y++) {
				if (baddies[x][y] && !baddies[x][y]->eesComing) {
					baddiesSpeed = baddies[x][y]->speed;
					return (baddies[x][y]->getX() >= 120 + 4);
				}
			}
		}
	} else {
		/*
		0  3  6  9 12 15 18
		1  4  7 10 13 16 19
		2  5  8 11 14 17 20
		*/
		for (int x = 0; x < COLUMNS; x++) {
			for (int y = 0; y < ROWS; y++) {
				if (baddies[x][y] && !baddies[x][y]->eesComing) {
					baddiesSpeed = baddies[x][y]->speed;
					return (baddies[x][y]->getX() <= 0 + 4);
				}
			}
		}
	}
	return false;
}

void BaddieGroup::moveBaddiesSound() {
	// could use a multiplier on BaddieMoveTimer that would allow the timer to speed up as they move faster
	// the baddie speed is up to date and kept in baddiesSpeed
	if (baddieMoveSwap && baddieMoveTimerBuffer >= baddieMoveTimer) {
		baddieMoveOne.play();
		baddieMoveTimerBuffer = 0;
		baddieMoveSwap = false;
		return;
	} else if (!baddieMoveSwap && baddieMoveTimerBuffer >= baddieMoveTimer) {
		baddieMoveTwo.play();
		baddieMoveTimerBuffer = 0;
		baddieMoveSwap = true;
		return;
	}
	baddieMoveTimerBuffer++;
}

void BaddieGroup::moveBaddies() {
	for (int x = 0; x < COLUMNS; x++) {
		for (int y = 0; y < ROWS; y++) {
			if (baddies[x][y]) {
				baddies[x][y]->update();
			}
		}
	}
	if (isBaddiesAdvance()) {
		shakeSpeed += 0.1f;
		allMoveRight = !allMoveRight;
		score::scoreBonus--;
		baddiesTimesAdvanced++;
		baddiesAdvanceSound.play();
		// order is irrelevant
		for (int x = 0; x < COLUMNS; x++) {
			for (int y = 0; y < ROWS; y++) {
				if (baddies[x][y] && !baddies[x][y]->eesComing) {
					baddies[x][y]->moveDown();
				}
			}
		}
	} else {
		// order is irrelevant
		for (int x = 0; x < COLUMNS; x++) {
			for (int y = 0; y < ROWS; y++) {
				if (baddies[x][y] && !baddies[x][y]->eesComing) {
					if (allMoveRight) {
						baddies[x][y]->moveRight();
					} else {
						baddies[x][y]->moveLeft();
					}
				}
			}
		}
	}
}

void BaddieGroup::accelerateBaddies() {
	while (baddiesKilledThisFrame > 0) {
		// order irrelevant
		for (int x = 0; x < COLUMNS; x++) {
			for (int y = 0; y < ROWS; y++) {
				if (baddies[x][y]) {
					baddies[x][y]->speed += (SPEED_MULT * MAX_BADDIES) / currentBaddies;
				}
			}
		}
		baddiesKilledThisFrame--;
		currentBaddies--;
		chooseBaddieCuss();
	}
}

void BaddieGroup::chooseBaddieCuss() {
	int chooseBaddie = util::rangedRand(0, currentBaddies - 1);
	int selectBuffer = 0;
	for (int x = 0; x < COLUMNS; x++) {
		for (int y = 0; y < ROWS; y++) {
			if (!baddies[x][y]) continue;
			if (selectBuffer == chooseBaddie) {
				particleGroup.createParticleText(util::cuss(), baddies[x][y]->getPosition(), Color::Red);
				return;
			} else {
				selectBuffer++;
			}
		}
	}
}

void BaddieGroup::baddieShoot() {
	if (shootTimer > SHOOT_DELAY) {
		randomColumn = util::rangedRand(0, COLUMNS - 1);
		// Bottom-up
		for (int y = ROWS - 1; y >= 0; y--) {
			if (baddies[randomColumn][y]) {
				float bulletX = baddies[randomColumn][y]->getX() + -1.f;
				float bulletY = baddies[randomColumn][y]->getY() + 4.f;
				bulletVector.emplace_back(BaddieBullet(bulletX, bulletY));
				shootTimer = 0;
				baddiepew.play();
				return;
			}
		}
	}
	shootTimer++;
	return;
}

void BaddieGroup::bulletUpdate() {
	for (auto bullet = bulletVector.begin(); bullet < bulletVector.end(); bullet++) {
		bullet->update();
		if (bullet->isOffScreen()) {
			bulletVector.erase(bullet--);
		}
	}
}

void BaddieGroup::deleteBaddie(int x, int y) {
	delete baddies[x][y];
	baddies[x][y] = nullptr;
	baddieDeath.play();
}

void BaddieGroup::baddieOffScreen() {
	for (int y = ROWS - 1; y >= 0; y--) {
		for (int x = COLUMNS - 1; x >= 0; x--) {
			if (baddies[x][y] && baddies[x][y]->getY() > defines::HEIGHT) {
				deleteBaddie(x, y);
				baddiesKilledThisFrame++;
			}
		}
	}
}

void BaddieGroup::forceKami() {
	for (int y = ROWS - 1; y >= 0; y--) {
		for (int x = COLUMNS - 1; x >= 0; x--) {
			if (baddies[x][y]) {
				baddies[x][y]->ohHeMad = true;
				return;
			}
		}
	}
}

bool BaddieGroup::testOneForCollision(GameObject* obj, bool deleteMine) {
	if (allMoveRight) {
		/*
		20 19 18 17 16 15 14
		13 12 11 10  9  8  7
		 6  5  4  3  2  1  0
		*/
		for (int y = ROWS - 1; y >= 0; y--) {
			for (int x = COLUMNS - 1; x >= 0; x--) {
				if (baddies[x][y]) {
					if (baddies[x][y]->testCollision(*obj)) {
						if (deleteMine) {
							particleGroup.createParticleText("+100", baddies[x][y]->getPosition(), Color::Cyan);
							deleteBaddie(x, y);
							baddiesKilledThisFrame++;
						}
						return true;
					}
				}
			}
		}
	} else {
		/*
		14 15 16 17 18 19 20
		 7  8  9 10 11 12 13
		 0  1  2  3  4  5  6
		*/
		for (int y = ROWS - 1; y >= 0; y--) {
			for (int x = 0; x < COLUMNS; x++) {
				if (baddies[x][y]) {
					if (baddies[x][y]->testCollision(*obj)) {
						if (deleteMine) {
							particleGroup.createParticleText("+100", baddies[x][y]->getPosition(), Color::Cyan);
							deleteBaddie(x, y);
							baddiesKilledThisFrame++;
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool BaddieGroup::testManyForCollisionWithBarrier(vector<Barrier>& objs, bool deleteMine, bool deleteTheirs) {
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

bool BaddieGroup::isBaddiesWin() {
	/*
	14 15 16 17 18 19 20
	 7  8  9 10 11 12 13
	 0  1  2  3  4  5  6
	*/
	for (int y = ROWS - 1; y >= 0; y--) {
		for (int x = 0; x < COLUMNS; x++) {
			if (baddies[x][y] && !baddies[x][y]->eesComing) {
				return (baddies[x][y]->getY() >= 115);
			}
		}
	}
	return false;
}

void BaddieGroup::animateIntro(int framesElapsed) {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			if (!baddies[x][y]) continue;
			// Vector2f start = baddies[x][y]->getPosition();
			Vector2f start = baddies[x][y]->startingPosition;
			Vector2f destination((x * 12) + 4, 10 + (y * 12) + 4);
			float percentage = ((float)framesElapsed) / baddies[x][y]->animationFinishTime;
			baddies[x][y]->setPosition(util::tween(start, destination, percentage));

		}
	}
}

void BaddieGroup::playerDeathAnimation(int framesElapsed) {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			if (!baddies[x][y]) continue;
			if (baddies[x][y]->ohHeMad) {
				deleteBaddie(x, y);
				continue;
			}
			if (framesElapsed == 0) {
				baddies[x][y]->startingPosition = baddies[x][y]->getPosition();
				baddies[x][y]->destination.y = 132.f;
				baddies[x][y]->destination.x = util::lerp(
					-defines::WIDTH / 2,
					defines::WIDTH * 3 / 2,
					baddies[x][y]->startingPosition.x / defines::WIDTH
				);
			}
			float percentage = ((float)framesElapsed) / baddies[x][y]->animationPlayerDead;
			baddies[x][y]->setPosition(util::tween(baddies[x][y]->startingPosition, baddies[x][y]->destination, percentage));
		}
	}
}

void BaddieGroup::baddiesWinAnimation(int framesElapsed) {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			if (!baddies[x][y]) continue;
			if (baddies[x][y]->ohHeMad) {
				deleteBaddie(x, y);
				continue;
			}
			if (setJump < currentBaddies) {
				baddies[x][y]->jump = (x % 2 == 0);
				setJump++;
			}
			if (framesElapsed % 20 == 0) {
				baddies[x][y]->jumpAnimate();
			}
		}
	}
}

void BaddieGroup::update() {
	moveBaddiesSound();
	moveBaddies();
	accelerateBaddies();
	baddieShoot();
	bulletUpdate();
	baddieOffScreen();
}

void BaddieGroup::windowShake(RenderWindow& window) {
	View view = window.getView();
	Vector2f center = view.getCenter();
	center.x += util::rangedRandFloat(-shakeSpeed, shakeSpeed, 100);
	center.y += util::rangedRandFloat(-shakeSpeed, shakeSpeed, 100);
	view.setCenter(center);
	window.setView(view);
}

void BaddieGroup::draw(RenderWindow& window) {
	for (int x = 0; x < COLUMNS; x++) {
		for (int y = 0; y < ROWS; y++) {
			if (baddies[x][y])
				baddies[x][y]->draw(window);
		}
	}
	for (BaddieBullet& bullet : bulletVector) {
		bullet.draw(window);
	}
}

BaddieGroup::~BaddieGroup() {
	for (int x = 0; x < COLUMNS; x++) {
		for (int y = 0; y < ROWS; y++) {
			if (baddies[x][y]) {
				deleteBaddie(x, y);
			}
		}
	}
}
