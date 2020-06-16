#include "MusicTask.h"

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
    (void)cbData;
    //Serial.printf("ID3 callback for: %s = '", type);

    if (isUnicode)
    {
        string += 2;
    }

    while (*string)
    {
        char a = *(string++);
        if (isUnicode)
        {
            string++;
        }
        //Serial.printf("%c", a);
    }
    //Serial.printf("'\n");
    //Serial.flush();
}

void MusicTask::setup()
{
    // audioLogger = &Serial;
    _filenames = {"/0.wav", "/1.wav", "/2.wav"};
    _willRun = false;

    SPIFFS.begin();
    _file = new AudioFileSourceSPIFFS();
    _id3 = new AudioFileSourceID3(_file);
    _out = new AudioOutputI2SNoDAC();
    _mp3 = new AudioGeneratorWAV();
}

void MusicTask::loop()
{
    if (_mp3->isRunning())
    {
        if (!_mp3->loop())
            _mp3->stop();
    }
    else
    {
        // if (_willRun == true)
        // {
        // _willRun = false;
        // String fileName = _filenames[micros() % 4];
        // _file->open(fileName.c_str());
        // delete _id3;
        // _id3 = new AudioFileSourceID3(_file);
        // _mp3->begin(_id3, _out);

        // Serial.println(fileName);
        // }
        // else
        // {
            delay(100);
        // }
    }
}

void MusicTask::Run()
{
    if (_isRunning)
    {
        return;
    }
    
    _isRunning = true;
    String fileName = _filenames[micros() % 4];
    _file->open(fileName.c_str());
    delete _id3;
    _id3 = new AudioFileSourceID3(_file);
    _mp3->begin(_id3, _out);

    //Serial.println(fileName);

    while (true)
    {
        if (_mp3->isRunning())
        {
            if (!_mp3->loop())
                _mp3->stop();
            break;
        }
    }
     
    _isRunning = false;
}
