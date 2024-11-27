#include "std.h"

Tiles::Tiles(string _name, string _readable_name, int _priority) : name(_name), priority(_priority), readable_name(_readable_name)
{
	
}
string Tiles::getName() const
{
	return name;
}
int Tiles::getPriority() const 
{
	return priority;
}
string Tiles::getReadableName() const
{
	return readable_name;
}