#include "MotorDriver.h"

MotorDriver::MotorDriver(Shape &pivot, bool isX)
	: Pivot(&pivot), isXDriver(isX) {
	SetReady(true);
	Enable();
}

void MotorDriver::DoTask(Task task)
{
	//Set member fields
	stepSize = calculateStepSize(task);
	timeRemaining = task.Time;
	dest = task.Dest;
	//Ready = false
	Module::SetReady(false);
}

void MotorDriver::AddTask(std::queue<Task> tasks) {
	auto size = tasks.size();
	for (int i = 0; i < size; i++) {
		ToDo.push(tasks.front());
		tasks.pop();
	}
}

float MotorDriver::LastPos() {
	return ToDo.back().Dest;
}

float MotorDriver::calculateStepSize(const Task &task)
{
	//Get current pos
	float pos = (isXDriver) ? Pivot->GetOrig().X : Pivot->GetOrig().Y;
	//Find difference in position
	float deltaS = task.Dest - pos;
	// Divide difference over remaining timespan in ms
	return deltaS / task.Time;
}

void MotorDriver::Routine(float DeltaTime)
{
	if (Enabled()) {
		//Execute current task
		if (!IsReady())
		{
			//Calculate step size
			auto Step = stepSize * DeltaTime;
			//Update pivot pos
			if (isXDriver) {
				Pivot->Move(Step, 0);
			}
			else
				Pivot->Move(0, Step);

			//Update timekeeping
			timeRemaining -= DeltaTime;

			//Check if finished with task.
			if (timeRemaining <= 0) {
				//Set pos to exact dest (Floating point isn't perfect.)
				Point2 pos = Pivot->GetOrig();
				isXDriver ? pos.X : pos.Y = dest;
				Pivot->SetOrig(pos);

				SetReady(true);
			}
		}
		//Check if there are any tasks in queue
		if (IsReady() && !ToDo.empty()) {
			DoTask(ToDo.front());
			ToDo.pop();
		}

		if (IsReady() && ToDo.empty()) {
			std::cout << "Driver " << ((isXDriver) ? "X" : "Y") << ": DONE!\n";
			Disable();
		}
	}
}

Shape &____GetPivotPoint(const MotorDriver &driver)
{
	return *driver.Pivot;
}

void MotorDriver::AddTask(Task task) {
	ToDo.push(task);
}

//TESTS
bool test_Module()
{
	try
	{
		//Init prerequisites
		auto pv = Square({ 0, 0 }, 0.0f);
		auto Driver = MotorDriver(pv, false);

		//Test Disable
		Driver.Disable();
		if (Driver.Enabled())
			throw "MODULE ERROR (DISABLE)";

		//Test Enable
		Driver.Enable();
		if (!Driver.Enabled())
			throw "MDOULE ERROR (ENABLE)";

		//Test Ready
		Task task;
		task.Dest = 1;
		task.Time = 1000; //timeRemaining wordt hierdoor 1000ms

		Driver.AddTask(task);
		Driver.Routine(500.0f);
		if (Driver.IsReady())
			throw "MODULE ERROR (READY)";

		Driver.Routine(501.0f);
		if (!Driver.IsReady())
			throw "MODULE ERROR (READY)";
	}
	catch (const char *e)
	{
		printf("%s\n", e);
		return false;
	}
	return true;
}

bool test_MotorDriver()
{
	try
	{
		//Initialize prerequisites.
		auto &pv = *(new Square({ 0, 0 }, 0.0f));
		//Initialize drivers
		auto xdriver = MotorDriver(pv, true);
		auto ydriver = MotorDriver(pv, false);

		//Set task
		auto task = Task();
		task.Time = 1; //1s
		task.Dest = 1; //(1,0)

		//Execute task
		xdriver.AddTask(task);

		//Wait half a second
		xdriver.Routine(500.0f);

		//Test predicted location (0.5, 0)
		if (____GetPivotPoint(xdriver).GetOrig().X != 0.5f)
			throw "MOTORDRIVER ERROR";
	}
	catch (const char *e)
	{
		printf("%s\n", e);
		return false;
	}
	return true;
}
