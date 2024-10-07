#include "WeatherData.h"
#include <memory>

int main()
{
	CWeatherData weatherData;

	std::shared_ptr<CDisplay> display = std::make_shared<CDisplay>();
	weatherData.RegisterObserver(display, 2);

	{
		std::shared_ptr<CStatsDisplay> statsDisplay = std::make_shared<CStatsDisplay>();
		weatherData.RegisterObserver(statsDisplay);
		weatherData.SetMeasurements(3, 0.7, 760);
	}

	weatherData.SetMeasurements(4, 0.8, 761);

	weatherData.RemoveObserver(display);

	weatherData.SetMeasurements(10, 0.8, 761);
	weatherData.SetMeasurements(-10, 0.8, 761);
	return 0;
}