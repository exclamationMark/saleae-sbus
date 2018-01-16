#ifndef SBUS_SIMULATION_DATA_GENERATOR
#define SBUS_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class sbusAnalyzerSettings;

class sbusSimulationDataGenerator
{
public:
	sbusSimulationDataGenerator();
	~sbusSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, sbusAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	sbusAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //SBUS_SIMULATION_DATA_GENERATOR