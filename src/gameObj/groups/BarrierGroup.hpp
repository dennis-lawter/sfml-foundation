#ifndef BARRIERGROUP_HPP_
#define BARRIERGROUP_HPP_
#include <SFML/Graphics.hpp>
#include "../Barrier.hpp"
#include "../BaddieBullet.hpp"

class BarrierGroup {
private:
	const vector<pair<int, int>> COORDS = {
		{3, 14},
		{4, 14},
		{5, 14},
		{3, 13},
		{4, 13},
		{5, 13},
		{3 + 7, 14},
		{4 + 7, 14},
		{5 + 7, 14},
		{3 + 7, 13},
		{4 + 7, 13},
		{5 + 7, 13}
	};
public:
	vector<Barrier> barrierVector;

	BarrierGroup();

	bool testOneForCollision(GameObject* obj, bool deleteMine);
	bool testManyForCollisionWithBaddieBullet(vector<BaddieBullet>& objs, bool deleteMine, bool deleteTheirs);
	void animateIntro(int framesElapsed);

	void update();
	void draw(RenderWindow& window);

	~BarrierGroup();
};

#endif
