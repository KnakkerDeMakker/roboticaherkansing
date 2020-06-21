#include "Module.h"

void Module::Enable()
{
		EN = true;
}

void Module::Disable()
{
	EN = false;
}

bool Module::Enabled()
{
	return EN;
}

bool Module::IsReady()
{
	return RDY;
}

void Module::SetReady(bool stat)
{
	RDY = stat;
}
