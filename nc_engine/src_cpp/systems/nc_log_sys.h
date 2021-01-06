#ifndef NC_LOG_SYSTEM_H
#define NC_LOG_SYSTEM_H

#include <nc_pch.hpp>
#include <nc_core.hpp>

namespace NC
{
	/// FormatToken struct
	/// Description:
	/// -- Represents some value of any type for formatted writting
	/// -- cIndicator is a character which helps to find that some character means this token
	/// -- cDivisor is a character which is set between tokens
	/// -- ftValue is an actual value representation for the token
	template<typename FTType>
	struct NC_API FToken
	{
		FTType ftValue = FTType();
		static const char* cIndicator;
	};
	const char* FToken<Int32>::cIndicator = "int";
	const char* FToken<Float32>::cIndicator = "flt";
	const char* FToken<Float64>::cIndicator = "dbl";
	const char* FToken<Char>::cIndicator = "chr";
	const char* FToken<CString>::cIndicator = "str";
	/// LogParams struct
	/// Description:
	/// -- This is just a bunch of settings for LogSys
	enum LogFlags : UInt32 {
		LF_WRITE_HEADER_LOGGER = 1 << 0,
		LF_WRITE_LOC_DIR = 1 << 1, LF_WRITE_LOC_FILE = 1 << 2, LF_WRITE_LOC_LINE = 1 << 3
	};
	/// LogSystem static class
	/// Descritpion:
	/// -- The core debugger which helps to write messages and manage errors
	/// -- Main methods are "WriteF" and "WriteErrF" for formatted logging
	/// -- It can save logs in files, print the information on the screen(in the console for now)
	/// -- Format is described further
	/// -- For now 20.12.2020: only WriteF and WriteErrF
	/// -- I also can implement some exception which will report LogSystem about own error code
	/// Interface:
	/// -> Initialize the system
	/// -> WriteF to use formatted Logging.
	/// ==| The first argument is a format which describes how further arguments will be written
	/// ==| "{}" means that some symbols inside must reference some number further in arguments
	/// ==| In the curly brackets must be at least one first character - the type of argument
	/// ==| With ":" after the character we can assign, how much arguments follows
	/// ==| It is also possible to add second ":" to set a character-divisor which will be between args
	/// ==| Example: WriteF("Some message for {s:2:_}", "Formatted", "Logging"); -> Some Message for Formatted_Logging
	/// ==| For now only {t} format is supported
	class NC_API LogSys
	{
		using ErrStack = std::stack<Int32>;
		using LogInput = std::istream;
		using LogOutput = std::ostream;
	public:
		// -- Getters
		static inline LogInput& GetLogInput() { return std::cin; }
		static inline LogOutput& GetLogOutput() { return std::cout; }
		static inline LogFlags& GetLogFlags() { return s_LogFlags; }
		// -- Setters

		// -- Core Methods
		static bool OnInit() {
			return true;
		}

		static void WriteF(const char* strFormat, ...) {
			DArray<FToken<Int32>> intTokens;
			DArray<FToken<Float32>> fltTokens;
			DArray<FToken<Float64>> dblTokens;
			DArray<FToken<Char>> cTokens;
			DArray<FToken<CString>> strTokens;

			Int32 nLength = strlen(strFormat);
			std::stringstream strStream;
			Int32 nCurr = 0;

			va_list vaList;
			va_start(vaList, strFormat);
			while (nCurr < nLength) {
				char cCurr = strFormat[nCurr++];
				if (cCurr == '{') {
					char cBuf[4]{ 0 };
					UInt32 nCurrBuf = 0;
					while (cCurr != '}' && cCurr != ':' && nCurr < nLength) {
						cCurr = strFormat[nCurr++];
						if (nCurrBuf < 3) cBuf[nCurrBuf++] = cCurr;
					}
					if (strcmp(cBuf, FToken<Int32>::cIndicator) == 0) {
						intTokens.push_back({ va_arg(vaList, Int32) });
					}
					else if (strcmp(cBuf, FToken<Float32>::cIndicator) == 0) {
						fltTokens.push_back({ static_cast<Float32>(va_arg(vaList, Float64)) });
					}
					else if (strcmp(cBuf, FToken<Float64>::cIndicator) == 0) {
						dblTokens.push_back({ va_arg(vaList, Float64) });
					}
					else if (strcmp(cBuf, FToken<Char>::cIndicator) == 0) {
						cTokens.push_back({ va_arg(vaList, Char) });
					}
					else if (strcmp(cBuf, FToken<CString>::cIndicator) == 0) {
						strTokens.push_back({ va_arg(vaList, CString) });
					}
					if (cCurr == ':') {		// Check counter
						cCurr = strFormat[++nCurr];
						cCurr = strFormat[++nCurr];
					}
					if (cCurr == ':') {		// Check divisor
						cCurr = strFormat[++nCurr];
						cCurr = strFormat[++nCurr];
					}
					if (cCurr == '}' && nCurr <= nLength) cCurr = strFormat[++nCurr];	// End this up
				}

				while (intTokens.size() > 0) {
					strStream << intTokens[0].ftValue;
					intTokens.erase(intTokens.begin());
				}
				while (fltTokens.size() > 0) {
					strStream << fltTokens[0].ftValue;
					fltTokens.erase(fltTokens.begin());
				}
				while (dblTokens.size() > 0) {
					strStream << dblTokens[0].ftValue;
					dblTokens.erase(dblTokens.begin());
				}
				while (cTokens.size() > 0) {
					strStream << cTokens[0].ftValue;
					cTokens.erase(cTokens.begin());
				}
				while (strTokens.size() > 0) {
					strStream << strTokens[0].ftValue;
					strTokens.erase(strTokens.begin());
				}
				strStream << cCurr;
			}
			va_end(vaList);

			if (s_LogFlags & LF_WRITE_HEADER_LOGGER) { GetLogOutput() << "--==<LOG_SYSTEM>==--" << '\n'; }
			if (s_LogFlags & LF_WRITE_LOC_DIR) { GetLogOutput() << "FILE:: " << __FILE__ << '\n'; }
			//if (s_LogFlags & LF_WRITE_LOC_FILE) { GetLogOutput() << __FILE__ << '\n'; }
			if (s_LogFlags & LF_WRITE_LOC_LINE) { GetLogOutput() << "LINE::" << __LINE__ << '\n'; }

			GetLogOutput() << strStream.str() << '\n';
		}
		template <typename ... Args>
		static void WriteErrF(Int32 nErrCode, const char* strFormat, Args ... Arguments) {
			WriteF("LOG::ERROR::CODE_{int}", nErrCode);
			__debugbreak();
			WriteF(strFormat, std::forward<Args>(Arguments));
		}
	private:
		static LogFlags s_LogFlags;
		static ErrStack s_ErrStack;
	};
}

#endif	// NC_LOG_SYSTEM_H