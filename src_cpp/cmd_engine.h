#ifndef CMD_ENGINE_H
#define CMD_ENGINE_H

#include <cmd_core.hpp>
#include <cmd_structs.h>
#include <cmd_framebuf.h>

namespace CMD
{
	/// CmdEngine class
	class CMD_API CmdEngine : public ASingleton<CmdEngine>
	{
		friend class ASingleton<CmdEngine>;
	public:
		CmdEngine();
	public:
		~CmdEngine();

		// --getters
		inline AMemAllocator& GetMemory()				{ return m_Memory; }
		inline Thread& GetRunThread()					{ return m_thrRun; }

		inline CmdFrameBuf* GetFrameBuf()				{ return m_pfbCur; }
		
		inline const CWindowInfo& GetWndInfo()	const	{ return m_cwInfo; }
		inline const CPixelInfo& GetPxInfo()	const	{ return m_cpxInfo; }
		inline const CEventsInfo& GetEvInfo()	const	{ return m_cevInfo; }

		inline const Int16 GetWndWidth()		const	{ return m_cwInfo.GetWidth(); }
		inline const Int16 GetWndHeight()		const	{ return m_cwInfo.GetHeight(); }

		inline UInt16 GetMouseMoveX()				const	{ return static_cast<UInt16>(m_cevInfo.msInfo.xMove); }
		inline UInt16 GetMouseMoveY()				const	{ return static_cast<UInt16>(m_cevInfo.msInfo.yMove); }
		inline UInt16 GetMouseHeldX(UInt16 msCode)	const	{ return static_cast<UInt16>(m_cevInfo.msInfo.xHeld[msCode]); }
		inline UInt16 GetMouseHeldY(UInt16 msCode)	const	{ return static_cast<UInt16>(m_cevInfo.msInfo.yHeld[msCode]); }

		inline bool GetMousePressed(MouseButtons msCode)	const	{ return m_cevInfo.msInfo.bsButtons[msCode].bPressed; }
		inline bool GetMouseReleased(MouseButtons msCode)	const	{ return m_cevInfo.msInfo.bsButtons[msCode].bReleased; }
		inline bool GetMouseHeld(MouseButtons msCode)		const	{ return m_cevInfo.msInfo.bsButtons[msCode].bHeld; }
		inline bool GetKeyPressed(KeyCodes kCode)			const	{ return m_cevInfo.kbInfo.bsKeys[kCode].bPressed; }
		inline bool GetKeyReleased(KeyCodes kCode)			const	{ return m_cevInfo.kbInfo.bsKeys[kCode].bReleased; }
		inline bool GetKeyHeld(KeyCodes kCode)				const	{ return m_cevInfo.kbInfo.bsKeys[kCode].bHeld; }
		// --setters
		void SetWndSize(UInt16 nWidth, UInt16 nHeight);
		void SetTitle(const char* strTitle);
		void SetPxSize(UInt16 nWidth, UInt16 nHeight);
		
		void SetWndInfo(const CWindowInfo& rwInfo);
		void SetPxInfo(const CPixelInfo& rpxInfo);
		void SetCursorInfo(const CCursorInfo& rcurInfo);
		// --predicates
		inline bool IsRunning() const { return m_bIsRunning; }

		// --core_methods
		void Run();
		bool Init();
		void Quit();
		void Update();
		void OnEvent(AEvent& rEvt);
		void PollEvents();
		void SwapBuffers();
	private:
		Bit m_bIsRunning;
		Thread m_thrRun;
		MemArena m_Memory;

		CmdFrameBuf *m_pfbCur, m_fbs[2];
		Ptr m_pCout, m_pCin;

		CWindowInfo m_cwInfo;
		CPixelInfo m_cpxInfo;
		CCursorInfo m_curInfo;
		CEventsInfo m_cevInfo;

		Float64 m_nTimeDelta;
		Float64 m_nTimeNow;
		Float64 m_nTimeLast;
	};
}
#endif	// CMD_ENGINE_H