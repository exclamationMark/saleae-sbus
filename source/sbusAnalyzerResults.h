#ifndef SBUS_ANALYZER_RESULTS
#define SBUS_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class sbusAnalyzer;
class sbusAnalyzerSettings;

class sbusAnalyzerResults : public AnalyzerResults
{
public:
	sbusAnalyzerResults( sbusAnalyzer* analyzer, sbusAnalyzerSettings* settings );
	virtual ~sbusAnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	sbusAnalyzerSettings* mSettings;
	sbusAnalyzer* mAnalyzer;
};

#endif //SBUS_ANALYZER_RESULTS
