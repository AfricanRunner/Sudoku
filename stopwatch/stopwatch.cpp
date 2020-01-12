
#include "stopwatch.h"

#include <sstream>
#include <iomanip>

using namespace sw;
using namespace std::chrono;

void stopwatch::start()
{
	laps = 1;
	start_time = steady_clock::now();
}

void stopwatch::lap()
{
	laps++;
}

void stopwatch::stop()
{
	end_time = steady_clock::now();
}

void write_to_stream(std::stringstream& ss, const std::chrono::duration<double>& time)
{
	unsigned int mil_sec = duration_cast<milliseconds>(time).count() % 1000;
	unsigned int sec = duration_cast<seconds>(time).count() % 60;
	unsigned int min = duration_cast<minutes>(time).count() % 60;
	unsigned int hour = duration_cast<hours>(time).count();

	if(hour > 0)
		ss << std::setfill('0') << std::setw(2) << hour << ":";
	ss << std::setfill('0') << std::setw(2) << min << ":";
	ss << std::setfill('0') << std::setw(2) << sec << ":";
	ss << std::setfill('0') << std::setw(3) << mil_sec;
}

std::string stopwatch::total_str() const
{
	std::stringstream ss;

	auto time = (end_time - start_time);
	write_to_stream(ss, time);

	return ss.str();
}

std::string stopwatch::mean_str() const
{
	std::stringstream ss;

	auto time = (end_time - start_time) / laps;
	write_to_stream(ss, time);

	return ss.str();
}

std::ostream& sw::operator<<(std::ostream& out, const stopwatch& sw)
{
	out << "Total Time: " << sw.total_str();
	if(sw.laps != 1)
		out << "\nMean Time: " << sw.mean_str();
	return out;
}

