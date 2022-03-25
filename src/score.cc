#include "score.hh"

namespace score {
	int currentLives = 2;
	int score = 0;
	string initials = " ";
	int roundNumber = 1;
	double speedModifier = 0;
	double roundMultiplier = 0.005;
	int scoreBonus = 10; // 8 is minimum
	int scoreBonusMultiplier = 10;

	vector<pair<string, int>> scoreList = {
		{"AAA", 0},
		{"AAA", 0},
		{"AAA", 0},
		{"AAA", 0},
		{"AAA", 0},
		{"AAA", 0},
		{"AAA", 0},
		{"AAA", 0},
		{"AAA", 0},
		{"AAA", 0}
	};
	// vector<string> initialsList = {"AAA", "AAA", "AAA", "AAA", "AAA", "AAA", "AAA", "AAA", "AAA", "AAA"};


	bool compareScores(pair<string, int> left, pair<string, int> right) {
		return left.second > right.second;
	}

	void loadScores() {
		ifstream loadScore;
		loadScore.open(resources::highScoresFileName);
		if (!loadScore.fail()) {
			scoreList.clear();

			int scoreFromFile = 0;
			char initialsFromFile [4] = "   "; 
			while (!loadScore.eof()) {
				loadScore >> initialsFromFile;
				loadScore >> scoreFromFile;
				scoreList.push_back({initialsFromFile, scoreFromFile});
			}
		}
		loadScore.close();
		while (scoreList.size() > 10) {
			scoreList.pop_back();
		}
		while (scoreList.size() < 10) {
			scoreList.push_back({"AAA", 0});
		}
		sort(scoreList.begin(), scoreList.end(), compareScores);
	}

	void saveScores() {
		ofstream saveScore;
		saveScore.open(resources::highScoresFileName, ofstream::trunc);
		if (!saveScore.fail()) {
			for (pair<string, int> singleScore : scoreList) {
				saveScore << singleScore.first << '\t' << singleScore.second << '\n';
			}
		}
		saveScore.close();
	}

	void addScore() {
		scoreList.push_back({initials, score});
		sort(scoreList.begin(), scoreList.end(), compareScores);
		while (scoreList.size() > 10) {
			scoreList.pop_back();
		}
		saveScores();
	}

	bool newScoreIsAHighScore() {
		if (score == 0) {
			return false;
		}
		for (int i = scoreList.size() - 1; i >= 0; i--) {
			if (score >= scoreList[i].second) {
				return true;
			}
		}
		return false;
	}

	int matchScore() {
		if (score == 0) {
			return -1;
		}
		for (int i = scoreList.size() - 1; i >= 0; i--) {
			if (score == scoreList[i].second) {
				return i;
			}
		}
		return -1;
	}

	string getScoreTextString(bool currentScoreVisible) {
		stringstream highScores;
		int matchScoreResult = matchScore();
		for (unsigned int i = 0; i < scoreList.size(); i++) {
			if (!currentScoreVisible && matchScoreResult >= 0 && i == ((unsigned int)matchScoreResult)) {
				highScores << "            \n";
			} else {
				highScores << scoreList[i].first << " ";
				highScores << setfill('0') << setw(8) << scoreList[i].second << "\n";
			}
		}
		return highScores.str();
	}

	GameText getScoreTextBlock(bool currentScoreVisible) {
		GameText highScoreText;

		highScoreText.setText(getScoreTextString(currentScoreVisible));
		highScoreText.setHAlign(GameText::CENTER);
		highScoreText.setVAlign(GameText::MIDDLE);
		highScoreText.setSize(GameText::LARGE);
		highScoreText.setPosition({defines::WIDTH/2.f, defines::HEIGHT/2.f});

		return highScoreText;
	}
}
