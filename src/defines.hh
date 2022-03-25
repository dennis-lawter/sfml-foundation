#ifndef DEFINES_HH_
#define DEFINES_HH_

#include <string>
#include <vector>
using namespace std;

namespace defines {
	static const string GAME_NAME = "Totally Invading Space";
	static const string GAME_TITLE_SCREEN = "TOTALLY\nINVADING\nSPACE";
	static const int WIDTH = 128;
	static const int HEIGHT = 128;
	static const int UFO_FIRE_END = defines::WIDTH - 32;
	static const int UFO_FIRE_START = 32;
	static const string IMAGE_FILE_TYPE = ".png";
	static const string FONT_FILE_TYPE = ".ttf";
	static const string SOUND_FILE_TYPE = ".wav";
	static const string SCORES_FILE_TYPE = ".txt";
	static const int LIVES_CAP = 3;
	static const int BULLET_SPEED_MODIFIER_CAP = 3;

	static const string FONT_FILE_NAME = "PressStart2P";
	static const string SCORES_FILE_NAME = "HighScore";

	static const vector<string> TEXTURE_FILE_NAMES = {
		"1up",
		"aggression",
		"barrier",
		"bomb",
		"boom",
		"bullet",
		"coin",
		"curved",
		"defender",
		// "enemy",
		"explosion",
		"explosionmono",
		"ghost",
		"invader1",
		"invader2",
		"invader3",
		"missile",
		"particle",
		"passive",
		// "player",
		"punch",
		"speed_down",
		"speed_up",
		"ufo"
	};

	static const vector<string> SOUND_FILE_NAMES = {
		"1up",
		"accept",
		"backspace",
		"bad",
		"baddieadvance",
		"baddieboom",
		"baddiemove1",
		"baddiemove2",
		"baddiepew",
		"barrierboom",
		"blip",
		"boss",
		"defenderboom",
		"defenderpew",
		"gameover",
		"idlescorelist",
		"newhighscore",
		"randommusic",
		"speeddown",
		"speedup",
		"ufo",
		"ufoFire",
		"victory",
		"woah",
		"wtf"
	};


	enum PowerUp {
		OneUp = 0,
		Aggressive,
		Bomb,
		Coin,
		Curved,
		// Ghost,
		Missile,
		Passive,
		Punch,
		SpeedDown,
		SpeedUp,

		COUNT
	};

	static map<PowerUp, string> POWER_UP_LIST = {
		{OneUp, "1up"},
		{Aggressive, "aggression"},
		{Bomb, "bomb"},
		{Coin, "coin"},
		{Curved, "curved"},
		// {Ghost, "ghost"},
		{Missile, "missile"},
		{Passive, "passive"},
		{Punch, "punch"},
		{SpeedDown, "speed_down"},
		{SpeedUp, "speed_up"}
	};
}

#endif
