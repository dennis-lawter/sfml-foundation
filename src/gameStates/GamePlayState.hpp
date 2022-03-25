#ifndef GAMEPLAYSTATE_HPP_
#define GAMEPLAYSTATE_HPP_
#include "GameState.hpp"
#include "../gameObj/groups/ParticleGroup.hpp"
#include "../gameObj/groups/BaddieGroup.hpp"
#include "../gameObj/groups/BarrierGroup.hpp"
#include "../gameObj/Player.hpp"
#include "../gameObj/PlayerBullet.hpp"
#include "../gameObj/Barrier.hpp"
#include "../gameObj/Ufo.hpp"
#include "../gameObj/Powerup.hpp"
#include "../Hud.hpp"

class GamePlayState : public GameState {
protected:
	ParticleGroup particles;
	Hud hud;
	Player defender;
	BaddieGroup killemAll;
	BarrierGroup saveMe;
	Sound startMusic;
	Ufo* ufo = nullptr;
	Powerup* powerup = nullptr;
	Sound powerupSound;
	Sound powerdownSound;
	Sound playerDeath;
	Sound victory;

	// UNCOMMENT TO RECORD DEMO
	// stringstream demo;

	const static int ROUND_START_MAX = 425;
	const static int BLINK_MAX = 380;
	const static int BLINK_SPEED = 20;
	const static int UFO_TIMER_MAX = 600;
	const static int UFO_TIMER_MIN = 50;
	const static int END_ROUND_TIMER = 120;
	int roundStartTimer = 0;
	int ufoBuffer = 0;
	int setUfoRandom = 0;
	int endRoundBuffer = 0;
	defines::PowerUp randomPowerup;

	GameText pause;
	GameText roundTitle;
	RectangleShape pauseTint;

	void startRound();
	void endRound();
	void updateComponents();
	void detectCollisions();
	void removeOffscreenAssets();
	void calculateUfo();
	void calculateStateStatus();
	void loseGame();
public:
	bool didWin = false;
	bool didLose = false;
	bool roundStart = true;
	bool isPause = false;
	bool setUfoTimer = false;
	bool isUfoMoving = false;
	bool didUfoFire = false;

	GamePlayState();

	void processInput(Event& event);
	void update(RenderWindow& window);
	void draw(RenderWindow& window);

	virtual ~GamePlayState();
};

#endif
