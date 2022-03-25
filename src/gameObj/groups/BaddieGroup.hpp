#ifndef BADDIEGROUP_HPP_
#define BADDIEGROUP_HPP_
#include "../Baddie.hpp"
#include "../BaddieBullet.hpp"
#include "../../score.hh"
#include "../Barrier.hpp"
#include "ParticleGroup.hpp"

class BaddieGroup {
private:
	const static int SHOOT_DELAY = 60;
	const float SPEED_MULT = 0.0125;

	bool baddieMoveSwap = true;
	bool allMoveRight = true;
	int baddiesKilledThisFrame = 0;
	int randomColumn = 0;
	int shootTimer = 0;
	int baddieMoveTimer = 100;
	int baddieMoveTimerBuffer = 0;
	int setJump = 0;
	float baddiesSpeed = 0;

	Sound baddiepew;
	Sound baddieMoveOne;
	Sound baddieMoveTwo;
	Sound baddieDeath;
	Sound baddiesAdvanceSound;
	ParticleGroup& particleGroup;

	void moveBaddiesSound();
	void moveBaddies();
	void accelerateBaddies();
	void baddieShoot();
	void bulletUpdate();
	void deleteBaddie(int x, int y);
	void baddiesWinAnimation();
public:
	const static int COLUMNS = 7;
	const static int ROWS = 3;
	const static int MAX_BADDIES = ROWS * COLUMNS;
	Baddie* baddies[COLUMNS][ROWS];
	vector<BaddieBullet> bulletVector;
	int currentBaddies = MAX_BADDIES;
	int baddiesTimesAdvanced = 0;
	float shakeSpeed = 0.f;

	BaddieGroup(ParticleGroup& particleGroup);

	bool testOneForCollision(GameObject* obj, bool deleteMine);
	bool testManyForCollisionWithBarrier(vector<Barrier>& objs, bool deleteMine, bool deleteTheirs);

	bool isBaddiesAdvance();
	bool isBaddiesWin();
	void chooseBaddieCuss();
	void animateIntro(int framesElapsed);
	void playerDeathAnimation(int framesElapsed);
	void baddiesWinAnimation(int framesElapsed);
	void baddieOffScreen();
	void forceKami();

	void update();
	void windowShake(RenderWindow& window);
	void draw(RenderWindow& window);

	~BaddieGroup();
};

#endif
