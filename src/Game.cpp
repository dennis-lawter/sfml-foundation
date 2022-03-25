#include "Game.hpp"

Game::Game() {
	this->screenClearColor = sf::Color(0x222222ff);
	this->background.setFillColor(sf::Color::Black);
	this->background.setPosition(0, 0);
	this->background.setSize(sf::Vector2f(defines::WIDTH, defines::HEIGHT));
}

void Game::run() {
	this->gameState = new LoadingState();
	this->currentGameState = GameState::Loading;
	this->initializeWindow();
	this->gameLoop();
}

Game::~Game() {
	delete gameState;
}



void Game::initializeWindow() {
	int screenWidthAvailable = sf::VideoMode::getDesktopMode().width - 100;
	int screenHeightAvailable = sf::VideoMode::getDesktopMode().height - 100;
	int widthMultiplier = screenWidthAvailable / defines::WIDTH;
	int heightMultiplier = screenHeightAvailable / defines::HEIGHT;
	int gameScreenMultiplier = (widthMultiplier < heightMultiplier) ? widthMultiplier : heightMultiplier;
	window.create(sf::VideoMode(gameScreenMultiplier * defines::WIDTH, gameScreenMultiplier * defines::HEIGHT), defines::GAME_NAME);
	camera.setSize(defines::WIDTH, defines::HEIGHT);
	camera.setCenter(defines::WIDTH / 2.f, defines::HEIGHT / 2.f);
	window.setView(camera);

	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
}

void Game::resizeWindow() {
	float x, y, w, h, idealMultiplier;
	float windowWidth = this->window.getSize().x;
	float windowHeight = this->window.getSize().y;
	float widthMultiplier = windowWidth / defines::WIDTH;
	float heightMultiplier = windowHeight / defines::HEIGHT;
	float gameAspectRatio = ((float)defines::WIDTH) / defines::HEIGHT;
	if (widthMultiplier > heightMultiplier) {
		idealMultiplier = windowHeight / (1.f / gameAspectRatio);
		w = idealMultiplier / windowWidth;
		x = (1.f - w) / 2.f;
		h = 1.f;
		y = 0.f;
	} else {
		idealMultiplier = windowWidth / gameAspectRatio;
		h = idealMultiplier / windowHeight;
		y = (1.f - h) / 2.f;
		w = 1.f;
		x = 0.f;
	}
	this->camera.setViewport(sf::FloatRect(x, y, w, h));
	this->window.setView(this->camera);
}

void Game::gameLoop() {
	while (this->isRunning) {
		this->processInputLoop();
		this->update();
		this->draw();
	}
}

void Game::processInputLoop() {
	while (this->window.pollEvent(this->currentEvent)) {
		switch (this->currentEvent.type) {
		case sf::Event::Closed:
			this->isRunning = false;
			break;
		case sf::Event::Resized:
			this->resizeWindow();
			break;
		default:
			this->gameState->processInput(this->currentEvent);
			break;
		}
	}
}

void Game::update() {
	this->gameState->update(window);

	if (this->gameState->isEnding) {
		switch (this->currentGameState) {
		case GameState::Loading:
			delete this->gameState;
			this->gameState = new LoadingState();
			this->currentGameState = GameState::Loading;
			break;
		default:
			throw std::runtime_error("Invalid game state");
			break;
		}
	}
}

void Game::draw() {
	this->window.clear(this->screenClearColor);
	this->window.draw(this->background);

	this->gameState->draw(this->window);
	
	this->window.display();
}
