/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>

#include "Module.h"
#include <interfaces/IHelloWorld.h>

namespace Thunder {
namespace Plugin {

    class HelloWorldImplementation : public Exchange::IHelloWorld {
    public:
        HelloWorldImplementation(const HelloWorldImplementation&) = delete;
        HelloWorldImplementation& operator=(const HelloWorldImplementation&) = delete;

        HelloWorldImplementation();
        ~HelloWorldImplementation() override = default;

        BEGIN_INTERFACE_MAP(HelloWorldImplementation)
            INTERFACE_ENTRY(Exchange::IHelloWorld)
        END_INTERFACE_MAP

        // Exchange::IHelloWorld Methods
        void Register(Exchange::IHelloWorld::INotification* observer) override;
        void Unregister(const Exchange::IHelloWorld::INotification* observer) override;

        uint32_t PrintStuff(const string &randomWord) const override;

    private:
        mutable Core::CriticalSection _adminLock;
        std::vector<Exchange::IHelloWorld::INotification*> _notifications;

        void NotifyPrintedString(const string& word) const;
    };
    

} // namespace Plugin
} // namespace Thunder

 