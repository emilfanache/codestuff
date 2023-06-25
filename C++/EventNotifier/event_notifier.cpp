#include <algorithm>
#include <limits>
#include <random>

#include "EventNotifier/event_notifier.h"

EventNotifier::EventNotifier() {
    ntf_thread_ = std::thread(&EventNotifier::NotificationThread, this);
    done_.store(false);
}

EventNotifier::~EventNotifier() {
    done_.store(true);
    cv_.notify_one();
    ntf_thread_.join();
}

void EventNotifier::AddObserver(Observer* obs) {
    observers_.push_back(obs);
}

void EventNotifier::RemoveObserver(Observer* obs) {
    observers_.erase(std::find(observers_.begin(), observers_.end(), obs));
}

std::shared_ptr<Notification> EventNotifier::BuildNotification(
    const std::string& message) {
    int notification_id = 0;
    std::shared_ptr<Notification> ntf = std::make_shared<Notification>();
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(0, 50000);
    std::cout << "[BuildNotification] message: " << message.c_str()
              << std::endl;
    ntf->id = dist(mt);
    ntf->description = message;

    std::cout << "[EventNotifier] ntf->description: "
              << ntf->description.c_str() << std::endl;
    return ntf;
}

void EventNotifier::NotificationThread() {
    while (!done_.load()) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock);

        // if the destructor awaked the thread, stop processing further
        if (done_.load()) {
            return;
        }
        std::pair<std::string, std::bitset<32>> client_data =
            ntf_queue_.front();
        std::shared_ptr<Notification> ntf =
            BuildNotification(client_data.first);
        NotifyObservers(ntf, client_data.second);
        ntf_queue_.pop();
    }
}

void EventNotifier::PushNotificationEvent(const std::string& message,
                                          const std::bitset<32>& receivers) {
    std::unique_lock<std::mutex> lock(mutex_);
    ntf_queue_.push(std::make_pair(message, receivers));
    cv_.notify_one();
}

void EventNotifier::NotifyObservers(std::shared_ptr<Notification> ntf,
                                    const std::bitset<32>& receivers) {
    for (auto obs : observers_) {
        if (receivers.test(obs->GetId())) {
            std::cout << "[EventNotifier] Sending event to observer id: "
                      << obs->GetId() << std::endl;
            obs->Update(ntf.get());
        }
    }
}
