#include "HelloWorld.h"

namespace Thunder{
namespace Plugin{

    
    namespace {

        static Metadata<HelloWorld> metadata(
            // Version
            1, 0, 0,
            // Preconditions
            {subsystem::PLATFORM},
            // Terminations
            {},
            // Controls
            {}
        );
    }
    
const string HelloWorld::Initialize(PluginHost::IShell* service){

    std::string message;

    ASSERT(_service == nullptr);
    ASSERT(service != nullptr);
    //ASSERT(_impl == nullptr);

    _service = service;
    _service->AddRef();
    _service->Register(&_connectionNotification);

    _impl = _service->Root<Exchange::IHelloWorld>(_connectionId, 2000, _T("HelloWorldImplementation"));
    if (_impl == nullptr) {
         message = _T("Couldn't create volume control instance");
    } else {
        _impl->Register(&_helloNotification);
        std::cout << "Reached register helloworld" << std::endl;
        Exchange::JHelloWorld::Register(*this, _impl);
    }
    
    return message;
}

void HelloWorld::Deinitialize(PluginHost::IShell* service){

    if(_service != nullptr){
        ASSERT(_service == service);
    }

    _service -> Unregister(&_connectionNotification);

    if( _impl != nullptr){
        Exchange::JHelloWorld::Unregister(*this);
        _impl->Unregister(&_helloNotification);

        RPC::IRemoteConnection* connection(_service->RemoteConnection(_connectionId));
        VARIABLE_IS_NOT_USED uint32_t result = _impl->Release();
        _impl = nullptr;
        ASSERT(result == Core::ERROR_DESTRUCTION_SUCCEEDED);
        if (connection != nullptr) {
            connection->Terminate();
            connection->Release();
        }

    }

    std::cout << "Deinitialized HelloWorld" << std::endl;

    _service -> Release();
    _service = nullptr;
    _connectionId = 0;
}

void HelloWorld::Deactivated(RPC::IRemoteConnection* connection)
{
    if (connection->Id() == _connectionId) {
        ASSERT(_service != nullptr);
        Core::IWorkerPool::Instance().Submit(PluginHost::IShell::Job::Create(_service,
            PluginHost::IShell::DEACTIVATED,
            PluginHost::IShell::FAILURE));
        }
}

string HelloWorld::Information() const{
    return string();
};


} // Plugin
} // Thunder