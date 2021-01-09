#include <ncw_pch.hpp>

int main(int nArgs, char** strArgs)
{
	NC::ConsoleEngine* pCEngine = &NC::ConsoleEngine::Get();

	NC::CWindowInfo cwInfo;
	cwInfo.strTitle = "console_engine";
	cwInfo.xywhRect = { 0, 0, 100, 50 };
	NC::CFrameBufInfo cfbInfo{ 0 };
	cfbInfo.dwSize = {cwInfo.GetWidth() + 1, cwInfo.GetHeight() + 1 };
	NC::CPixelInfo cpxInfo{ 0 };
	cpxInfo.dwFontSize = { 8, 16 };

	if (!pCEngine->Init(cwInfo, cpxInfo, cfbInfo)) { return -1; }
	while (pCEngine->IsRunning()) {
		if (pCEngine->GetMouseHeld(NC::MSB_RIGHT)) {
			pCEngine->SetPixelXY(pCEngine->GetMouseMoveX(), pCEngine->GetMouseMoveY(),
				NC::CCN_BG_5 | NC::CCN_FG_16, NC::CPT_1_4);
		}
		if (pCEngine->GetKeyPressed(NC::KC_ESCAPE)) { pCEngine->Quit(); }
		pCEngine->Update();
	}

	return 0;
}