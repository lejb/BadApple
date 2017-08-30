
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <fstream> 
#include <unistd.h> 

using namespace std;

const char* _waveFileNames = "./animation/BadApple.wav";
Mix_Chunk* _sample = NULL;

// Initializes the application data
bool Init(void)
{
    // Set up the audio stream
    int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    result = Mix_AllocateChannels(4);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
        exit(-1);
    }

    // Load waveforms       
    _sample = Mix_LoadWAV(_waveFileNames);
    if( _sample == NULL )
    {
        fprintf(stderr, "Unable to load wave file: %s\n", _waveFileNames);
    }   return true;
}

ifstream AnimationTextFile;

void AnimationInit()
{
    AnimationTextFile.open("./animation/BadApple");

    if (!AnimationTextFile)
    {
        fprintf(stderr, "Can not open the animation file! \n");
        exit(1);
    }
}

void AnimationClose()
{
    AnimationTextFile.close();
}

void AnimationReadNextFrame()
{
    static const int linesPerFrame = 64;
    static const int charsPerLine = 142;
    
    static char frameBuffer[linesPerFrame * charsPerLine];

    //system("clear");
    
    for (int i = 0; i < linesPerFrame - 1; i++)
    {
        cout << "\e[A";
    }

    AnimationTextFile.read(frameBuffer, sizeof(char) * linesPerFrame * charsPerLine);

    puts(frameBuffer);
}

bool beEndofAnimation()
{
    return AnimationTextFile.eof();
}

int main(void)
{
    // Initialize the SDL library
    SDL_Init(SDL_INIT_AUDIO);
    atexit(SDL_Quit);

    // Application specific Initialize of data structures
    if (Init() == false)
        return -1;

    Mix_PlayChannel(-1, _sample, 0);
    
    AnimationInit();
    // Event descriptor
    SDL_Event Event;

    bool done = false;
    while (!done)
    {
        bool gotEvent = SDL_PollEvent(&Event);

        while (!done && gotEvent)
        {
            switch (Event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;

                default:
                    break;
            }

            if( !done )
            {
                gotEvent = SDL_PollEvent(&Event);
            }
        }

        AnimationReadNextFrame();

        if (beEndofAnimation())
        {
            break;
        }

        usleep(35000);
    }
    Mix_FreeChunk(_sample);

    Mix_CloseAudio();
    AnimationClose();
    SDL_Quit();
    return 0;
}


