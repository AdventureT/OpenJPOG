#include "TGUIDeserialisable.h"

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIDeserialisable, TObject);

TGUIDeserialisable *TOSHI_API TGUIDeserialisable::Create(TGUIInterface *a_pInterface, const PProperties *a_pProperties)
{
	static bool          s_flag         = 0;
	static const TClass *s_class        = TNULL;
	static TPCString     s_propNameType = TPCString();
	if ((s_flag & 1) == 0) {
		s_flag |= 1;
		s_class = TClass::Find("TGUIDeserialisable", TNULL);
	}
	if ((s_flag & 2) == 0) {
		s_flag |= 2;
		s_propNameType = TSystem::GetCStringPool()->Get("type");
	}
	return TNULL;
}

TOSHI_NAMESPACE_END
