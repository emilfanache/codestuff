#ifndef EVENT_NOTIFIER_H
#define EVENT_NOTIFIER_H

#include <atomic>
#include <bitset>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "observer.h"

class Observer;

struct Notification {
    uint32_t id;
    std::string description;
};

class EventNotifier {
 public:
    EventNotifier();
    ~EventNotifier();
    void AddObserver(Observer* obs);
    void RemoveObserver(Observer* obs);
    void NotifyObservers(std::shared_ptr<Notification>,
                         const std::bitset<32>& receivers);
    std::shared_ptr<Notification> BuildNotification(
        const std::string& description);
    void NotificationThread();
    void PushNotificationEvent(const std::string& message,
                               const std::bitset<32>& receivers);

 private:
    Notification notification_;
    std::vector<Observer*> observers_;
    std::thread ntf_thread_;
    std::queue<std::pair<std::string, std::bitset<32>>> ntf_queue_;
    std::condition_variable cv_;
    std::atomic<bool> done_;
    std::mutex mutex_;
};

#endif  // EVENT_NOTIFIER_H
