#include "PPropertyParser/PProperties.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_FREELIST(PProperties::PProperty, 0, 8)
IMPLEMENT_DYNCREATE(PProperties, TObject)

const PProperties::PProperty *PProperties::FindProperty(const Toshi::TPCString &a_szProperty, TQList<PProperty>::Iterator &a_oProperties)
{
	for (auto it = a_oProperties; it != m_oPropsQueue.End(); it++) {
	}
	return nullptr;
}
