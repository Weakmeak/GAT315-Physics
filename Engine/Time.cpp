#include "Time.h"

Time::Time()
{
    m_prevTime = SDL_GetPerformanceCounter();
}

void Time::Update()
{
    uint64_t m_time = SDL_GetPerformanceCounter();
    uint64_t elaspedTime = m_time - m_prevTime;
    m_prevTime = m_time;

    m_deltaTime = elaspedTime / (float)SDL_GetPerformanceFrequency();
    m_fps = 1 / m_deltaTime;

}

