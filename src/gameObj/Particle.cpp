#include "Particle.hpp"

Particle::Particle(ParticleAttributeList attributes)
	: ParticleAttributeList(attributes) {
}

void Particle::move() {
	velocity += acceleration;
	position += velocity;
}

Color Particle::currentColor() {
	if (initialColor == finalColor) return initialColor;

	Color color;
	color.r = util::lerp(initialColor.r, finalColor.r, agePercentage);
	color.g = util::lerp(initialColor.g, finalColor.g, agePercentage);
	color.b = util::lerp(initialColor.b, finalColor.b, agePercentage);
	color.a = util::lerp(initialColor.a, finalColor.a, agePercentage);

	return color;
}

void Particle::update() {
	if (age >= timeToLive) {
		isReadyToDie = true;
	}
	agePercentage = ((float)age) / timeToLive;
	
	move();
	
	age++;
}

Particle::~Particle() {
}


ParticleText::ParticleText(ParticleAttributeList attributes, std::string text)
	:Particle(attributes) {
		this->text.setFillColor(attributes.initialColor);
		// this->text.setFont(resources::font);
		this->text.setCharacterSize(80);
		this->text.setScale(.05f, .05f);
		this->text.setString(text);

		FloatRect textBounds = this->text.getLocalBounds();
		this->text.setPosition(this->position);
		this->text.setOrigin(textBounds.width/2.f, 0.f);
	}

void ParticleText::update() {
	Particle::update();
	text.setFillColor(currentColor());
	text.setPosition(position);
}

void ParticleText::draw(RenderWindow& window) {
	window.draw(text);
}

ParticleText::~ParticleText() {
}


ParticleObject::ParticleObject(ParticleAttributeList attributes)
	: GameObject(ParticleObject::PARTICLE_NAME)
	, Particle(attributes) {
	sprite.setColor(initialColor);
	sprite.setScale(initScaleFactor, initScaleFactor);
}

void ParticleObject::update() {
	Particle::update();
	sprite.setColor(currentColor());
	sprite.setPosition(position);
}

ParticleObject::~ParticleObject() {
}
