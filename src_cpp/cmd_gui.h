#ifndef CMD_GUI_H
#define CMD_GUI_H

#include <cmd_core.hpp>
#include <cmd_structs.h>

namespace CMD
{
	using CWidgetCallback = std::function<void()>;
	class CMD_API CWidget
	{
	public:
		using SubWidgets = std::unordered_map<UInt32, CWidget*>;
	public:
		CWidget();
		CWidget(const char* strName);
		virtual ~CWidget();

		// --getters
		inline const char* GetName() { return &m_strName[0]; }
		inline UInt32 GetId() { return m_unId; }
		inline V2xy GetCoord() { return m_xyCrd; }
		inline V2xy GetSize() { return m_whSize; }
		inline SubWidgets& GetSubWidgets() { return m_SubWidgets; }
		inline CWidget* GetSubWidget(UInt32 unId) { return m_SubWidgets.find(unId) == m_SubWidgets.end()? nullptr : m_SubWidgets[unId]; }
		inline bool IsEnabled() { return m_bIsEnabled; }
		// --setters
		inline void SetName(const char* strName) { m_strName = strName; }
		inline void SetCoord(UInt16 unX, UInt16 unY) { m_xyCrd.X = unX; m_xyCrd.Y = unY; }
		inline void SetSize(UInt16 unWidth, UInt16 unHeight) { m_whSize.X = unWidth; m_whSize.Y = unHeight; }
		inline void AddSubWidget(CWidget* pcWidget) {
			if (pcWidget == nullptr) { return; }
			m_SubWidgets[pcWidget->GetId()] = pcWidget;
		}
		inline void RmvSubWidget(UInt32 unId) {
			auto& itWgt = m_SubWidgets.find(unId);
			if (itWgt == m_SubWidgets.end()) { return; }
			m_SubWidgets.erase(itWgt);
		}
		// --core_methods
		virtual void Enable() = 0;
		virtual void Disable() = 0;
		virtual void Render() = 0;
		virtual void OnMouseEvent(MOUSE_EVENT_RECORD& rmEvt) = 0;
		virtual void OnKeyEvent(MOUSE_EVENT_RECORD& rkEvt) = 0;
	private:
		static IdStack s_IdStack;
	protected:
		UInt32 m_unId = 0;
		String m_strName = "";
		V2xy m_xyCrd = { 0, 0 };
		V2wh m_whSize = { 1, 1 };
		bool m_bIsEnabled = false;

		SubWidgets m_SubWidgets;
	};
	class CMD_API GuiMenuItem : public CWidget
	{
	public:
		GuiMenuItem();
		~GuiMenuItem();

		// --getters
		// --setters
		// --core_methods
		virtual void Enable() override;
		virtual void Disable() override;
		virtual void Render() override;
		virtual void OnMouseEvent(MOUSE_EVENT_RECORD& rmEvt) override;
		virtual void OnKeyEvent(MOUSE_EVENT_RECORD& rkEvt) override;
	private:
	};
}

#endif	// CMD_GUI_H