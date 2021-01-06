#include "nc_pch.hpp"
#include "nc_Drawer.h"

#include <graphics/gcontext/nc_cwindow.h>

#include <core/nc_engine.h>

bool NC::Drawer::s_bIsDrawing = false;
static NC::CWindow *s_pWindow = nullptr;

namespace NC
{
    // --<core_methods>--
    void Drawer::Init()
    {
        s_pWindow = Engine::Get().GetWindow();
    }
    void Drawer::Quit()
    {
    }
    // --</core_methods>--
    
    // --<drawing>--
    void Drawer::BeginDraw()
    {
        bool bCanDraw = !s_bIsDrawing;
        if (!bCanDraw) { return; }
        s_bIsDrawing = true;
    }
    void Drawer::OnDrawPixel(float nX, float nY, Pixel Px)
    {
        bool bCanDraw = s_bIsDrawing;
        if (!bCanDraw) { return; }

        UInt16 unX = static_cast<UInt16>(static_cast<float>(s_pWindow->GetWidth()) * nX);
        UInt16 unY = static_cast<UInt16>(static_cast<float>(s_pWindow->GetHeight()) * nY);

        CPixel cPx = { 0 };
        UInt32 unRgb = Px.unR | Px.unG | Px.unB;
        for (UInt8 cli = 0; cli < 16; cli++) {
            if (unRgb > (CN_FG_2 << cli)) cPx.Attributes |= (CN_FG_2 << cli);
        }
        if (Px.unA > 32) {
            cPx.Char.UnicodeChar = PX_1_4;
            if (Px.unA > 96) {
                cPx.Char.UnicodeChar = PX_2_4;
                if (Px.unA > 160) {
                    cPx.Char.UnicodeChar = PX_3_4;
                    if (Px.unA > 224) {
                        cPx.Char.UnicodeChar = PX_SOLID;
                    }
                }
            }
        }
        s_pWindow->SetPixel(unX, unY, cPx);
    }
    void Drawer::OnDrawText(const char* strText, float nX, float nY, Pixel Px)
    {
        bool bCanDraw = s_bIsDrawing;
        if (!bCanDraw) { return; }
        
        UInt16 unX = static_cast<UInt16>(static_cast<float>(s_pWindow->GetWidth()) * nX);
        UInt16 unY = static_cast<UInt16>(static_cast<float>(s_pWindow->GetHeight()) * nY);
        UInt16 unW = s_pWindow->GetWidth();
        UInt16 unH = s_pWindow->GetHeight();

        for (Int32 ci = 0, nLen = strlen(strText); ci < nLen; ci++) {
            CPixel cPx = { 0 };
            UInt32 unRgb = Px.unR | Px.unG | Px.unB;
            for (UInt8 cli = 0; cli < 16; cli++) {
                if (unRgb > (CN_FG_2 << cli)) cPx.Attributes |= (CN_FG_2 << cli);
            }

            if (strText[ci] == '\n') {
                cPx.Char.UnicodeChar = '\0';
                cPx.Char.AsciiChar = '\0';
            }
            else {
                cPx.Char.UnicodeChar = (TCHAR)(strText[ci]);
                cPx.Char.AsciiChar = (strText[ci]);
            }
            cPx.Attributes = CN_FG_4 | CN_BG_16;
            s_pWindow->SetPixel(unX + ci % unW, unY + ci / unW, cPx);
        }
    }
    void Drawer::EndDraw()
    {
        bool bCanDraw = s_bIsDrawing;
        if (!bCanDraw) { return; }
        s_bIsDrawing = false;
    }
    // --</drawing>--
}