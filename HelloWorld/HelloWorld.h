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

#include "Module.h"
#include "interfaces/IHelloWorld.h"
#include "interfaces/json/JHelloWorld.h"

namespace Thunder{
namespace Plugin{
    class HelloWorld : public PluginHost::IPlugin, public PluginHost::JSONRPC{
    public:
        HelloWorld(const HelloWorld&) = delete;
        HelloWorld& operator=(const HelloWorld&) = delete;

        HelloWorld()
        : _service(nullptr),
          _impl(nullptr),
          _connectionId(0),
          _connectionNotification(this),
          _helloNotification(this)
        {
        }

        ~HelloWorld() override
        {
        }

        BEGIN_INTERFACE_MAP(HelloWorld)
        INTERFACE_ENTRY(PluginHost::IPlugin)
        INTERFACE_ENTRY(PluginHost::IDispatcher)
        INTERFACE_AGGREGATE(Exchange::IHelloWorld, _impl);
        END_INTERFACE_MAP

        void SendMessage();

        //  IPlugin Methods
        const string Initialize(PluginHost::IShell* service) override;
        void Deinitialize(PluginHost::IShell* service) override;
        string Information() const override;

        
    private:

        class ConnectionNotification : public RPC::IRemoteConnection::INotification {
        public:
            explicit ConnectionNotification(HelloWorld* parent)
                : _parent(*parent)
            {
                ASSERT(parent != nullptr);
            }

            ~ConnectionNotification() override = default;

            ConnectionNotification() = delete;
            ConnectionNotification(const ConnectionNotification&) = delete;
            ConnectionNotification& operator=(const ConnectionNotification&) = delete;

            void Activated(RPC::IRemoteConnection* connection) override
            {
            }

            void Deactivated(RPC::IRemoteConnection* connection) override
            {
                _parent.Deactivated(connection);
            }

            BEGIN_INTERFACE_MAP(ConnectionNotification)
                INTERFACE_ENTRY(RPC::IRemoteConnection::INotification)
            END_INTERFACE_MAP

        private:
            HelloWorld& _parent;
        };
        
        class HelloNotification : public Exchange::IHelloWorld::INotification{ 
          public:
            explicit HelloNotification(HelloWorld *parent) 
              : _parent(*parent)
              {
                ASSERT(parent != nullptr);
              }

            ~HelloNotification() override = default;

            HelloNotification() = delete;
            HelloNotification(const HelloNotification&) = delete;
            HelloNotification& operator=(const HelloNotification&) = delete;

            void Printed(const string& word) const override
            {
              std::cout << "calledbeforejhello";
              Exchange::JHelloWorld::Event::Printed(_parent, word);
              
            }

            BEGIN_INTERFACE_MAP(VolumeNotification)
                INTERFACE_ENTRY(Exchange::IHelloWorld::INotification)
            END_INTERFACE_MAP

          private:
            HelloWorld& _parent;            
        };

        void Deactivated(RPC::IRemoteConnection* connection);
                
        PluginHost::IShell* _service;
        Exchange::IHelloWorld* _impl;
        Core::SinkType<HelloNotification> _helloNotification;
        Core::SinkType<ConnectionNotification> _connectionNotification;
        uint32_t _connectionId;
                    
    };

} // namespace Plugin
} // namespace Thunder