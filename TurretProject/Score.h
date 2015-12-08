#pragma once
class Score
{
public:
	static Score* GetInstance();
	~Score() { delete instance; }

	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }

private:
	Score() {m_score = 0 ; }
	int m_score;

	static bool instanceFlag;
	static Score* instance;
};

