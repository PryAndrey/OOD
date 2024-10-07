#include "WeatherData.h"

int main()
{
	CWeatherDataDuoPro weatherDataIn;
	CWeatherDataDuoPro weatherDataOut;

	CDisplay display(&weatherDataIn, &weatherDataOut);
    CStatsDisplay statsDisplay(&weatherDataIn, &weatherDataOut);

	weatherDataIn.RegisterObserver(display);
	weatherDataIn.RegisterObserver(statsDisplay);
	weatherDataOut.RegisterObserver(display);
	weatherDataOut.RegisterObserver(statsDisplay);

	weatherDataIn.SetMeasurements(3, 0.7, 760, 10, 90);
	weatherDataOut.SetMeasurements(4, 0.8, 761, 10, 0);
    weatherDataIn.SetMeasurements(3, 0.7, 760, 10, 200);
    weatherDataIn.SetMeasurements(3, 0.7, 760, 10, 359);
    weatherDataIn.SetMeasurements(3, 0.7, 760, 10, 90);

    return 0;
}