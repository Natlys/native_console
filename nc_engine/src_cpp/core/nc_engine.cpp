#include "nc_pch.hpp"
#include "nc_engine.h"

#include <core/nc_engine_state.h>

#include <graphics/gcontext/nc_cwindow.h>
#include <graphics/control/nc_Drawer.h>

#include <systems/nc_ev_sys.h>
#include <systems/nc_io_sys.h>
#include <systems/nc_time_sys.h>
#include <systems/nc_log_sys.h>

namespace NC
{
    Engine::Engine() :
        m_strName("nc_application"),
        m_pWindow(nullptr),
        m_pCurrState(nullptr),
        m_bIsRunning(false) { }
    Engine::~Engine() { }

    // --getters
    inline EngineState* Engine::GetState(const char* strName) {
        if (m_States.size() == 0) return nullptr;
        auto itState = FIND_BY_FUNC_NAME(m_States, EngineState*, strName, ->GetName);
        if (itState == m_States.end()) return nullptr;
        return *itState;
    }
    // --setters
    void Engine::AddState(EngineState* pState)
    {
        if (!pState->Init()) { Quit(); }
        m_States.push_back(pState);
        if (m_pCurrState == nullptr) { SwitchState(pState->GetName()); }
    }
    void Engine::RemoveState(const char* strName)
    {
        auto itState = FIND_BY_FUNC_NAME(m_States, EngineState*, strName, ->GetName);
        if (itState == m_States.end()) return;
        EngineState* pState = *itState;
        pState->OnDisable();
        m_States.erase(itState);
        if (pState == m_pCurrState) {
            m_pCurrState = nullptr;
            if (m_States.size() > 0) { SwitchState(&(*m_States.begin())->GetName()[0]); }
            else { Quit(); }
        }
        delete pState;
    }
    void Engine::SwitchState(const char* strName)
    {
        if (EngineState* pState = GetState(strName)) {
            if (m_pCurrState != nullptr) m_pCurrState->OnDisable();
            m_pCurrState = pState;
            m_pCurrState->OnEnable();
        }
    }

    // --<core_methods>--
    bool Engine::Init() {
        m_pWindow = new CWindow(WindowInfo(m_strName, V2wh{ 50, 25 }, V2wh{ 8, 16 }));
        Drawer::Init();

        m_pWindow->SetEventCallback([this](AEvent& rEvt)->void { OnEvent(rEvt); });
        EvSys::Init();
        
        system("\a");
        return true;
    }
    void Engine::Quit()
    {
        m_bIsRunning = false;
        system("\a");
    }
    void Engine::Run()
    {
        m_bIsRunning = true;
        if (m_pCurrState == nullptr) {
            AddState(new EngineState());
        }

        while (m_bIsRunning == true) { Update(); }

        while (m_States.begin() != m_States.end()) { RemoveState((*m_States.begin())->GetName()); }
        delete m_pWindow;

        Drawer::Quit();
    }
    // --</core_methods>--

    // --<engine_only_methods>--
    void Engine::Update()
    {
        m_pWindow->Update();
        m_pCurrState->Update();

        IOSys::Update();
        EvSys::Update();
        TimeSys::Update();
    }

    void Engine::OnEvent(AEvent& rEvt)
    {
        if (MouseEvent* pmEvt = dynamic_cast<MouseEvent*>(&rEvt)) {
            m_pCurrState->OnEvent(*pmEvt);
            if (!pmEvt->bIsHandled) {
            }
        }
        else if (KeyboardEvent* pkEvt = dynamic_cast<KeyboardEvent*>(&rEvt)) {
            m_pCurrState->OnEvent(*pkEvt);
            if (!pkEvt->bIsHandled) {
                if (pkEvt->unKeyCode == NC_KEY_ESCAPE_27) { pkEvt->bIsHandled = true; Quit(); }
            }
        }
        else if (WindowEvent* pwEvt = dynamic_cast<WindowEvent*>(&rEvt)) {
            m_pCurrState->OnEvent(*pwEvt);
            if (!pwEvt->bIsHandled) {
                if (pwEvt->EvtType == ET_WINDOW_CLOSE) { pwEvt->bIsHandled = true; Quit(); }
            }
        }
    }
    // --</engine_only_methods>--
}