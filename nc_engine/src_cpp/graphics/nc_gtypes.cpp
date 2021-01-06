#include <nc_pch.hpp>
#include "nc_gtypes.h"

// AImage
namespace NC
{
	AImage::AImage() :
		ADataRes(),
		b_pClrData(nullptr), b_szClr(0), b_nChannels(0)
	{
		ResetData();
	}
	AImage::AImage(AImage& rImgCpy) :
		ADataRes(),
		b_pClrData(nullptr), b_szClr(0), b_nChannels(0)
	{
		SetData(rImgCpy.b_pClrData, rImgCpy.b_szClr, rImgCpy.b_nChannels); rImgCpy.ResetData();
	}
	AImage::~AImage()
	{
		ResetData();
	}

	// -- Setters
	void AImage::SetData(UByte* pClrData, Size szClrData, UInt32 unChannels)
	{
		ResetData();
		b_szClr = szClrData;
		b_nChannels = unChannels;
		if (pClrData == nullptr || b_szClr == 0 || b_nChannels == 0) return;
		b_pClrData = new UByte[b_szClr];
		memcpy(b_pClrData, pClrData, b_szClr);
	}
	void AImage::ResetData()
	{
		if (b_szClr) delete[] b_pClrData;
		b_pClrData = nullptr;
		b_szClr = b_nChannels = 0;
	}
	bool AImage::SaveF(const char* strFPath)
	{
		return true;
	}
	bool AImage::LoadF(const char* strFPath)
	{
		return true;
	}
}