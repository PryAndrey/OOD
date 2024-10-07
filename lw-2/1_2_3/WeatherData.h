#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo {
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
};

class CStatistic {
public:
    void Update(double value) {
        m_minValue = std::min(m_minValue, value);
        m_maxValue = std::max(m_minValue, value);
        m_accValue += value;
        ++m_count;
    }

    [[nodiscard]] double GetMin() const { return m_minValue; }

    [[nodiscard]] double GetMax() const { return m_maxValue; }

    [[nodiscard]] double GetAverage() const { return (m_count != 0 ? m_accValue / m_count : 0); }

private:
    double m_minValue = std::numeric_limits<double>::infinity();
    double m_maxValue = -std::numeric_limits<double>::infinity();
    double m_accValue = 0;
    unsigned m_count = 0;
};

class CDisplay : public IObserver<SWeatherInfo> {
private:
    void Update(SWeatherInfo const &data) override {
		std::cout << "--------------------------------" << std::endl;
        std::cout << "Current params: " << std::endl;
        std::cout << "Temp=" << data.temperature;
        std::cout << " Hum=" << data.humidity;
        std::cout << " Pressure=" << data.pressure << std::endl;
		std::cout << "--------------------------------" << std::endl;
    }
};

class CStatsDisplay : public IObserver<SWeatherInfo> {
private:
    void Update(SWeatherInfo const &data) override {
        m_temperatureStatistics.Update(data.temperature);
        m_humidityStatistics.Update(data.humidity);
        m_pressureStatistics.Update(data.pressure);

        std::cout << "--------------------------------" << std::endl;
        std::cout << "Max Temp: " << m_temperatureStatistics.GetMax() << std::endl;
        std::cout << "Min Temp: " << m_temperatureStatistics.GetMin() << std::endl;
        std::cout << "Average Temp: " << m_temperatureStatistics.GetAverage() << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "Max Humidity: " << m_humidityStatistics.GetMax() << std::endl;
        std::cout << "Min Humidity: " << m_humidityStatistics.GetMin() << std::endl;
        std::cout << "Average Humidity: " << m_humidityStatistics.GetAverage() << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "Max Pressure: " << m_pressureStatistics.GetMax() << std::endl;
        std::cout << "Min Pressure: " << m_pressureStatistics.GetMin() << std::endl;
        std::cout << "Average Pressure: " << m_pressureStatistics.GetAverage() << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }

    CStatistic m_temperatureStatistics;
    CStatistic m_humidityStatistics;
    CStatistic m_pressureStatistics;
};

class CWeatherData : public CObservable<SWeatherInfo> {
public:
    [[nodiscard]] double GetTemperature() const {
        return m_temperature;
    }

    [[nodiscard]] double GetHumidity() const {
        return m_humidity;
    }

    [[nodiscard]] double GetPressure() const {
        return m_pressure;
    }

    void MeasurementsChanged() {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure) {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;

        MeasurementsChanged();
    }

protected:
    [[nodiscard]] SWeatherInfo GetChangedData() const override {
        SWeatherInfo info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        return info;
    }

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
};
