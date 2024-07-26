#include "HelloWorldImplementation.h"

namespace Thunder{
namespace Plugin{

    SERVICE_REGISTRATION(HelloWorldImplementation, 1, 0)

    HelloWorldImplementation::HelloWorldImplementation()
        : _adminLock()

    {
    }

    void HelloWorldImplementation::Register(Exchange::IHelloWorld::INotification* notification)
    {
        ASSERT(notification);

        _adminLock.Lock();
        auto item = std::find(_notifications.begin(), _notifications.end(), notification);
        ASSERT(item == _notifications.end());

        if (item == _notifications.end()) {
            notification->AddRef();
            _notifications.push_back(notification);
        }
        _adminLock.Unlock();
    }

    void HelloWorldImplementation::Unregister(const Exchange::IHelloWorld::INotification* notification)
    {
        ASSERT(notification);

        _adminLock.Lock();
        auto item = std::find(_notifications.begin(), _notifications.end(), notification);
        ASSERT(item != _notifications.end());

        if (item != _notifications.end()) {
            _notifications.erase(item);
            (*item)->Release();
        }
        _adminLock.Unlock();
    }

    uint32_t HelloWorldImplementation::PrintStuff(const string& randomWord) const{
        std::cout << randomWord << std::endl;
        NotifyPrintedString(randomWord);
        return Core::ERROR_NONE;
    }

    void HelloWorldImplementation::NotifyPrintedString(const string& randomWord) const{

        _adminLock.Lock();
        for (auto* notification : _notifications) {
            notification->Printed(randomWord);
        }
        _adminLock.Unlock();

    }
}
}