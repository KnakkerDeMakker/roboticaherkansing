#include "ServoDriver.h"

void ServoDriver::Up() {
	up = true;
}

void ServoDriver::Down() {
	up = false;
}

bool ServoDriver::IsUp()
{
	return up;
}

bool test_ServoDriver()
{
	try
	{
		ServoDriver &sd = *(new ServoDriver());

		//Test IsUp
		if (sd.IsUp())
			throw "SERVODRIVER ERROR (ISUP)";

		/*				OBSOLETE AFTER REINVENTING SERVODRIVER
		sd.Toggle();
		if (!sd.IsUp())
			throw "SERVODRIVER ERROR (TOGGLE)";
			*/
		return true;
	}
	catch (const char *e)
	{
		return false;
	}
}

void ServoDriver::AddTask(Task task) {
	tasks.push(task);
}

void ServoDriver::AddTask(std::queue<Task> tasks) {
	auto size = tasks.size();
	for (int i = 0; i < size; i++) {
		this->tasks.push(tasks.front());
		tasks.pop();
	}
}

void ServoDriver::Routine(float DeltaTime)
{
	if (Enabled()) {
		//Execute current task
		if (!IsReady())
		{
			//Update timekeeping
			timeRemaining -= DeltaTime;

			//Check if finished with task.
			if (timeRemaining <= 0) {
				if (Dest > 0)
					Up();
				else if (Dest < 0)
					Down();

				SetReady(true);
			}
		}
		//Check if there are any tasks in queue
		if (IsReady() && !tasks.empty()) {
			DoTask(tasks.front());
			tasks.pop();
		}

		if (IsReady() && tasks.empty()) {
			std::cout << "Driver Z" << ": DONE!\n";
			Disable();
		}
	}
}

void ServoDriver::DoTask(Task task) {
	//Set member fields
	timeRemaining = task.Time;
	if (task.Dest == 0 || task.Dest == 1 || task.Dest == -1)
		Dest = (char)task.Dest;
	Module::SetReady(false);
}