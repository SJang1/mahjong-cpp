#pragma once
class Player
{
private:
	string name;
	bool Reach;
	bool Win;
public:
	Player(string _name);
	string getName() const;
	bool getReach() const;
	bool getWin() const;

	void setReach();
	void setWin();
};

