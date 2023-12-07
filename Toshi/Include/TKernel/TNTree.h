#pragma once

#include <TKernel/TDebug.h>

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TGenericNTree
{
	class TNode
	{
	protected:


		TINT FindChild(TNode const* a_pNode, TINT a_iCount)
		{
			for (TINT i = 0; i < a_iCount; i++) {
				if (a_pNode == m_pChildren[i]) {
					return i;
				}
			}
			return -1;
		}

		TNode* Child(TINT a_iIndex) const { return m_pChildren[a_iIndex]; }
		TNode* Parent() const { return m_pParent; }

	private:
		TNode* m_pParent;   // 0x0
		TNode** m_pChildren; // 0x4
	};

protected:

	TGenericNTree()
	{
		m_pRoot = TNULL;
	}

	void InsertRoot(TNode *a_pNode)
	{
		m_pRoot = a_pNode;
		a_pNode = TNULL;
	}

	void RemoveRoot()
	{
		m_pRoot = TNULL;
	}

	TNode* Root() const { return m_pRoot; }
private:
	TNode* m_pRoot;   // 0x0
};



TOSHI_NAMESPACE_END