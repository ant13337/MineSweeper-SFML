#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include "NumberDisplay.h"
class Timer : public NumberDisplay
{
public:
	Timer();
	Timer(sf::Vector2i position);
	~Timer();

	void updateTimer();
	
	void resetTimer();
    void startTimer();
	void stopTimer();
    void stopTimer(std::string timeInformation);
private:
	bool timerStarted = false;
	std::time_t time;
	std::time_t lastTimeStamp;
};
