#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include "Observer.h"

enum class EventType {
    Temperature,
    Pressure,
    Humidity,
    WindSpeed,
    WindDirection
};

struct SWeatherInfo {
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
    double windSpeed = 0;
    double windDirection = 0;
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

    [[nodiscard]] std::string ToString(const std::string &parameterName) const {
        std::string temp = parameterName + ":"
                           + " Max=" + std::to_string(GetMax())
                           + " Min=" + std::to_string(GetMin())
                           + " Average=" + std::to_string(GetAverage());
        return temp;
    }

private:
    double m_minValue = std::numeric_limits<double>::infinity();
    double m_maxValue = -std::numeric_limits<double>::infinity();
    double m_accValue = 0;
    unsigned m_count = 0;
};

class CWindStatistic {
public:
    void Update(double windSpeed, double direction) {
        ++m_count;
        m_minSpeed = std::min(m_minSpeed, windSpeed);
        m_maxSpeed = std::max(m_maxSpeed, windSpeed);
        m_sumSpeed += windSpeed;

        double radians = direction * M_PI / 180.0; // Convert to radians
        m_sumX += cos(radians);
        m_sumY += sin(radians);
    }

    [[nodiscard]] double GetMin() const { return m_minSpeed; }

    [[nodiscard]] double GetMax() const { return m_maxSpeed; }

    [[nodiscard]] double GetAverageSpeed() const { return (m_count != 0 ? m_sumSpeed / m_count : 0); }

    [[nodiscard]] double GetAverageDirection() const {
        if (m_count == 0) {
            return 0;
        }
        double averageX = m_sumX / m_count;
        double averageY = m_sumY / m_count;
        double averageDirection = atan2(averageY, averageX) * 180.0 / M_PI; // Convert to degrees
        if (averageDirection < 0) {
            averageDirection += 360.0;
        }
        return averageDirection;
    }

private:
    unsigned m_count = 0;
    double m_minSpeed = std::numeric_limits<double>::infinity();
    double m_maxSpeed = -std::numeric_limits<double>::infinity();
    double m_sumSpeed = 0;
    double m_sumX = 0.0;
    double m_sumY = 0.0;
};

class CDisplay : public IObserver<SWeatherInfo, EventType> {
private:
    void Update(SWeatherInfo const &data, EventType eventType) override {
        switch (eventType) {
            case EventType::Temperature: {
                std::cout << "Current temp=" << data.temperature << std::endl;
                break;
            }
            case EventType::Pressure: {
                std::cout << "Current pressure=" << data.pressure << std::endl;
                break;
            }
            case EventType::Humidity: {
                std::cout << "Current humidity=" << data.humidity << std::endl;
                break;
            }
            case EventType::WindDirection: {
                std::cout << "Current wind direction=" << data.windDirection << std::endl;
                break;
            }
            case EventType::WindSpeed: {
                std::cout << "Current wind speed=" << data.windSpeed << std::endl;
                break;
            }
            default: {
                std::cout << "Unknown type" << std::endl;
            }
        }
    }
};

class CStatsDisplay : public IObserver<SWeatherInfo, EventType> {
private:
    void Update(SWeatherInfo const &data, EventType eventType) override {
        switch (eventType) {
            case EventType::Temperature: {
                m_temperatureStatistics.Update(data.temperature);
                std::cout << m_temperatureStatistics.ToString("Temp") << std::endl;
                break;
            }
            case EventType::Pressure: {
                m_pressureStatistics.Update(data.pressure);
                std::cout << m_pressureStatistics.ToString("Pressure") << std::endl;
                break;
            }
            case EventType::Humidity: {
                m_humidityStatistics.Update(data.humidity);
                std::cout << m_humidityStatistics.ToString("Humidity") << std::endl;
                break;
            }
            case EventType::WindDirection: {
                std::cout << "Wind:";
                std::cout << " Max=" << m_windStatistics.GetMax();
                std::cout << " Min=" << m_windStatistics.GetMin();
                std::cout << " AverageDirection=" << m_windStatistics.GetAverageDirection() << std::endl;
                break;
            }
            case EventType::WindSpeed: {
                std::cout << "Wind:";
                std::cout << " Max=" << m_windStatistics.GetMax();
                std::cout << " Min=" << m_windStatistics.GetMin();
                std::cout << " AverageSpeed=" << m_windStatistics.GetAverageSpeed() << std::endl;
                break;
            }
            default: {
                std::cout << "Unknown type" << std::endl;
            }
        }
    }

    CStatistic m_temperatureStatistics;
    CStatistic m_humidityStatistics;
    CStatistic m_pressureStatistics;
    CWindStatistic m_windStatistics;
};

class CWeatherData : public CObservable<SWeatherInfo, EventType> {
public:
    [[nodiscard]] double GetTemperature() const { return m_temperature; }

    [[nodiscard]] double GetHumidity() const { return m_humidity; }

    [[nodiscard]] double GetPressure() const { return m_pressure; }

    [[nodiscard]] double GetWindSpeed() const { return m_windSpeed; }

    [[nodiscard]] double GetWindDirection() const { return m_windDirection; }

    void MeasurementsChanged() {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection) {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;
        m_windSpeed = windSpeed;
        m_windDirection = windDirection;

        MeasurementsChanged();
    }

protected:
    [[nodiscard]] SWeatherInfo GetChangedData() const override {
        SWeatherInfo info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        info.windSpeed = GetWindSpeed();
        info.windDirection = GetWindDirection();
        return info;
    }

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
    double m_windSpeed = 0.0;
    double m_windDirection = 0.0;
};
