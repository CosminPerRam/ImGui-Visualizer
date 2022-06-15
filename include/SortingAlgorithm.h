
#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#define DO_CHECKSTEP bool goContinue = false; \
					while (!goContinue) { \
						stepState state = this->checkStep(); \
						if (state == stepState::EXITED) \
							return; \
						else if (state != stepState::PAUSED) \
							goContinue = true; \
					}
#define DO_PROGRESSIVE_CHECKSTEP ++stats.steps; DO_CHECKSTEP;
#define DO_STARTED this->reset();
#define DO_FINISHED m_isFinished = true;

class SortingAlgorithm
{
public:
	struct statistics
	{
		float sortTimeMs = 0.f;
		unsigned comparisons = 0, reads = 0, writes = 0, steps = 0;

		void reset();

		void addComparison();
		void addAssigment();
		void addSwap();
	};

protected:
	//std::mutex variablesMutex;

	statistics stats;

	std::vector<float> numbers;

	sf::Clock theClock;

	std::thread theThread;
	enum class stepState { NONE, PAUSED, EXITED, STEP };
	std::atomic<bool> m_pause = false, m_exit = false, m_isFinished = false, m_doStep = false;

	virtual void sorter() = 0;

	void reset();
	stepState checkStep();

public:
	SortingAlgorithm();

	void start();
	void stop();
	void pause();
	void resume();
	bool doStep();

	void shuffle();

	bool isFinished();
	const std::vector<float>& getNumbers();
	const statistics& getStatistics();
};
