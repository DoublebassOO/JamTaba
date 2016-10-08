#ifndef NINJAMTRACKNODE_H
#define NINJAMTRACKNODE_H

#include "core/AudioNode.h"
#include <QByteArray>
#include "vorbis/VorbisDecoder.h"
#include "SamplesBufferResampler.h"

namespace Audio {
class SamplesBuffer;
class StreamBuffer;
}

class NinjamTrackNode : public Audio::AudioNode
{
public:

    enum LowCutState
    {
        OFF, NORMAl, DRASTIC
    };

    explicit NinjamTrackNode(int ID);
    virtual ~NinjamTrackNode();
    void addVorbisEncodedInterval(const QByteArray &encodedBytes);
    void processReplacing(const Audio::SamplesBuffer &in, Audio::SamplesBuffer &out, int sampleRate,
                          const Midi::MidiMessageBuffer &midiBuffer);

    void setLowCutState(LowCutState newState);
    LowCutState setLowCutToNextState();
    LowCutState getLowCutState() const;

    bool startNewInterval();
    inline int getID() const
    {
        return ID;
    }

    int getSampleRate() const;

    bool isPlaying();

    void discardIntervals(bool keepMostRecentInterval);
    inline void setProcessingLastPartOfInterval(bool status)
    {
        this->processingLastPartOfInterval = status;
    }

private:
    int ID;
    SamplesBufferResampler resampler;

    class LowCutFilter;
    QScopedPointer<LowCutFilter> lowCut;
    const static double LOW_CUT_NORMAL_FREQUENCY;
    const static double LOW_CUT_DRASTIC_FREQUENCY;

    bool needResamplingFor(int targetSampleRate) const;

    int getFramesToProcess(int targetSampleRate, int outFrameLenght);

    bool processingLastPartOfInterval;

    class IntervalDecoder;

    QList<IntervalDecoder*> decoders;
    IntervalDecoder* currentDecoder;
    QMutex decodersMutex;

};

#endif // NINJAMTRACKNODE_H
