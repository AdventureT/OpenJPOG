#include "TRenderContext.h"

TOSHI_NAMESPACE_BEGIN

void TRenderContext::SetModelViewMatrix(const TMatrix44 &a_rModelViewMatrix)
{
	m_iFlags |= (FLAG_DIRTY_VIEWMODELMATRIX | FLAG_DIRTY_WORLDMODELMATRIX);
	m_oModelViewMatrix = a_rModelViewMatrix;
	m_iFlags &= ~(FLAG_HAS_MODELWORLDMATRIX | FLAG_UNK3);
}

TOSHI_NAMESPACE_END