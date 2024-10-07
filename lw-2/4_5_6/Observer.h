#pragma once

#include "WeatherData.h"
#include <functional>
#include <map>
#include <set>

template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
    ///интерфейс - done
	virtual void Update(IObservable<T>* observer) = 0;

	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;

	[[maybe_unused]] virtual void RegisterObserver(IObserver<T>& observer, int priority = 5) = 0;

	virtual void NotifyObservers() = 0;

	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority = 5) override
	{
		if (m_observers.find(&observer) != m_observers.end())
		{
			m_observers.at(&observer) = (priority);
		}
		else
		{
			m_observers[&observer] = priority;
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observersCopy = m_observers;
		std::map<int, std::set<ObserverType*>> observersTemp;

		for (const auto& [observer, priority] : m_observers)
		{
			observersTemp[priority].insert(observer);
		}

		for (auto it = observersTemp.rbegin(); it != observersTemp.rend(); ++it)
		{
			for (const auto& observer : it->second)
			{
				observer->Update(this);
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(&observer);
	}

	virtual T GetChangedData() const = 0;

private:
	std::map<ObserverType*, int> m_observers;
};
