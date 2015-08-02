#include "MidiDriver.h"

using namespace Midi;

MidiBuffer::MidiBuffer(int maxMessages)
    : maxMessages(maxMessages),
      messages(new MidiMessage[maxMessages]),
      writeIndex(0), readIndex(0),
      messagesCount(0)
{

}

MidiBuffer::MidiBuffer(const MidiBuffer &other)
    : maxMessages(other.maxMessages),
      messages(new MidiMessage[other.maxMessages]),
      writeIndex(other.writeIndex), readIndex(other.readIndex),
      messagesCount(other.messagesCount)
{
    for (int m = 0; m < other.messagesCount; ++m) {
        this->messages[m].data = other.messages[m].data;
        this->messages[m].timestamp = other.messages[m].timestamp;
    }
}

MidiBuffer::~MidiBuffer(){
    delete [] messages;
}

void MidiBuffer::addMessage(const MidiMessage &m){
    messages[writeIndex].data = m.data;
    messages[writeIndex].timestamp = m.timestamp;
    writeIndex = (writeIndex + 1) % maxMessages;
    messagesCount++;
}

MidiMessage MidiBuffer::consumeMessage(){
    if(messagesCount > 0){
        messagesCount--;
        return messages[readIndex++];
    }
    return MidiMessage();
}

//++++++++++++++++
MidiDriver::MidiDriver()
{

}

MidiDriver::~MidiDriver()
{

}
