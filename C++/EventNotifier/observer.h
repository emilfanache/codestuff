#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <string>
#include "event_notifier.h"

class EventNotifier;
struct Notification;

class Observer {
 public:
    static constexpr uint8_t kObserversNum = 10;
    Observer(uint8_t id, EventNotifier* ev_ntf) : id_(id), ev_ntf_(ev_ntf) {}

    void Update(Notification* nf);
    void SubscribeToNotification();
    void UnsubscribeFromNotification();
    const std::string& GetInfo();
    void PrintInfo();
    uint32_t GetId();

 private:
    std::string info_;
    uint32_t id_;
    EventNotifier* ev_ntf_;
};

#endif  // OBSERVER_H
