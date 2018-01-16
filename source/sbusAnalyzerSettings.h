#ifndef SBUS_ANALYZER_SETTINGS
#define SBUS_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class sbusAnalyzerSettings : public AnalyzerSettings
{
public:
	sbusAnalyzerSettings();
	virtual ~sbusAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	U32 mBitRate;
	U32 mRCChannel;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mRCChannelInterface;
};

#endif //SBUS_ANALYZER_SETTINGS
