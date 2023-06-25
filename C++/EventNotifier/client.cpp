#include <random>

#include "client.h"
#include "observer.h"

Client::Client(EventNotifier* ev_ntf) : ev_ntf_(ev_ntf) {
    GenerateString();
    GenerateObserversMask();
}

void Client::GenerateString() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(kStartAsciiLetters,
                                            kEndAsciiLetters);

    for (uint8_t idx = 0; idx < kStringSize; idx++) {
        rand_string_ += dist(mt);
    }

    std::cout << "[Client] rand_string_ " << rand_string_ << std::endl;
}

void Client::GenerateObserversMask() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, Observer::kObserversNum - 1);

    // being a small subset, the same random value will be generated multiple times
    // giving a different subset for each execution
    for (uint8_t idx = 0; idx < Observer::kObserversNum; idx++) {
        observer_mask_.set(dist(mt));
    }
    std::cout << "[Client] observer_mask_ " << observer_mask_ << std::endl;
}

void Client::SignalNotifiyer() {
    ev_ntf_->PushNotificationEvent(rand_string_, observer_mask_);
}
