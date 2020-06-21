#pragma once

class Module
{

private:
	bool EN;
	bool RDY;

public:
	void Enable();

	void Disable();

	bool Enabled();

	bool IsReady();

	/**
	 * Loop routine of module.
	 */
	virtual void Routine(float) = 0;

protected:
	void SetReady(bool stat);
};
