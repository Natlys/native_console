#ifndef NC_ADATA_RESOURCE_H
#define NC_ADATA_RESOURCE_H

#include <nc_core.hpp>

namespace NC
{
	class NC_API ADataRes
	{
		using IdStack = DStack<UInt32>;
	public:
		ADataRes();
		ADataRes(const ADataRes& rDataRes);
		virtual ~ADataRes();

		// --getters
		inline UInt32 GetId() { return m_unId; }
		// --setters

		// --interface_methods
		virtual bool SaveF(const char* strFPath) = 0;
		virtual bool LoadF(const char* strFPath) = 0;
	protected:
		UInt32 m_unId;
	private:
		static IdStack s_IdStack;
	};
}

#endif	// NC_ADATA_RESOURCE_H