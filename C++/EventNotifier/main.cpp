#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "client.h"
#include "event_notifier.h"
#include "observer.h"

int main() {
    const int kWaitMseconds = 200;
    std::shared_ptr<EventNotifier> notifier = std::make_shared<EventNotifier>();
    std::shared_ptr<Observer> observers[Observer::kObserversNum];

    for (unsigned int idx = 0; idx < Observer::kObserversNum; idx++) {
        observers[idx] = std::make_shared<Observer>(idx, notifier.get());
        observers[idx]->SubscribeToNotification();
    }

    std::unique_ptr<Client> client = std::make_unique<Client>(notifier.get());

    client->SignalNotifiyer();

    // wait for the event notifier to finish
    std::chrono::milliseconds dura(kWaitMseconds);
    std::this_thread::sleep_for(dura);

    return 0;
}
