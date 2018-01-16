#include "sbusAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


sbusAnalyzerSettings::sbusAnalyzerSettings()
:	mInputChannel( UNDEFINED_CHANNEL ),
	mBitRate( 100000 ),
	mRCChannel(1)
{
	mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mInputChannelInterface->SetTitleAndTooltip( "Serial", "Standard sbus" );
	mInputChannelInterface->SetChannel( mInputChannel );

	mBitRateInterface.reset( new AnalyzerSettingInterfaceInteger() );
	mBitRateInterface->SetTitleAndTooltip( "Bit Rate (Bits/S)",  "Specify the bit rate in bits per second." );
	mBitRateInterface->SetMax( 6000000 );
	mBitRateInterface->SetMin( 1 );
	mBitRateInterface->SetInteger( mBitRate );

	mRCChannelInterface.reset( new AnalyzerSettingInterfaceInteger() );
	mRCChannelInterface->SetTitleAndTooltip( "RC channel (1-16)",  "Specify RC channel to decode." );
	mRCChannelInterface->SetMax( 16 );
	mRCChannelInterface->SetMin( 1 );
	mRCChannelInterface->SetInteger( mRCChannel );

	AddInterface( mInputChannelInterface.get() );
	AddInterface( mBitRateInterface.get() );
	AddInterface( mRCChannelInterface.get() );

	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mInputChannel, "Serial", false );
}

sbusAnalyzerSettings::~sbusAnalyzerSettings()
{
}

bool sbusAnalyzerSettings::SetSettingsFromInterfaces()
{
	mInputChannel = mInputChannelInterface->GetChannel();
	mBitRate = mBitRateInterface->GetInteger();
	mRCChannel = mRCChannelInterface->GetInteger();

	ClearChannels();
	AddChannel( mInputChannel, "sbus", true );

	return true;
}

void sbusAnalyzerSettings::UpdateInterfacesFromSettings()
{
	mInputChannelInterface->SetChannel( mInputChannel );
	mBitRateInterface->SetInteger( mBitRate );
	mRCChannelInterface->SetInteger( mRCChannel );
}

void sbusAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mInputChannel;
	text_archive >> mBitRate;
	text_archive >> mRCChannel;

	ClearChannels();
	AddChannel( mInputChannel, "sbus", true );

	UpdateInterfacesFromSettings();
}

const char* sbusAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mInputChannel;
	text_archive << mBitRate;
	text_archive << mRCChannel;

	return SetReturnString( text_archive.GetString() );
}
