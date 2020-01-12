
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <string>
#include <iostream>
#include <chrono>

namespace sw
{
	struct stopwatch
	{
	private:
		std::chrono::steady_clock::time_point start_time;
		std::chrono::steady_clock::time_point end_time;
		int laps;

	public:
		void start();
		void lap();
		void stop();

		std::string total_str() const;
		std::string mean_str() const;

		friend std::ostream& operator<<(std::ostream& out, const stopwatch& sw);
	};
};

#endif /* STOPWATCH_H */
