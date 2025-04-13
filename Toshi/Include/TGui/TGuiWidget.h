#pragma once
#include "Defines.h"
#include "TKernel/TNodeList.h"
#include "TGUIDeserialisable.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIWidget : public TGUIDeserialisable, public TNodeList<TGUIWidget>::TNode
{
	DECLARE_DYNAMIC(TGUIWidget)

	enum State
	{
		STATE_ENABLED = BITFIELD(0),
		STATE_FOCUSED = BITFIELD(1),
		STATE_VISIBLE = BITFIELD(2),
		STATE_ROLLOVER = BITFIELD(3),
		STATE_SELECTED = BITFIELD(4),
	};
};

TOSHI_NAMESPACE_END