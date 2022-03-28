#include "playerInput.hh"

namespace playerInput {

	bool testBool = true;
	int joystickId = -1;
	sf::Vector2f xRange = { -1.f, 1.f };
	sf::Vector2f yRange = { -1.f, 1.f };
	sf::Vector2f inputVector = { 0.f, 0.f };

	sf::Vector2f getInputVector() {
		float magnitudeSquared = inputVector.x * inputVector.x + inputVector.y * inputVector.y;
		if (magnitudeSquared > 1) {
			float invMagnitude = util::InvSqrt(magnitudeSquared);
			return inputVector * invMagnitude;
		} else {
			return inputVector;
		}
	}

	void inputSideScroll(sf::Event& event) {
		joystickId = -1;

		switch (event.type) {
		case sf::Event::JoystickButtonPressed:
			switch (event.joystickButton.button) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			default:
				break;
			}
			break;

		case sf::Event::JoystickMoved:
			joystickId = event.joystickMove.joystickId;
			if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) < -15 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) < -15
				) {
			} else if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) > 15 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) > 15
				) {
			} else {
			}
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
				// God Button
				// case Keyboard::BackSlash:
				// 	break;
			case sf::Keyboard::A:
			case sf::Keyboard::Left:
				break;
			case sf::Keyboard::D:
			case sf::Keyboard::Right:
				break;
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
			case sf::Keyboard::Space:
				break;
			case sf::Keyboard::Escape:
			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code) {
			case sf::Keyboard::Key::A:
			case sf::Keyboard::Key::Left:
				break;
			case sf::Keyboard::Key::D:
			case sf::Keyboard::Key::Right:
				break;
			default:
				break;
			}
		default:
			break;
		}
	}

	void inputTopDown(sf::Event& event) {
		joystickId = -1;

		switch (event.type) {
		case sf::Event::JoystickButtonPressed:
			switch (event.joystickButton.button) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			default:
				break;
			}
			break;

		case sf::Event::JoystickMoved:
			joystickId = event.joystickMove.joystickId;
			if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) < -15 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) < -15
				) {
			} else if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X) > 15 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovX) > 15
				) {
			} else {
			}
			
			if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y) < -15 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) < -15
				) {
			} else if (
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y) > 15 ||
				sf::Joystick::getAxisPosition(joystickId, sf::Joystick::PovY) > 15
				) {
			} else {
			}
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
				// God Button
				// case Keyboard::BackSlash:
				// 	break;
			case sf::Keyboard::A:
			case sf::Keyboard::Left:
				inputVector.x -= 1.f;
				break;
			case sf::Keyboard::D:
			case sf::Keyboard::Right:
				inputVector.x += 1.f;
				break;
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				inputVector.y += 1.f;
				break;
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
				inputVector.y -= 1.f;
				break;
			case sf::Keyboard::Space:
				break;
			case sf::Keyboard::Escape:
			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code) {
			case sf::Keyboard::Key::A:
			case sf::Keyboard::Key::Left:
				inputVector.x += 1.f;
				break;
			case sf::Keyboard::Key::D:
			case sf::Keyboard::Key::Right:
				inputVector.x -= 1.f;
				break;
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				inputVector.y -= 1.f;
				break;
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
				inputVector.y += 1.f;
				break;
			default:
				break;
			}
		default:
			break;
		}

	}

}
