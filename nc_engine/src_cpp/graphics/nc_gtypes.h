#ifndef NC_GTYPES_H
#define NC_GTYPES_H

#include <graphics/nc_gstructs.h>

#include <core/nc_adata_res.h>

// AImage
namespace NC
{
	/// Abstract Image Class
	/// Description:
	/// -- Contains color data for each pixel
	/// -- Contains size of that data
	/// -- Has channels number to define how many bytes every pixel takes
	class NC_API AImage : public ADataRes
	{
	public:
		// Constructor&Destructor
		AImage();
		AImage(AImage& rImgCpy);
		virtual ~AImage();

		// Getters
		inline UByte* GetColorData() { return b_pClrData; }
		inline Size GetColorSize() { return b_szClr; }
		inline Int32 GetChannels() { return b_nChannels; }
		// Setters
		virtual void SetData(UByte* pClrData, Size szClrData, UInt32 unChannels = 1);

		// Interface Methods
		virtual void ResetData();

		virtual bool SaveF(const char* strFPath);
		virtual bool LoadF(const char* strFPath);
	protected:
		UByte* b_pClrData;
		Size b_szClr;
		Int32 b_nChannels;
	};
}

#endif	// NC_GTYPES_H