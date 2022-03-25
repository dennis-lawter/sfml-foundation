#include <cstdlib>
#include "gameStates/GamePlayState.hpp"
#include "gameStates/TitleState.hpp"
#include "gameStates/GameOverState.hpp"
#include "gameStates/AttractState.hpp"
#include "gameStates/ShowScoreState.hpp"
#include "gameStates/EnterInitialsState.hpp"
#include "score.hh"
using namespace sf;
using namespace std;

RenderWindow window;
View kamera;
RectangleShape background;

GameState* gameState = nullptr;

int stateLevel = 0;

int init() {
	/* a try catch will run the first function and catches a RUNTIME ERROR
	*/
	try {
		resources::loadResources();
	} catch (const runtime_error& e) {
		return EXIT_FAILURE;
	}

	gameState = new TitleState();

	background.setFillColor(Color::Black);
	background.setSize(Vector2f(defines::WIDTH, defines::HEIGHT));
	background.setPosition(0, 0);

	return EXIT_SUCCESS;
}


/*Creates the window within a certain range of the user screen and creates
a square screen that makes the game large enough to see the models at a
proper aspect ratio
*/
void windowInit() {
	int width = VideoMode::getDesktopMode().width - 100;
	int height = VideoMode::getDesktopMode().height - 120;
	int widthMulti = width / defines::WIDTH;
	int heightMulti = height / defines::HEIGHT;
	int smallestMulti = (widthMulti > heightMulti) ? heightMulti : widthMulti;
	window.create(VideoMode(smallestMulti * defines::WIDTH, smallestMulti * defines::HEIGHT), defines::GAME_NAME);
	kamera.setSize(defines::WIDTH, defines::HEIGHT);
	kamera.setCenter(defines::WIDTH / 2, defines::HEIGHT / 2);
	window.setView(kamera);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
}

void update() {
	GamePlayState* asGamePlayState;
	TitleState* asTitleState;
	ShowScoreState* asShowScoreState;
	bool didWin;

	gameState->update(window);

	if (gameState->isEnding) {
		switch (stateLevel) {
		case GameState::EnterInitials:
			delete gameState;
			gameState = new GameOverState();
			stateLevel = GameState::GameOver;
			break;
		case GameState::Attract:
			delete gameState;
			gameState = new TitleState();
			asTitleState = (TitleState*)gameState;
			asTitleState->bufferTick = asTitleState->BUFFERTIMER;
			stateLevel = GameState::Title;
			break;
		case GameState::ShowScore:
			asShowScoreState = (ShowScoreState*)gameState;
			if (asShowScoreState->idle) {
				delete gameState;
				gameState = new AttractState();
				stateLevel = GameState::Attract;
			} else {
				delete gameState;
				gameState = new TitleState();
				stateLevel = GameState::Title;
			}
			break;
		case GameState::Title:
			asTitleState = (TitleState*)gameState;
			if (asTitleState->idle) {
				delete gameState;
				gameState = new ShowScoreState();
				stateLevel = GameState::ShowScore;
			} else {
				delete gameState;
				gameState = new GamePlayState();
				stateLevel = GameState::GamePlay;
			}
			break;
		case GameState::GamePlay:
			asGamePlayState = (GamePlayState*)gameState;
			didWin = asGamePlayState->didWin;
			if (didWin) {
				stateLevel = GameState::Title;
				score::roundNumber++;
				score::speedModifier += (score::roundNumber * score::roundMultiplier);
				delete gameState;
				gameState = new GamePlayState();
				stateLevel = GameState::GamePlay;
				break;
			} else if (score::newScoreIsAHighScore()) {
				delete gameState;
				gameState = new EnterInitialsState();
				stateLevel = GameState::EnterInitials;
			} else {
				delete gameState;
				gameState = new GameOverState();
				stateLevel = GameState::GameOver;
			}
			break;
		case GameState::GameOver:
			delete gameState;
			gameState = new TitleState();
			stateLevel = GameState::Title;
			break;
		default:
			window.close();
			break;
		}
	}
}

void draw() {
	// The background of the game when in a larger window
	window.clear(Color(0x000022ff));
	window.draw(background);
	gameState->draw(window);
	window.display();
}

void resizeWindow() {
	double w, h, idealMultiplier, x, y;
	double windowWidth = window.getSize().x;
	double windowHeight = window.getSize().y;
	double screenAspectRatio = windowWidth / windowHeight;
	double gameAspectRatio = ((double)defines::WIDTH) / defines::HEIGHT;
	if (screenAspectRatio > 1) {
		idealMultiplier = windowHeight / gameAspectRatio;
		w = idealMultiplier / windowWidth;
		x = (1.0 - w) / 2.0;
		h = 1.0;
		y = 0.0;
	} else {
		idealMultiplier = windowWidth / gameAspectRatio;
		h = idealMultiplier / windowHeight;
		y = (1.0 - h) / 2.0;
		w = 1.0;
		x = 0.0;
	}
	kamera.setViewport(FloatRect(x, y, w, h));
	window.setView(kamera);
}

int main(int argc, char** argv) {
	if (init() != EXIT_SUCCESS)
		return EXIT_FAILURE;
	windowInit();

	while (window.isOpen()) {
		Event currentEvent;
		while (window.pollEvent(currentEvent)) {
			switch (currentEvent.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				resizeWindow();
				break;
			default:
				gameState->processInput(currentEvent);
				break;
			}
		}

		update();
		draw();
	}
	delete gameState;
	return EXIT_SUCCESS;
}
