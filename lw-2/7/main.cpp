#include "WeatherData.h"
#include <memory>

int main() {
    CWeatherData weatherData;

    std::shared_ptr<CDisplay> display = std::make_shared<CDisplay>();
    weatherData.RegisterObserver(display, EventType::Temperature, 2);

    {
        std::shared_ptr<CStatsDisplay> statsDisplay = std::make_shared<CStatsDisplay>();
        weatherData.RegisterObserver(statsDisplay, EventType::Temperature);
        weatherData.RegisterObserver(statsDisplay, EventType::Pressure);
        weatherData.SetMeasurements(3, 0.7, 760, 10, 90);
    }

    weatherData.SetMeasurements(4, 0.8, 761, 10, 90);

    weatherData.RemoveObserver(display, EventType::Temperature);

    weatherData.SetMeasurements(10, 0.8, 761, 10, 90);
    weatherData.SetMeasurements(-10, 0.8, 761, 10, 90);
    return 0;
}