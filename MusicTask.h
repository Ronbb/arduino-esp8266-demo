#ifndef __MUSIC_TASK__
#define __MUSIC_TASK__

#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>
#include <vector>

#include <SoftwareSerial.h>

#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioOutputI2SNoDAC.h"
#include "AudioGeneratorWAV.h"

class MusicTask : public Task
{
protected:
    virtual void setup() override;
    virtual void loop() override;

public:
    void Run();

private:
    std::vector<String> _filenames;
    volatile bool _willRun;
    volatile bool _isRunning;
    AudioFileSourceSPIFFS *_file;
    AudioFileSourceID3 *_id3;
    AudioOutputI2SNoDAC *_out;
    AudioGeneratorWAV *_mp3;
};

#endif
