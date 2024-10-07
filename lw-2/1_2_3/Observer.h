#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <unordered_set>

struct WeakPtrCompare
{
	template <typename T>
	bool operator()(const std::weak_ptr<T>& lhs, const std::weak_ptr<T>& rhs) const
	{
        //выяснить
		return lhs.owner_before(rhs) || (!rhs.owner_before(lhs) && lhs.lock() < rhs.lock());
	}
};

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;

	virtual ~IObserver() = default;

	void SetPriority(int priority)
	{
		m_priority = priority;
	}
	int GetPriority()
	{
		return m_priority;
	}

protected:
	int m_priority = 5;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;

	[[maybe_unused]] virtual void RegisterObserver(std::shared_ptr<IObserver<T>> observer, int priority = 5) = 0;

	virtual void NotifyObservers() = 0;

	virtual void RemoveObserver(std::shared_ptr<IObserver<T>> observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(std::shared_ptr<ObserverType> observer, int priority = 5) override
	{
		observer.get()->SetPriority(priority);
		auto prioritySet = m_observers.find(priority);
		if (prioritySet != m_observers.end())
		{
			prioritySet->second.insert(observer);
		}
		else
		{
			m_observers[priority] = { observer };
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
        //можно фгещ
		std::map<int, std::set<std::weak_ptr<ObserverType>, WeakPtrCompare>> observersCopy = m_observers;

        /// Запомнить итератор и с ним работать(в RegisterObserver)- done
		/// можно через вектор - done
		/// безопасное удаление
		for (auto it = observersCopy.rbegin(); it != observersCopy.rend(); ++it)
		{
			for (const auto& observer : it->second)
			{
                //удаляем
				if (auto obs = observer.lock())
				{
					obs.get()->Update(data);
				}
			}
		}
	}

	void RemoveObserver(std::shared_ptr<ObserverType> observer) override
	{
		std::weak_ptr<ObserverType> tempWeak = observer;
		if (auto obs = tempWeak.lock())
		{
			m_observers[observer.get()->GetPriority()].erase(tempWeak);
		}
	}

protected:
	virtual T GetChangedData() const = 0;

private:
    //вынести приоритет
	std::map<int, std::set<std::weak_ptr<ObserverType>, WeakPtrCompare>> m_observers;
};
