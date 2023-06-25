#include "EventNotifier/observer.h"

void Observer::SubscribeToNotification() {
    ev_ntf_->AddObserver(this);
}
void Observer::UnsubscribeFromNotification() {
    ev_ntf_->RemoveObserver(this);
}

void Observer::Update(Notification* nf) {
    std::cout << "[Observer] Received notification for observer id: " << id_
              << std::endl;
    std::cout << "[Observer] notification id: " << nf->id << std::endl;
    std::cout << "[Observer] description: " << nf->description.c_str()
              << std::endl;
    info_ = nf->description;
}

const std::string& Observer::GetInfo() {
    return info_;
}

void Observer::PrintInfo() {
    std::cout << "Info: " << info_.c_str() << std::endl;
}

uint32_t Observer::GetId() {
    return id_;
}
