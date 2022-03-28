#include "playerInput.hh"

namespace playerInput {

	bool testBool = true;
	int joystickId = -1;
	sf::Vector2f xRange = { -1, 1 };
	sf::Vector2f yRange = { -1, 1 };

	sf::Vector2f inputSideScroll(sf::Event& event) {
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

	sf::Vector2f inputTopDown(sf::Event& event) {
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
			case sf::Keyboard::S:
			case sf::Keyboard::Down:
				break;
			case sf::Keyboard::W:
			case sf::Keyboard::Up:
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

}
