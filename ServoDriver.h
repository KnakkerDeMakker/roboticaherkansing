#pragma once
#include <queue>
#include "Module.h"
#include "Task.h"
#include "Dynamic.h"
#include <iostream>

class ServoDriver : public Module , public Dynamic
{

private:
	bool up;
	char Dest;
	std::queue<Task> tasks;
	float timeRemaining = 1;

public:
	ServoDriver() : up(false), tasks(std::queue<Task>()), timeRemaining(0) { Enable(); SetReady(true); };

	bool IsUp();
	void AddTask(Task task);
	void AddTask(std::queue<Task> tasks);
	void Routine(float) override;

private:
	void DoTask(Task task);
	void Up();
	void Down();
};

bool test_ServoDriver();

