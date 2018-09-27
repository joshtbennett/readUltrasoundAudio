#include <iostream>
#include <string.h>
#include <cstdint>

using namespace std;


typedef struct  WAV_HEADER{
        uint8_t riff[4];
        uint32_t chunkSize;
        uint8_t wave[4];
        uint8_t fmt[4];
        uint32_t subChunk1Size;
        uint16_t audioFormat;
        uint16_t numOfChannels;
        uint32_t samplesPerSecond;
        uint32_t bytesPerSecond;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
        uint8_t subChunk2ID[4];
        uint32_t subChunk2Size;
}wav_hdr; 

int main(int argc, char const *argv[]){
        wav_hdr wavHeader;
        int headerSize = sizeof(wav_hdr), filelength = 0;
        char* filePath = "/home/josh/Documents/doppler.wav";
        FILE *wavFile = fopen(filePath, "r");
        if (wavFile == nullptr)
        {
                fprintf(stderr, "Unable to open wave file: %s\n", filePath);
                return 1;
        }


       //Read the header
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    cout << "Header Read " << bytesRead << " bytes." << endl;
    if (bytesRead > 0)
    {
        //Read the data
        uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;      //Number     of bytes per sample
        uint64_t numSamples = wavHeader.chunkSize / bytesPerSample; //How many samples are in the wav file?
        static const uint16_t BUFFER_SIZE = 4096;
        int8_t* buffer = new int8_t[BUFFER_SIZE];
        while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
        {
            /** DO SOMETHING WITH THE WAVE DATA HERE **/
            cout << "Read " << bytesRead << " bytes." << endl;
        }
        delete [] buffer;
        buffer = nullptr;
        // filelength = getFileSize(wavFile);

        cout << "File is                    :" << filelength << " bytes." << endl;
        cout << "RIFF header                :" << wavHeader.riff[0] << wavHeader.riff[1] << wavHeader.riff[2] << wavHeader.riff[3] << endl;
        cout << "WAVE header                :" << wavHeader.wave[0] << wavHeader.wave[1] << wavHeader.wave[2] << wavHeader.wave[3] << endl;
        cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
        cout << "Data size                  :" << wavHeader.chunkSize << endl;

        // Display the sampling Rate from the header
        cout << "Sampling Rate              :" << wavHeader.samplesPerSecond << endl;
        cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
        cout << "Number of channels         :" << wavHeader.numOfChannels << endl;
        cout << "Number of bytes per second :" << wavHeader.bytesPerSecond << endl;
        cout << "Data length                :" << wavHeader.subChunk2Size << endl;
        cout << "Audio Format               :" << wavHeader.audioFormat << endl;
        // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

        cout << "Block align                :" << wavHeader.blockAlign << endl;
        cout << "Data string                :" << wavHeader.subChunk2ID[0] << wavHeader.subChunk2ID[1] << wavHeader.subChunk2ID[2] << wavHeader.subChunk2ID[3] << endl;
    }
        fclose(wavFile);
        return 0;
}
