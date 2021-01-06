#ifndef NC_RENDERER_H
#define NC_RENDERER_H

#include <graphics/nc_gstructs.h>

namespace NC
{
	/// Drawer static class
	class NC_API Drawer
	{
		friend class FrameBuf;
	public:
		// --getters
		// --setters
		// --predicates
		static inline bool GetIsDrawing() { return s_bIsDrawing; }

		// --core_methods
		static void Init();
		static void Quit();

		// --drawing
		static void BeginDraw();
		static void OnDrawPixel(float nX, float nY, Pixel Px);
		static void OnDrawText(const char* strText, float nX, float nY, Pixel Px);
		static void EndDraw();
	private:
		static bool s_bIsDrawing;
	};
}

#endif	// NC_RENDERER_H