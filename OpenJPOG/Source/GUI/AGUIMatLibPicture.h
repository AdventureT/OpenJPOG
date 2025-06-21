#pragma once
#include "AGUIPicture.h"
#include "TKernel/TCString.h"

class AGUIMatLibPicture : public AGUIPicture
{
	DECLARE_DYNAMIC(AGUIMatLibPicture);

public:

	AGUIMatLibPicture();

protected:
	void LoadMaterialLibrary();
	void UnloadMaterialLibrary();

public:
	void SetFile(TPCCHAR a_szFile);

public:
	virtual void Create(Toshi::TSpriteShader *a_pShader);
	virtual void Flush();
	virtual void Cache();

private:
	TINT            m_tmlidx;  // 0x20
	Toshi::TCString m_sPrefix; // 0x24
};