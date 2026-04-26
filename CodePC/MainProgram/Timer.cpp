#include "Timer.h"

Timer::Timer()
{
    time = 0;
    lastTimeStamp = 0;
}

Timer::Timer(sf::Vector2i position)
{
    time = 0;
    lastTimeStamp = 0;
    setPosition(position);
}

Timer::~Timer()
{
    std::cout << "~Timer()" << std::endl;
}

void Timer::updateTimer()
{
    std::time_t unixTimestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if (timerStarted)
    {
        if (unixTimestamp - time < 1000)
        {
            setNumberToDisplay(unixTimestamp - time);
        }
        else
        {
            setNumberToDisplay(999); //if the timer goes above 999 just display 999
        }
        lastTimeStamp = unixTimestamp;
    }
    else if (time == std::time_t(0)) //if timer was reset
    {
        setNumberToDisplay(0);
    }
    else //if timer stopped
    {
        setNumberToDisplay(lastTimeStamp - time);
    }
}

void Timer::resetTimer()
{
    time = 0;
}

void Timer::startTimer()
{
    std::time_t unixTimestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    time = unixTimestamp;
    timerStarted = true;
}

void Timer::stopTimer()
{
    timerStarted = false;
}

//Victory version saves the time it took to complete the board
void Timer::stopTimer(std::string timeInformation) //timeInformation should contain details about the board that you played on
{
    auto unixTimestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::ofstream outFile("../times.txt", std::ios_base::app);

    if (outFile.is_open()) 
    {
        // Write a new row of text to the file
        outFile << timeInformation  << " " << unixTimestamp - time << " seconds" << std::endl;

        // Close the file
        outFile.close();
    }
    timerStarted = false;
}