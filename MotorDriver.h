#pragma once
#include "Module.h"
#include "Dynamic.h"
#include "Square.h"
#include "Task.h"
#include <iostream>
#include <queue>

class MotorDriver : public Module, public Dynamic
{

private:
	float stepSize;		 //Distance for pivot movement per ms
	float timeRemaining; //Time remaining for movement
	Shape *Pivot;
	bool isXDriver;
	std::queue<Task> ToDo;
	float dest;

public:
	void AddTask(Task task);
	void AddTask(std::queue<Task> tasks);
	MotorDriver(Shape &pivot, bool IsXDriver);
	void Routine(float DeltaTime) override;
	float LastPos();

private:
	/*
	 *	Transforms next destination to step itervals
	 */
	float calculateStepSize(const Task &task);

	void DoTask(Task task);

	//This friend function is only used for testing :)
	friend Shape &____GetPivotPoint(const MotorDriver &);
};

Shape &____GetPivotPoint(const MotorDriver &driver);

bool test_MotorDriver();
bool test_Module();
