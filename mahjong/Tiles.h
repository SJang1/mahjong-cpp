#pragma once
class Tiles
{
private:
	string name;
	string readable_name;
	int priority;

public:
	Tiles(string _name, string readable_name, int _priority);

	string getName() const;
	int getPriority() const;
	string getReadableName() const;
};

