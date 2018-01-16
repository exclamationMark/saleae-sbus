#ifndef SBUS_ANALYZER_H
#define SBUS_ANALYZER_H

#include <Analyzer.h>
#include "sbusAnalyzerResults.h"
#include "sbusSimulationDataGenerator.h"

class sbusAnalyzerSettings;
class ANALYZER_EXPORT sbusAnalyzer : public Analyzer2
{
public:
	sbusAnalyzer();
	virtual ~sbusAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< sbusAnalyzerSettings > mSettings;
	std::auto_ptr< sbusAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	sbusSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //SBUS_ANALYZER_H
