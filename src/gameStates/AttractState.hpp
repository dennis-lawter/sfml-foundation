#ifndef ATTRACTSTATE_HPP_
#define ATTRACTSTATE_HPP_
#include "GamePlayState.hpp"

class AttractState : public GamePlayState {
private:
	const unsigned int SEED = 0U;
	const string INPUT = "                                  DDDDDDDDDDDDDDDDD        W                                                             W                                                         W                                                                   DDDDDDDDDDDDDDDDDDDDDDDDD                    W                    W                           W                                                     W                                                            W                                                    W                                                         W                                                 W                                                                   AAAAAAAAAAAA                         AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA                                     DDDDDDDDDDDDDDDDDDDDDD                        DDDDD                                                           DDDDDDDDDDD     W                            W                            W                              AAAAAAAA   W                                                        AAAAAAAAAAAAAAAAAA                                               DDDDDDDDDDDD      DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD                    AAAAAAAAAAAAAAAAAAA                  AAAAAAAAAAAAAAAAA   W               AAAAAAAAAAAAAAAA                        DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD    W                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDWDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD  AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA W                                DDDDDDDDD                DDDDDDDDDDDDDDD       DDDDDDDDDWDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD   AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA                                     DDDDDDDDDDDDD                                                                                     DDDDDDDDDDDDDDDWDDDDDDD                         DDDDDDDDDDWDDDD                              DDDDDDDDDDDDDWD                                  DDDDDDDDDD    W              AAAAAAAAAAAAAAAAAAAAAAAAAAAAWAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA        AAAAAAAAAAAAAAA        DDDDDDDDWDDDDDD   DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD   AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA   DWDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDWDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDWDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA                                                              ";
	const string PRESS_START = "PRESS ANY KEY";
	GameText pressStartText;
	unsigned int inputIter = 0;
public:
	AttractState();

	void processInput(Event& event);
	void update(RenderWindow& window);
	void draw(RenderWindow& window);

	virtual ~AttractState();
};

#endif
