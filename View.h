#pragma once
#include "Drawable.h"
#include "Model.h"
#include "Time.h"
#include <vector>
#include <iostream>

class View : public Drawable
{
private:
	Model *model;
	Time t;

public:
	View(Model *model);
	void Update();
	void Draw() override;
};

bool test_View();
