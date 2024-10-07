#include "../WeatherData.h"
#include <gtest/gtest.h>

class CObserverWithRemoveUpdate : public IObserver<SWeatherInfo>
{
public:
	explicit CObserverWithRemoveUpdate(CObservable<SWeatherInfo>& observable)
		: m_observable(observable)
	{
	}

	void Update(SWeatherInfo const& data) override
	{
		m_observable.RemoveObserver(*this);
	}

private:
	CObservable<SWeatherInfo>& m_observable;
};

class CObserverWithOrderedUpdate : public IObserver<SWeatherInfo>
{
public:
	CObserverWithOrderedUpdate(std::vector<int>& callOrder, int id)
		: m_callOrder(callOrder)
		, m_id(id)
	{
	}

	void Update(SWeatherInfo const& data) override
	{
		m_callOrder.push_back(m_id);
	}

private:
	std::vector<int>& m_callOrder;
	int m_id;
};

TEST(ObserverTests, SafeNotificationTest)
{
	CWeatherData weatherData;

	CDisplay display;
	CObserverWithRemoveUpdate testObserver(weatherData);

	weatherData.RegisterObserver(display);
	weatherData.RegisterObserver(testObserver);

	CStatsDisplay statsDisplay;
	weatherData.RegisterObserver(statsDisplay, 1);

	weatherData.SetMeasurements(10, 0.8, 761);
	weatherData.SetMeasurements(-10, 0.8, 761);
}

TEST(WeatherStationTest, PriorityTest)
{
	CWeatherData weatherData;

	std::vector<int> callOrder;

	CObserverWithOrderedUpdate observer1(callOrder, 1);
	CObserverWithOrderedUpdate observer2(callOrder, 2);

	weatherData.RegisterObserver(observer1, 3);
	weatherData.RegisterObserver(observer2, 5);

	weatherData.SetMeasurements(10, 0.8, 761);

	EXPECT_EQ(callOrder.size(), 2);
	EXPECT_EQ(callOrder[0], 2);
	EXPECT_EQ(callOrder[1], 1);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
