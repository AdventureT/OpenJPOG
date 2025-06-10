#include "AOptions.h"
#include "PPropertyParser/PPropertyReader.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

TPCCHAR   AOptions::sm_szOptionsDir  = TNULL;
TPCCHAR   AOptions::sm_szOptionsName = "Options";
AOptions *AOptions::ms_pSingleton    = TNULL;

// $JPOG: FUNCTION 004674e0
AOptions::AOptions()
{
	m_iAutoSaveState   = 1;
	ms_pSingleton      = this;
	PProperties *props = new PProperties();
	m_pUnkProps        = props;
	m_pCurProps        = props;
}

// $JPOG: FUNCTION 00474fc0
TBOOL AOptions::GetOption(TPCCHAR a_szProp, TINT &a_iValue)
{
	const PPropertyValue *value = m_pCurProps->GetProperty(TSystem::GetCStringPool()->Get(a_szProp));
	if (!value) {
		return TFALSE;
	}
	if (!value->CanBeType(PPropertyValue::TYPE_INT)) {
		return TFALSE;
	}
	a_iValue = value->GetInteger();
	return TTRUE;
}

AOptions::Result AOptions::LoadOptions()
{
	AOptions::Result result = LoadOptions(-1, -1, sm_szOptionsDir, sm_szOptionsName);
	return result;
}

AOptions::Result AOptions::LoadOptions(TINT a_int, TINT a_int2, const Toshi::TCString &a_szOptionsDir, const Toshi::TCString &a_szOptionsName)
{
	PPropertyReader reader   = PPropertyReader();
	Toshi::TCString filepath = Toshi::TCString().Format("%s/%s.ini", a_szOptionsDir.GetString(), a_szOptionsName.GetString());
	TBOOL           res      = reader.Open("Options.ini");
	if (!res) {
		return RESULT_ERROR;
	}
	PProperties *props = new PProperties();
	res                = reader.LoadPropertyBlock(*props);
	if (!res) {
		return RESULT_ERROR;
	}
	if (m_pUnkProps) {
		delete m_pUnkProps;
	}
	m_pUnkProps = props;
	m_pCurProps = props;
	return RESULT_OK;
}

AOptionsLogic::AScreenRes AOptionsLogic::m_oScreenRes = AOptionsLogic::AScreenRes(640, 480, 32, 0);

AOptionsLogic::AOptionsLogic()
{
}

TBOOL AOptionsLogic::GetOption(OPTION a_eOption, AScreenRes &a_rScreenRes)
{
	AOptionSetting setting;
	setting.m_eOption = a_eOption;
	OptionGet(setting);
	a_rScreenRes = *(AScreenRes *)(&setting + 1);
	return setting.m_bFetched;
}

TBOOL AOptionsLogic::GetOption(OPTION a_eOption, LMH &a_rLMH)
{
	AOptionSetting setting;
	setting.m_eOption = a_eOption;
	OptionGet(setting);
	a_rLMH = *(LMH *)(&setting + 1);
	return setting.m_bFetched;
}

TBOOL AOptionsLogic::SetOption(OPTION a_eOption, AScreenRes &a_rScreenRes)
{
	return TBOOL();
}

void AOptionsLogic::OptionGet(AOptionSetting &a_rSetting)
{
	// GetShaders
	AScreenRes *screenRes = (AScreenRes *)(&a_rSetting + 1);
	switch (a_rSetting.m_eOption) {
		case OPTION_SCREENRES:
			screenRes = &m_oScreenRes;
			break;
		default:
			break;
	}
}
