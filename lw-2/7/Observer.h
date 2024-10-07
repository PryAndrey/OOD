#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <unordered_set>

struct WeakPtrCompare {
    template<typename T>
    bool operator()(const std::weak_ptr<T> &lhs, const std::weak_ptr<T> &rhs) const {
        return lhs.owner_before(rhs) || (!rhs.owner_before(lhs) && lhs.lock() < rhs.lock());
    }
};

template<typename T, typename ET>
class IObserver {
public:
    virtual void Update(T const &data, ET eventType) = 0;
    virtual ~IObserver() = default;
};

template<typename T, typename ET>
class IObservable {
public:
    virtual ~IObservable() = default;

    [[maybe_unused]] virtual void
    RegisterObserver(std::shared_ptr<IObserver<T, ET>> observer, ET eventType, int priority = 5) = 0;

    virtual void NotifyObservers() = 0;

    virtual void RemoveObserver(std::shared_ptr<IObserver<T, ET>> observer, ET eventType) = 0;
};

template<class T, typename ET>
class CObservable : public IObservable<T, ET> {
public:
    typedef IObserver<T, ET> ObserverType;

    void RegisterObserver(std::shared_ptr<ObserverType> observer, ET eventType, int priority = 5) override {
        auto prioritySet = m_observers.find(priority);
        if (prioritySet != m_observers.end()) {
            prioritySet->second.insert({observer});
        } else {
            m_observers[priority] = {observer};
        }
    }

    void NotifyObservers() override {
        T data = GetChangedData();
        auto observersCopy = m_observers;

        for (const auto &[priority, observers]: observersCopy) {
            for (const auto &observer: observers) {
                if (auto obs = observer.lock()) {
                    for (auto &event: obs.get()->GetEvents()) {
                        obs.get()->Update(data, event);
                    }
                }
            }
        }
    }

    void RemoveObserver(std::shared_ptr<ObserverType> observer, ET eventType) override {
        std::weak_ptr<ObserverType> tempWeak = observer;
        std::set<ET> events = observer->GetEvents();
        if (events.find(eventType) != events.end()) {
            observer->RemoveEvent(eventType);
        }
        if (auto obs = tempWeak.lock() || observer->GetEvents().empty()) {
            m_observers[observer.get()->GetPriority()].erase(tempWeak);
        }
    }

protected:
    virtual T GetChangedData() const = 0;

private:
    std::map<int, std::set<std::weak_ptr<ObserverType>>> m_observers;
};
