#ifndef __FRONTPANEL_H
#define __FRONTPANEL_H

#include "Module.h"
#include "FrontPanelHAL.h"

namespace WPEFramework {
namespace Plugin {

    class FrontPanel : public PluginHost::IPlugin, public PluginHost::IWeb {
    public:
        class Config : public Core::JSON::Container {
        private:
            Config(const Config&) = delete;
            Config& operator=(const Config&) = delete;

        public:
            Config()
                : Core::JSON::Container()
                , Indicator()
                , BlinkDuration()
                , BlinkIterations()
                , Brightness()
                , State()
                , StateStr()
                , Color()
                , ColorStr()
                , TimeFormat()
                , TimeFormatStr()
                , Hour()
                , Minutes()
                , Text()
                , TextDisplay()
                , Enable()
                , ScrollHoldOnDur()
                , HorzScrollIterations()
                , VertScrollIterations()
                , ToPersist()
            {
                Add(_T("Indicator"), &Indicator);
                Add(_T("BlinkDuration"), &BlinkDuration);
                Add(_T("BlinkIterations"), &BlinkIterations);
                Add(_T("Brightness"), &Brightness);
                Add(_T("State"), &State);
                Add(_T("State"), &StateStr);
                Add(_T("Color"), &Color);
                Add(_T("Color"), &ColorStr);
                Add(_T("TimeFormat"), &TimeFormat);
                Add(_T("TimeFormat"), &TimeFormatStr);
                Add(_T("Hour"), &Hour);
                Add(_T("Minutes"), &Minutes);
                Add(_T("Text"), &Text);
                Add(_T("TextDisplay"), &TextDisplay);
                Add(_T("Enable"), &Enable);
                Add(_T("ScrollHoldOnDur"), &ScrollHoldOnDur);
                Add(_T("HorzScrollIterations"), &HorzScrollIterations);
                Add(_T("VertScrollIterations"), &VertScrollIterations);
                Add(_T("ToPersist"), &ToPersist);
            }
            ~Config()
            {
            }

        public:
            Core::JSON::DecUInt32 Indicator;
            Core::JSON::DecUInt32 BlinkDuration;
            Core::JSON::DecUInt32 BlinkIterations;
            Core::JSON::DecUInt32 Brightness;
            Core::JSON::DecUInt32 State;
            Core::JSON::String StateStr;
            Core::JSON::DecUInt32 Color;
            Core::JSON::String ColorStr;
            Core::JSON::DecUInt32 TimeFormat;
            Core::JSON::String TimeFormatStr;
            Core::JSON::DecUInt32 Hour;
            Core::JSON::DecUInt32 Minutes;
            Core::JSON::String Text;
            Core::JSON::DecUInt32 TextDisplay;
            Core::JSON::DecUInt32 Enable;
            Core::JSON::DecUInt32 ScrollHoldOnDur;
            Core::JSON::DecUInt32 HorzScrollIterations;
            Core::JSON::DecUInt32 VertScrollIterations;
            Core::JSON::Boolean ToPersist;
        };
    private:
        FrontPanel(const FrontPanel&) = delete;
        FrontPanel& operator=(const FrontPanel&) = delete;

    public:
        FrontPanel()
            : _skipURL(0)
            , _service(nullptr)
        {
        }

        virtual ~FrontPanel()
        {
        }

        BEGIN_INTERFACE_MAP(FrontPanel)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_ENTRY(PluginHost::IWeb)
        END_INTERFACE_MAP

    public:
        //   IPlugin methods
        // -------------------------------------------------------------------------------------------------------
        virtual const string Initialize(PluginHost::IShell* service);
        virtual void Deinitialize(PluginHost::IShell* service);
        virtual string Information() const;

        //   IWeb methods
        // -------------------------------------------------------------------------------------------------------
        virtual void Inbound(Web::Request& request) override;
        virtual Core::ProxyType<Web::Response> Process(const Web::Request& request) override;

    private:
        Core::ProxyType<Web::Response> GetMethod(Core::TextSegmentIterator& index, const Web::Request& request);
        Core::ProxyType<Web::Response> PostMethod(Core::TextSegmentIterator& index, const Web::Request& request);
        Core::ProxyType<Web::Response> DeleteMethod(Core::TextSegmentIterator& index);

    private:
        uint8_t _skipURL;
        PluginHost::IShell* _service;
        Core::ProxyType<FrontPanelHAL> _controller;
    };

} // Namespace Plugin.
}

#endif // __FRONTPANEL_H
