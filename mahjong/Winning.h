#pragma once
class Winning
{
private:
public:
	static bool isWinningHand(const vector<Tiles*>& tiles);
	static bool canDeclareRiichi(const vector<Tiles*>& tiles, vector<Tiles*>& reachhand);
};

