#pragma once

#include "Observer.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

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
        m_sumValue += value;
        ++m_count;
    }

    [[nodiscard]] double GetMin() const { return m_minValue; }

    [[nodiscard]] double GetMax() const { return m_maxValue; }

    [[nodiscard]] double GetAverage() const { return (m_count != 0 ? m_sumValue / m_count : 0); }

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
    double m_sumValue = 0;
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
        double averageDirection = atan2(averageY, averageX) * 180.0 / M_PI;
        if (averageDirection < 0) {
            averageDirection += 360.0;
        }
        return averageDirection;
    }

    [[nodiscard]] std::string ToString(const std::string &parameterName) const {
        std::string temp = parameterName + ":"
                           + " Max=" + std::to_string(GetMax())
                           + " Min=" + std::to_string(GetMin())
                           + " AverageSpeed=" + std::to_string(GetAverageSpeed());
                           + " AverageDirection=" + std::to_string(GetAverageDirection());
        return temp;
    }

private:
    unsigned m_count = 0;
    double m_minSpeed = std::numeric_limits<double>::infinity();
    double m_maxSpeed = -std::numeric_limits<double>::infinity();
    double m_sumSpeed = 0;
    double m_sumX = 0.0;
    double m_sumY = 0.0;
};

class CDisplay : public IObserver<SWeatherInfo> {

public:
    CDisplay(CObservable<SWeatherInfo> *weatherDataIn, CObservable<SWeatherInfo> *weatherDataOut)
            : m_weatherDataIn(weatherDataIn), m_weatherDataOut(weatherDataOut) {
    }

private:
    void Update(IObservable<SWeatherInfo> *observer) override {
        SWeatherInfo dataIn = m_weatherDataIn->GetChangedData();
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Current params In:";
        std::cout << " Temp=" << dataIn.temperature;
        std::cout << " Hum=" << dataIn.humidity;
        std::cout << " Pressure=" << dataIn.pressure << std::endl;
        std::cout << "--------------------------------" << std::endl;
        SWeatherInfo dataOut = m_weatherDataOut->GetChangedData();
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Current params Out:";
        std::cout << " Temp=" << dataOut.temperature;
        std::cout << " Hum=" << dataOut.humidity;
        std::cout << " Pressure=" << dataOut.pressure;
        std::cout << " WindSpeed=" << dataOut.windSpeed;
        std::cout << " WindDirection=" << dataOut.windDirection << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }

    const CObservable<SWeatherInfo> *m_weatherDataIn;
    const CObservable<SWeatherInfo> *m_weatherDataOut;
};

class CStatsDisplay : public IObserver<SWeatherInfo> {
public:
    CStatsDisplay(CObservable<SWeatherInfo> *weatherDataIn, CObservable<SWeatherInfo> *weatherDataOut)
            : m_weatherDataIn(weatherDataIn), m_weatherDataOut(weatherDataOut) {
    }

private:
    void Update(IObservable<SWeatherInfo> *observer) override {
        if (observer == m_weatherDataIn) {
            SWeatherInfo dataIn = m_weatherDataIn->GetChangedData();
            m_temperatureStatisticsIn.Update(dataIn.temperature);
            m_humidityStatisticsIn.Update(dataIn.humidity);
            m_pressureStatisticsIn.Update(dataIn.pressure);
        }

        std::cout << "--------------------------------" << std::endl;
        std::cout << "StationType: In" << std::endl;
        std::cout << m_temperatureStatisticsIn.ToString("Temp") << std::endl;
        std::cout << m_humidityStatisticsIn.ToString("Humidity") << std::endl;
        std::cout << m_pressureStatisticsIn.ToString("Pressure") << std::endl;

        std::cout << std::endl;
        if (observer == m_weatherDataOut) {
            SWeatherInfo dataOut = m_weatherDataOut->GetChangedData();

            m_temperatureStatisticsOut.Update(dataOut.temperature);
            m_humidityStatisticsOut.Update(dataOut.humidity);
            m_pressureStatisticsOut.Update(dataOut.pressure);
            m_windStatisticOut.Update(dataOut.windSpeed, dataOut.windDirection);
        }
        ///дублирование - done

        std::cout << m_temperatureStatisticsOut.ToString("Temp") << std::endl;
        std::cout << m_humidityStatisticsOut.ToString("Humidity") << std::endl;
        std::cout << m_pressureStatisticsOut.ToString("Pressure") << std::endl;
        std::cout << m_windStatisticOut.ToString("Wind") << std::endl;
    }

    CStatistic m_temperatureStatisticsIn;
    CStatistic m_humidityStatisticsIn;
    CStatistic m_pressureStatisticsIn;

    CStatistic m_temperatureStatisticsOut;
    CStatistic m_humidityStatisticsOut;
    CStatistic m_pressureStatisticsOut;
    CWindStatistic m_windStatisticOut;

    const CObservable<SWeatherInfo> *m_weatherDataIn;
    const CObservable<SWeatherInfo> *m_weatherDataOut;
};

class CWeatherDataDuoPro : public CObservable<SWeatherInfo> {
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
