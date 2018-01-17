#include "sbusAnalyzer.h"
#include "sbusAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

sbusAnalyzer::sbusAnalyzer()
:	Analyzer2(),  
	mSettings( new sbusAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

sbusAnalyzer::~sbusAnalyzer()
{
	KillThread();
}

void sbusAnalyzer::SetupResults()
{
	mResults.reset( new sbusAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
}

void sbusAnalyzer::WorkerThread()
{
	mSampleRateHz = GetSampleRate();

	mSerial = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mSerial->GetBitState() == BIT_HIGH )
		mSerial->AdvanceToNextEdge();

	U32 samples_per_bit = mSampleRateHz / mSettings->mBitRate;
	U32 samples_to_first_center_of_first_data_bit = U32( 1.5 * double( mSampleRateHz ) / double( mSettings->mBitRate ) );

	U8 bitCounter = 0;
	U8 startBit = 8 + (mSettings->mRCChannel-1)*11;
	U16 channelData = 0;
	U64 starting_sample = 0;

	for( ; ; )
	{	
		mSerial->AdvanceToNextEdge(); //falling edge -- beginning of the start bit

		if(bitCounter==0){
			starting_sample = mSerial->GetSampleNumber();
		}

		mSerial->Advance( samples_to_first_center_of_first_data_bit );

		for( U32 i=0; i<8; i++ )
		{

			if(bitCounter >= startBit && bitCounter < startBit+11){
				
				channelData>>=1;
				
				if( mSerial->GetBitState() == BIT_LOW ){
					channelData += 1024;
					mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::One, mSettings->mInputChannel );
				}else{
					mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::Zero, mSettings->mInputChannel );
				}
			}else{
				mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::X, mSettings->mInputChannel );
			}
			bitCounter++;

			mSerial->Advance( samples_per_bit );
		}

		//PARITY BIT
		mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel );
		mSerial->Advance( samples_per_bit );

		//end of frame 
		if(bitCounter >= 200){
			Frame frame;
			frame.mData1 = channelData;
			frame.mFlags = 0;
			frame.mStartingSampleInclusive = starting_sample;
			frame.mEndingSampleInclusive = mSerial->GetSampleNumber();

			bitCounter=0;
			channelData=0;

			mResults->AddFrame( frame );
			mResults->CommitResults();
			ReportProgress( frame.mEndingSampleInclusive );
		}
	}
}

bool sbusAnalyzer::NeedsRerun()
{
	return false;
}

U32 sbusAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 sbusAnalyzer::GetMinimumSampleRateHz()
{
	return mSettings->mBitRate * 4;
}

const char* sbusAnalyzer::GetAnalyzerName() const
{
	return "sbus";
}

const char* GetAnalyzerName()
{
	return "sbus";
}

Analyzer* CreateAnalyzer()
{
	return new sbusAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}