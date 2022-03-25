#include "GamePlayState.hpp"

GamePlayState::GamePlayState()
	: defender(particles),
	killemAll(particles) {
	// util::setSeed(0U);
	// this->roundStartTimer = ROUND_START_MAX-1;
	// GamePlayState::startRound();

	startMusic.setBuffer(resources::soundFile["randommusic"]);
	startMusic.play();
	score::scoreBonus = 10;

	pauseTint.setFillColor(Color(0x000000D0));
	pauseTint.setSize(Vector2f(defines::WIDTH, defines::HEIGHT));
	pauseTint.setPosition(0, 0);

	pause.setText("PAUSE");
	pause.setHAlign(GameText::CENTER);
	pause.setVAlign(GameText::MIDDLE);
	pause.setSize(GameText::TITLE);
	pause.setPosition({ defines::WIDTH / 2.f, defines::HEIGHT / 2.f });

	stringstream roundTitleStringStream;
	roundTitleStringStream
		<< "ROUND "
		<< setfill(' ')
		<< setw(4)
		<< score::roundNumber;
	roundTitle.setText(roundTitleStringStream.str());
	roundTitle.setHAlign(GameText::CENTER);
	roundTitle.setVAlign(GameText::MIDDLE);
	roundTitle.setSize(GameText::LARGE);
	roundTitle.setPosition({ defines::WIDTH / 2.f, defines::HEIGHT / 2.f });

	powerupSound.setBuffer(resources::soundFile["1up"]);
	powerdownSound.setBuffer(resources::soundFile["bad"]);
	playerDeath.setBuffer(resources::soundFile["defenderboom"]);
	victory.setBuffer(resources::soundFile["victory"]);
}

void GamePlayState::startRound() {
	if (roundStartTimer < ROUND_START_MAX) {
		roundStartTimer++;

		killemAll.animateIntro(roundStartTimer);
		defender.animateIntro(roundStartTimer);
		saveMe.animateIntro(roundStartTimer);

		return;
	} else {
		roundStart = false;
	}
}

void GamePlayState::endRound() {
	if (endRoundBuffer <= 0) {
		victory.play();
	}
	defender.animateOutro(endRoundBuffer);
	endRoundBuffer++;
}

void GamePlayState::loseGame() {

	if (score::currentLives < 0) {
		defender.defenderExplode();
		killemAll.playerDeathAnimation(endRoundBuffer);
		endRoundBuffer++;
	} else {
		defender.defenderExplode();
		killemAll.baddiesWinAnimation(endRoundBuffer);
		endRoundBuffer++;
	}
}

void GamePlayState::updateComponents() {
	// update state components
	defender.update();
	killemAll.update();
	if (isUfoMoving && ufo) {
		ufo->update();
	}
	if (powerup) {
		powerup->update(particles);
	}
}

void GamePlayState::detectCollisions() {
	// do collision tests

	// defender's bullet collision tests
	defender.testBulletCollisions(killemAll, saveMe, particles);

	// defender touches baddie bullet
	if (defender.testManyForCollisionWithBaddieBullet(killemAll.bulletVector) && !defender.isInvuln) {
		score::currentLives--;
		defender.isInvuln = true;
		playerDeath.play();
	}

	// defender touches kamikaze baddie
	for (int x = 0; x < killemAll.COLUMNS; x++) {
		for (int y = 0; y < killemAll.ROWS; y++) {
			if (killemAll.baddies[x][y]) {
				if (defender.testKamiCollision(*killemAll.baddies[x][y]) && !defender.isInvuln) {
					score::currentLives--;
					defender.isInvuln = true;
					playerDeath.play();
				}
			}
		}
	}

	// barrier touches baddie bullet
	saveMe.testManyForCollisionWithBaddieBullet(killemAll.bulletVector, true, true);
	// barrier touches baddie
	killemAll.testManyForCollisionWithBarrier(saveMe.barrierVector, false, true);

	// powerup touches defender 

	// tests if the powerup is agressive or passive
	if (powerup && defender.testCollision(*powerup) && (randomPowerup == defines::PowerUp::Aggressive || randomPowerup == defines::PowerUp::Passive)) {
		for (int x = 0; x < killemAll.COLUMNS; x++) {
			for (int y = 0; y < killemAll.ROWS; y++) {
				if (killemAll.baddies[x][y] && randomPowerup == defines::PowerUp::Aggressive) {
					powerup->agressive(*killemAll.baddies[x][y]);
				} else if (killemAll.baddies[x][y] && randomPowerup == defines::PowerUp::Passive) {
					powerup->passive(*killemAll.baddies[x][y]);
				}
			}
		}
		delete powerup;
		powerup = nullptr;
	} else if (powerup && defender.testCollision(*powerup)) {
		powerup->grantPowerUp(particles);
		delete powerup;
		powerup = nullptr;
	}
}

void GamePlayState::removeOffscreenAssets() {
	// powerup off screen
	if (powerup) {
		if (powerup->isOffScreen()) {
			delete powerup;
			powerup = nullptr;
		}
	}

	// ufo despawns off screen
	if (ufo && ufo->isOffScreen()) {
		delete ufo;
		ufo = nullptr;
		isUfoMoving = false;
	}
}

void GamePlayState::calculateUfo() {
	// start ufo timer when baddies advance
	if (killemAll.baddiesTimesAdvanced > 0) {
		if (setUfoRandom > ufoBuffer && setUfoTimer) {
			ufoBuffer++;
		} else if (ufoBuffer >= setUfoRandom && setUfoTimer) {
			ufo = new Ufo();
			setUfoTimer = false;
			isUfoMoving = true;
			setUfoRandom = 0;
			ufoBuffer = 0;
		} else if (!setUfoTimer && !isUfoMoving) {
			setUfoTimer = true;
			setUfoRandom = util::rangedRand(UFO_TIMER_MIN, UFO_TIMER_MAX);
		}
	}

	// ufo fires powerup
	if (ufo && ufo->hasFired && !powerup && !didUfoFire) {
		int randomPowerUpInt = util::rangedRand(0, defines::PowerUp::COUNT - 1);
		// UNCOMMENT TO FORCE POWERUP
		// randomPowerUpInt = defines::PowerUp::Bomb;
		randomPowerup = static_cast<defines::PowerUp>(randomPowerUpInt);
		powerup = new Powerup(randomPowerup, ufo->getX(), defender);
		switch (randomPowerup)
		{
		case defines::PowerUp::OneUp:
		case defines::PowerUp::Coin:
		case defines::PowerUp::Passive:
		case defines::PowerUp::Curved:
		case defines::PowerUp::Missile:
		case defines::PowerUp::Punch:
		case defines::PowerUp::SpeedUp:
			powerupSound.play();
			break;
		case defines::PowerUp::Aggressive:
		case defines::PowerUp::Bomb:
		case defines::PowerUp::SpeedDown:
			powerdownSound.play();
			break;
		default:
			break;
		}
		didUfoFire = true;
	}

	// ufo & powerup reset
	if (!powerup && !ufo) {
		didUfoFire = false;
		randomPowerup = defines::PowerUp::COUNT;
	}
}

void GamePlayState::calculateStateStatus() {
	// test if state has been completed
	if (!didWin && killemAll.currentBaddies <= 0) {
		didWin = true;
		didLose = false;
		int bonus = score::scoreBonus * score::scoreBonusMultiplier;
		score::score += bonus;
		hud.indicateGlobalScoreChange(particles, bonus);
	} else if (didWin && endRoundBuffer >= END_ROUND_TIMER) {
		isEnding = true;
	} else if (!didLose && (killemAll.isBaddiesWin() || score::currentLives < 0)) {
		didWin = false;
		didLose = true;
	} else if (didLose && endRoundBuffer >= END_ROUND_TIMER) {
		isEnding = true;
	}
}

void GamePlayState::processInput(Event& event) {
	int joystickId = -1;
	if (roundStart) {
		return;
	}
	if (isPause) {
		switch (event.type) {
		case Event::KeyPressed:
			if (event.key.code != Keyboard::Escape) {
				return;
			}
			break;
		case Event::JoystickButtonPressed:
			if (event.joystickButton.button < 4 ||
				event.joystickButton.button > 11) {
				return;
			}
			break;
		default:
			return;
		}
	}

	switch (event.type) {
	case Event::JoystickButtonPressed:
		switch (event.joystickButton.button) {
		case 0:
		case 1:
		case 2:
		case 3:
			if (!didWin && !didLose) {
				defender.fire();
			}
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			isPause = !isPause;
			defender.playerIsMovingLeft = false;
			defender.playerIsMovingRight = false;
			break;
		default:
			break;
		}
		break;
	case Event::JoystickMoved:
		joystickId = event.joystickMove.joystickId;
		if (
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) < -15 ||
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) < -15
		) {
			defender.playerIsMovingLeft = true;
			defender.playerIsMovingRight = false;
		} else if (
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) > 15 ||
			sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) > 15
		) {
			defender.playerIsMovingRight = true;
			defender.playerIsMovingLeft = false;
		} else {
			defender.playerIsMovingLeft = false;
			defender.playerIsMovingRight = false;
		}
		break;
	case Event::KeyPressed:
		switch (event.key.code) {
			// God Button
		// case Keyboard::BackSlash:
		// 	killemAll.forceKami();
		// 	break;
		case Keyboard::A:
		case Keyboard::Left:
			defender.playerIsMovingLeft = true;
			break;
		case Keyboard::D:
		case Keyboard::Right:
			defender.playerIsMovingRight = true;
			break;
		case Keyboard::W:
		case Keyboard::Up:
		case Keyboard::Space:
			// UNCOMMENT TO RECORD DEMO
			// demo << "W";
			if (!didWin && !didLose) {
				defender.fire();
			}
			break;
		case Keyboard::Escape:
			isPause = !isPause;
			defender.playerIsMovingLeft = false;
			defender.playerIsMovingRight = false;
		default:
			break;
		}
		break;

	case Event::KeyReleased:
		switch (event.key.code) {
		case Keyboard::Key::A:
		case Keyboard::Key::Left:
			defender.playerIsMovingLeft = false;
			break;
		case Keyboard::Key::D:
		case Keyboard::Key::Right:
			defender.playerIsMovingRight = false;
			break;
		default:
			break;
		}
	default:
		break;
	}

}

void GamePlayState::update(RenderWindow& window) {
	// UNCOMMENT TO RECORD DEMO
	// if (defender.playerIsMovingLeft && !defender.playerIsMovingRight) {
	// 	demo << "A";
	// } else if (defender.playerIsMovingRight && !defender.playerIsMovingLeft) {
	// 	demo << "D";
	// } else {
	// 	demo << " ";
	// }
	if (isPause) {
		return;
	}
	hud.update();
	if (roundStart) {
		startRound();
		return;
	}
	particles.update();
	if (didWin) {
		killemAll.shakeSpeed = 0.f;
		endRound();
		calculateStateStatus();
		return;
	} else if (didLose) {
		loseGame();
		calculateStateStatus();
		return;
	}

	updateComponents();
	detectCollisions();
	removeOffscreenAssets();
	calculateUfo();
	calculateStateStatus();
}

void GamePlayState::draw(RenderWindow& window) {
	View view = window.getView();
	view.setCenter({ defines::WIDTH / 2.0f, defines::HEIGHT / 2.0f });
	window.setView(view);
	killemAll.windowShake(window);

	hud.draw(window);
	defender.draw(window);
	killemAll.draw(window);
	saveMe.draw(window);
	particles.draw(window);

	if (ufo) {
		ufo->draw(window);
	}
	if (powerup) {
		powerup->draw(window);
	}
	if (roundStart && roundStartTimer < BLINK_MAX && (roundStartTimer / BLINK_SPEED) % 2 == 0) {
		roundTitle.draw(window);
	}
	if (isPause) {
		window.draw(pauseTint);
		pause.draw(window);
	}
}

GamePlayState::~GamePlayState() {
	// UNCOMMENT TO RECORD DEMO
	// ofstream demoFile ("demo.txt");
	// if (!demoFile.fail()) {
	// 	demoFile << demo.rdbuf();
	// 	demoFile.close();
	// }
}
