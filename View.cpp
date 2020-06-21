#include "View.h"

View::View(Model *m)
	: model(m), t(Time()) {}

void View::Update()
{
	//New frame, so set timer
	t.Update();
	//Get collection of dynamic modules
	auto modules = model->getDynamicObjects();
	//Update all of their states
	for (auto module : modules)
	{
		module->Routine(t.DeltaTime);
	}
}

void View::Draw()
{
	//Get collection of all drawable shapes
	auto shapes = model->getDrawables();

	//Call Draw() on all of them
	for (auto shape : shapes)
	{
		shape->Draw();
	}
}
