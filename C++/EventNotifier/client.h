#ifndef CLIENT_H
#define CLIENT_H

#include <bitset>
#include <iostream>
#include <string>

#include "client.h"
#include "event_notifier.h"

class EventNotifier;

class Client {
   public:
    explicit Client(EventNotifier* ev_ntf);
    ~Client() = default;
    void SignalNotifiyer();

   private:
    void GenerateString();
    void GenerateObserversMask();

    static constexpr int kStartAsciiLetters = 97;
    static constexpr int kEndAsciiLetters = 122;
    static constexpr int kStringSize = 20;

    std::string rand_string_;
    std::bitset<32> observer_mask_;
    EventNotifier* ev_ntf_;
};

#endif  // CLIENT_H
