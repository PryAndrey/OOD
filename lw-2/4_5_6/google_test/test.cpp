#include "../WeatherData.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockWeatherDataDuo : public CObservable<SWeatherInfo>
{
public:
	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		MeasurementsChanged();
	}

	MOCK_METHOD(SWeatherInfo, GetChangedData, (), (const override));
};

TEST(WeatherStationDuoTest, SimTest)
{
	MockWeatherDataDuo weatherDataIn;
	MockWeatherDataDuo weatherDataOut;

	CDisplay display(&weatherDataIn, &weatherDataOut);

	weatherDataIn.RegisterObserver(display);
	weatherDataOut.RegisterObserver(display);

	EXPECT_CALL(weatherDataIn, GetChangedData()).Times(1);
	EXPECT_CALL(weatherDataOut, GetChangedData()).Times(2);

	weatherDataOut.SetMeasurements(3, 0.7, 760);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
