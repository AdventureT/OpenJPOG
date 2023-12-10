/* ========================================================================================== */
/* FMOD Dynamic DLL loading header. Copyright (c), Firelight Technologies Pty, Ltd 1999-2002. */
/* ========================================================================================== */

#ifndef _FMODDYN_H_
#define _FMODDYN_H_

#include <windows.h>
#include <stdio.h>
#include "fmod.h"

typedef struct
{
    HMODULE         module;

    signed char     (F_API *FSOUND_SetOutput)(int outputtype);
    signed char     (F_API *FSOUND_SetDriver)(int driver);
    signed char     (F_API *FSOUND_SetMixer)(int mixer);
    signed char     (F_API *FSOUND_SetBufferSize)(int len_ms);
    signed char     (F_API *FSOUND_SetHWND)(void *hwnd);
    signed char     (F_API *FSOUND_SetMinHardwareChannels)(int min);
    signed char     (F_API *FSOUND_SetMaxHardwareChannels)(int max);
    signed char     (F_API *FSOUND_SetMemorySystem)(void *pool, int poollen, FSOUND_ALLOCCALLBACK useralloc, FSOUND_REALLOCCALLBACK userrealloc, FSOUND_FREECALLBACK userfree);
    signed char     (F_API *FSOUND_Init)(int mixrate, int maxsoftwarechannels, unsigned int flags);
    void            (F_API *FSOUND_Close)();
    void            (F_API *FSOUND_SetSpeakerMode)(unsigned int speakermode);
    void            (F_API *FSOUND_SetSFXMasterVolume)(int volume);
    void            (F_API *FSOUND_SetPanSeperation)(float pansep);
    void            (F_API *FSOUND_File_SetCallbacks)(FSOUND_OPENCALLBACK  useropen, FSOUND_CLOSECALLBACK userclose, FSOUND_READCALLBACK userread, FSOUND_SEEKCALLBACK  userseek, FSOUND_TELLCALLBACK  usertell);
    int             (F_API *FSOUND_GetError)();
    float           (F_API *FSOUND_GetVersion)();
    int             (F_API *FSOUND_GetOutput)();
    void *          (F_API *FSOUND_GetOutputHandle)();
    int             (F_API *FSOUND_GetDriver)();
    int             (F_API *FSOUND_GetMixer)();
    int             (F_API *FSOUND_GetNumDrivers)();
    signed char *   (F_API *FSOUND_GetDriverName)(int id);
    signed char     (F_API *FSOUND_GetDriverCaps)(int id, unsigned int *caps);
    int             (F_API *FSOUND_GetOutputRate)();
    int             (F_API *FSOUND_GetMaxChannels)();
    int             (F_API *FSOUND_GetMaxSamples)();
    int             (F_API *FSOUND_GetSFXMasterVolume)();
    int             (F_API *FSOUND_GetNumHardwareChannels)();
    int             (F_API *FSOUND_GetChannelsPlaying)();
    float           (F_API *FSOUND_GetCPUUsage)();
    void            (F_API *FSOUND_GetMemoryStats)(unsigned int *currentalloced, unsigned int *maxalloced);
    FSOUND_SAMPLE * (F_API *FSOUND_Sample_Load)(int index, const char *name_or_data, unsigned int mode, int memlength);
    FSOUND_SAMPLE * (F_API *FSOUND_Sample_Alloc)(int index, int length, unsigned int mode, int deffreq, int defvol, int defpan, int defpri);
    void            (F_API *FSOUND_Sample_Free)(FSOUND_SAMPLE *sptr);
    signed char     (F_API *FSOUND_Sample_Upload)(FSOUND_SAMPLE *sptr, void *srcdata, unsigned int mode);
    signed char     (F_API *FSOUND_Sample_Lock)(FSOUND_SAMPLE *sptr, int offset, int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
    signed char     (F_API *FSOUND_Sample_Unlock)(FSOUND_SAMPLE *sptr, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);
    signed char     (F_API *FSOUND_Sample_SetMode)(FSOUND_SAMPLE *sptr, unsigned int mode);
    signed char     (F_API *FSOUND_Sample_SetLoopPoints)(FSOUND_SAMPLE *sptr, int loopstart, int loopend);
    signed char     (F_API *FSOUND_Sample_SetDefaults)(FSOUND_SAMPLE *sptr, int deffreq, int defvol, int defpan, int defpri);
    signed char     (F_API *FSOUND_Sample_SetMinMaxDistance)(FSOUND_SAMPLE *sptr, float min, float max);
    signed char     (F_API *FSOUND_Sample_SetMaxPlaybacks)(FSOUND_SAMPLE *sptr, int max);
    FSOUND_SAMPLE * (F_API *FSOUND_Sample_Get)(int sampno);
    char *          (F_API *FSOUND_Sample_GetName)(FSOUND_SAMPLE *sptr);
    unsigned int    (F_API *FSOUND_Sample_GetLength)(FSOUND_SAMPLE *sptr);
    signed char     (F_API *FSOUND_Sample_GetLoopPoints)(FSOUND_SAMPLE *sptr, int *loopstart, int *loopend);
    signed char     (F_API *FSOUND_Sample_GetDefaults)(FSOUND_SAMPLE *sptr, int *deffreq, int *defvol, int *defpan, int *defpri);
    unsigned int    (F_API *FSOUND_Sample_GetMode)(FSOUND_SAMPLE *sptr);
    int             (F_API *FSOUND_PlaySound)(int channel, FSOUND_SAMPLE *sptr);
    int             (F_API *FSOUND_PlaySoundEx)(int channel, FSOUND_SAMPLE *sptr, FSOUND_DSPUNIT *dsp, signed char startpaused);
    signed char     (F_API *FSOUND_StopSound)(int channel);
    signed char     (F_API *FSOUND_SetFrequency)(int channel, int freq);
    signed char     (F_API *FSOUND_SetVolume)(int channel, int vol);
    signed char     (F_API *FSOUND_SetVolumeAbsolute)(int channel, int vol);
    signed char     (F_API *FSOUND_SetPan)(int channel, int pan);
    signed char     (F_API *FSOUND_SetSurround)(int channel, signed char surround);
    signed char     (F_API *FSOUND_SetMute)(int channel, signed char mute);
    signed char     (F_API *FSOUND_SetPriority)(int channel, int priority);
    signed char     (F_API *FSOUND_SetReserved)(int channel, signed char reserved);
    signed char     (F_API *FSOUND_SetPaused)(int channel, signed char paused);
    signed char     (F_API *FSOUND_SetLoopMode)(int channel, unsigned int loopmode);
    signed char     (F_API *FSOUND_SetCurrentPosition)(int channel, unsigned int offset);
    signed char     (F_API *FSOUND_IsPlaying)(int channel);
    int             (F_API *FSOUND_GetFrequency)(int channel);
    int             (F_API *FSOUND_GetVolume)(int channel);
    int             (F_API *FSOUND_GetPan)(int channel);
    signed char     (F_API *FSOUND_GetSurround)(int channel);
    signed char     (F_API *FSOUND_GetMute)(int channel);
    int             (F_API *FSOUND_GetPriority)(int channel);
    signed char     (F_API *FSOUND_GetReserved)(int channel);
    signed char     (F_API *FSOUND_GetPaused)(int channel);
    unsigned int    (F_API *FSOUND_GetLoopMode)(int channel);
    unsigned int    (F_API *FSOUND_GetCurrentPosition)(int channel);
    FSOUND_SAMPLE * (F_API *FSOUND_GetCurrentSample)(int channel);
    signed char     (F_API *FSOUND_GetCurrentLevels)(int channel, float *l, float *r);
    int             (F_API *FSOUND_FX_Enable)(int channel, unsigned int fx);    /* See FSOUND_FX_MODES */
    signed char     (F_API *FSOUND_FX_Disable)(int channel);    
    signed char     (F_API *FSOUND_FX_SetChorus)(int fxid, float WetDryMix, float Depth, float Feedback, float Frequency, int Waveform, float Delay, int Phase);
    signed char     (F_API *FSOUND_FX_SetCompressor)(int fxid, float Gain, float Attack, float Release, float Threshold, float Ratio, float Predelay);
    signed char     (F_API *FSOUND_FX_SetDistortion)(int fxid, float Gain, float Edge, float PostEQCenterFrequency, float PostEQBandwidth, float PreLowpassCutoff);
    signed char     (F_API *FSOUND_FX_SetEcho)(int fxid, float WetDryMix, float Feedback, float LeftDelay, float RightDelay, int PanDelay);
    signed char     (F_API *FSOUND_FX_SetFlanger)(int fxid, float WetDryMix, float Depth, float Feedback, float Frequency, int Waveform, float Delay, int Phase);
    signed char     (F_API *FSOUND_FX_SetGargle)(int fxid, int RateHz, int WaveShape);
    signed char     (F_API *FSOUND_FX_SetI3DL2Reverb)(int fxid, int Room, int RoomHF, float RoomRolloffFactor, float DecayTime, float DecayHFRatio, int Reflections, float ReflectionsDelay, int Reverb, float ReverbDelay, float Diffusion, float Density, float HFReference);
    signed char     (F_API *FSOUND_FX_SetParamEQ)(int fxid, float Center, float Bandwidth, float Gain);
    signed char     (F_API *FSOUND_FX_SetWavesReverb)(int fxid, float InGain, float ReverbMix, float ReverbTime, float HighFreqRTRatio);  
    void            (F_API *FSOUND_Update)();   /* you must call this once a frame */
    void            (F_API *FSOUND_3D_SetDopplerFactor)(float scale);
    void            (F_API *FSOUND_3D_SetDistanceFactor)(float scale);
    void            (F_API *FSOUND_3D_SetRolloffFactor)(float scale);
    signed char     (F_API *FSOUND_3D_SetAttributes)(int channel, float *pos, float *vel);
    signed char     (F_API *FSOUND_3D_GetAttributes)(int channel, float *pos, float *vel);
    void            (F_API *FSOUND_3D_Listener_SetCurrent)(int current, int numlisteners);  /* use this if you use multiple listeners / splitscreen */
    void            (F_API *FSOUND_3D_Listener_SetAttributes)(float *pos, float *vel, float fx, float fy, float fz, float tx, float ty, float tz);
    void            (F_API *FSOUND_3D_Listener_GetAttributes)(float *pos, float *vel, float *fx, float *fy, float *fz, float *tx, float *ty, float *tz);
    signed char     (F_API *FSOUND_Stream_SetBufferSize)(int ms);      /* call this before opening streams, not after */
    FSOUND_STREAM * (F_API *FSOUND_Stream_OpenFile)(const char *filename, unsigned int mode, int memlength);
    FSOUND_STREAM * (F_API *FSOUND_Stream_Create)(FSOUND_STREAMCALLBACK callback, int length, unsigned int mode, int samplerate, int userdata);
    int             (F_API *FSOUND_Stream_Play)(int channel, FSOUND_STREAM *stream);
    int             (F_API *FSOUND_Stream_PlayEx)(int channel, FSOUND_STREAM *stream, FSOUND_DSPUNIT *dsp, signed char startpaused);
    signed char     (F_API *FSOUND_Stream_Stop)(FSOUND_STREAM *stream);
    signed char     (F_API *FSOUND_Stream_Close)(FSOUND_STREAM *stream);
    signed char     (F_API *FSOUND_Stream_SetEndCallback)(FSOUND_STREAM *stream, FSOUND_STREAMCALLBACK callback, int userdata);
    signed char     (F_API *FSOUND_Stream_SetSynchCallback)(FSOUND_STREAM *stream, FSOUND_STREAMCALLBACK callback, int userdata);
    FSOUND_SAMPLE * (F_API *FSOUND_Stream_GetSample)(FSOUND_STREAM *stream);   /* every stream contains a sample to playback on */
    FSOUND_DSPUNIT *(F_API *FSOUND_Stream_CreateDSP)(FSOUND_STREAM *stream, FSOUND_DSPCALLBACK callback, int priority, int param);
    signed char     (F_API *FSOUND_Stream_SetPosition)(FSOUND_STREAM *stream, unsigned int position);
    unsigned int    (F_API *FSOUND_Stream_GetPosition)(FSOUND_STREAM *stream);
    signed char     (F_API *FSOUND_Stream_SetTime)(FSOUND_STREAM *stream, int ms);
    int             (F_API *FSOUND_Stream_GetTime)(FSOUND_STREAM *stream);
    int             (F_API *FSOUND_Stream_GetLength)(FSOUND_STREAM *stream);
    int             (F_API *FSOUND_Stream_GetLengthMs)(FSOUND_STREAM *stream);
    signed char     (F_API *FSOUND_Stream_SetSubStream)(FSOUND_STREAM *stream, int index);
    int             (F_API *FSOUND_Stream_GetNumSubStreams)(FSOUND_STREAM *stream);
    signed char     (F_API *FSOUND_Stream_SetLoopPoints)(FSOUND_STREAM *stream, unsigned int loopstartpcm, unsigned int loopendpcm);
    int             (F_API *FSOUND_Stream_AddSynchPoint)(FSOUND_STREAM *stream, unsigned int pcmoffset, int userdata);
    signed char     (F_API *FSOUND_Stream_DeleteSynchPoint)(FSOUND_STREAM *stream, int index);
    int             (F_API *FSOUND_Stream_GetNumSynchPoints)(FSOUND_STREAM *stream);
    int             (F_API *FSOUND_Stream_GetOpenState)(FSOUND_STREAM *stream);
    signed char     (F_API *FSOUND_CD_Play)(char drive, int track);
    void            (F_API *FSOUND_CD_SetPlayMode)(char drive, signed char mode);
    signed char     (F_API *FSOUND_CD_Stop)(char drive);
    signed char     (F_API *FSOUND_CD_SetPaused)(char drive, signed char paused);
    signed char     (F_API *FSOUND_CD_SetVolume)(char drive, int volume);
    signed char     (F_API *FSOUND_CD_Eject)(char drive);
    signed char     (F_API *FSOUND_CD_GetPaused)(char drive);
    int             (F_API *FSOUND_CD_GetTrack)(char drive);
    int             (F_API *FSOUND_CD_GetNumTracks)(char drive);
    int             (F_API *FSOUND_CD_GetVolume)(char drive);
    int             (F_API *FSOUND_CD_GetTrackLength)(char drive, int track); 
    int             (F_API *FSOUND_CD_GetTrackTime)(char drive);
    FSOUND_DSPUNIT *(F_API *FSOUND_DSP_Create)(FSOUND_DSPCALLBACK callback, int priority, int param);
    void            (F_API *FSOUND_DSP_Free)(FSOUND_DSPUNIT *unit);
    void            (F_API *FSOUND_DSP_SetPriority)(FSOUND_DSPUNIT *unit, int priority);
    int             (F_API *FSOUND_DSP_GetPriority)(FSOUND_DSPUNIT *unit);
    void            (F_API *FSOUND_DSP_SetActive)(FSOUND_DSPUNIT *unit, signed char active);
    signed char     (F_API *FSOUND_DSP_GetActive)(FSOUND_DSPUNIT *unit);
    FSOUND_DSPUNIT *(F_API *FSOUND_DSP_GetClearUnit)();
    FSOUND_DSPUNIT *(F_API *FSOUND_DSP_GetSFXUnit)();
    FSOUND_DSPUNIT *(F_API *FSOUND_DSP_GetMusicUnit)();
    FSOUND_DSPUNIT *(F_API *FSOUND_DSP_GetFFTUnit)();
    FSOUND_DSPUNIT *(F_API *FSOUND_DSP_GetClipAndCopyUnit)();
    signed char     (F_API *FSOUND_DSP_MixBuffers)(void *destbuffer, void *srcbuffer, int len, int freq, int vol, int pan, unsigned int mode);
    void            (F_API *FSOUND_DSP_ClearMixBuffer)();
    int             (F_API *FSOUND_DSP_GetBufferLength)();      /* Length of each DSP update */
    int             (F_API *FSOUND_DSP_GetBufferLengthTotal)(); /* Total buffer length due to FSOUND_SetBufferSize */
    float *         (F_API *FSOUND_DSP_GetSpectrum)();          /* Array of 512 floats - call FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), TRUE)) for this to work. */
    signed char     (F_API *FSOUND_Reverb_SetProperties)(FSOUND_REVERB_PROPERTIES *prop);
    signed char     (F_API *FSOUND_Reverb_GetProperties)(FSOUND_REVERB_PROPERTIES *prop);
    signed char     (F_API *FSOUND_Reverb_SetChannelProperties)(int channel, FSOUND_REVERB_CHANNELPROPERTIES *prop);
    signed char     (F_API *FSOUND_Reverb_GetChannelProperties)(int channel, FSOUND_REVERB_CHANNELPROPERTIES *prop);
    signed char     (F_API *FSOUND_Record_SetDriver)(int outputtype);
    int             (F_API *FSOUND_Record_GetNumDrivers)();
    signed char *   (F_API *FSOUND_Record_GetDriverName)(int id);
    int             (F_API *FSOUND_Record_GetDriver)();
    signed char     (F_API *FSOUND_Record_StartSample)(FSOUND_SAMPLE *sptr, signed char loop);
    signed char     (F_API *FSOUND_Record_Stop)();
    int             (F_API *FSOUND_Record_GetPosition)();  
    FMUSIC_MODULE * (F_API *FMUSIC_LoadSong)(const char *name);
    FMUSIC_MODULE * (F_API *FMUSIC_LoadSongMemory)(void *data, int length);
    signed char     (F_API *FMUSIC_FreeSong)(FMUSIC_MODULE *mod);
    signed char     (F_API *FMUSIC_PlaySong)(FMUSIC_MODULE *mod);
    signed char     (F_API *FMUSIC_StopSong)(FMUSIC_MODULE *mod);
    void            (F_API *FMUSIC_StopAllSongs)();
    signed char     (F_API *FMUSIC_SetZxxCallback)(FMUSIC_MODULE *mod, FMUSIC_CALLBACK callback);
    signed char     (F_API *FMUSIC_SetRowCallback)(FMUSIC_MODULE *mod, FMUSIC_CALLBACK callback, int rowstep);
    signed char     (F_API *FMUSIC_SetOrderCallback)(FMUSIC_MODULE *mod, FMUSIC_CALLBACK callback, int orderstep);
    signed char     (F_API *FMUSIC_SetInstCallback)(FMUSIC_MODULE *mod, FMUSIC_CALLBACK callback, int instrument);
    signed char     (F_API *FMUSIC_SetSample)(FMUSIC_MODULE *mod, int sampno, FSOUND_SAMPLE *sptr);
    signed char     (F_API *FMUSIC_SetUserData)(FMUSIC_MODULE *mod, unsigned int userdata);
    signed char     (F_API *FMUSIC_OptimizeChannels)(FMUSIC_MODULE *mod, int maxchannels, int minvolume);
    signed char     (F_API *FMUSIC_SetReverb)(signed char reverb);             /* MIDI only */
    signed char     (F_API *FMUSIC_SetLooping)(FMUSIC_MODULE *mod, signed char looping);
    signed char     (F_API *FMUSIC_SetOrder)(FMUSIC_MODULE *mod, int order);
    signed char     (F_API *FMUSIC_SetPaused)(FMUSIC_MODULE *mod, signed char pause);
    signed char     (F_API *FMUSIC_SetMasterVolume)(FMUSIC_MODULE *mod, int volume);
    signed char     (F_API *FMUSIC_SetMasterSpeed)(FMUSIC_MODULE *mode, float speed);
    signed char     (F_API *FMUSIC_SetPanSeperation)(FMUSIC_MODULE *mod, float pansep);
    char *          (F_API *FMUSIC_GetName)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetType)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetNumOrders)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetNumPatterns)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetNumInstruments)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetNumSamples)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetNumChannels)(FMUSIC_MODULE *mod);
    FSOUND_SAMPLE * (F_API *FMUSIC_GetSample)(FMUSIC_MODULE *mod, int sampno);
    int             (F_API *FMUSIC_GetPatternLength)(FMUSIC_MODULE *mod, int orderno);
    signed char     (F_API *FMUSIC_IsFinished)(FMUSIC_MODULE *mod);
    signed char     (F_API *FMUSIC_IsPlaying)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetMasterVolume)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetGlobalVolume)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetOrder)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetPattern)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetSpeed)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetBPM)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetRow)(FMUSIC_MODULE *mod);
    signed char     (F_API *FMUSIC_GetPaused)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetTime)(FMUSIC_MODULE *mod);
    int             (F_API *FMUSIC_GetRealChannel)(FMUSIC_MODULE *mod, int modchannel);
    unsigned int    (F_API *FMUSIC_GetUserData)(FMUSIC_MODULE *mod);
} FMOD_INSTANCE;


FMOD_INSTANCE *FMOD_CreateInstance(char *dllName)
{
    FMOD_INSTANCE *instance;

    instance = (FMOD_INSTANCE *) calloc(sizeof(FMOD_INSTANCE), 1);
    if (!instance)
    {
        return NULL;
    }

    instance->module = LoadLibrary(dllName);
    if (!instance->module)
    {
        free(instance);
        return NULL;
    }

    #define GETPROC(_x, _y)                                                                       \
    {                                                                                             \
        *((unsigned int *)&instance->_x) = (unsigned int)GetProcAddress(instance->module, _y);    \
        if (!instance->_x)                                                                        \
        {                                                                                         \
            FreeLibrary(instance->module);                                                        \
            free(instance);                                                                       \
            return NULL;                                                                          \
        }                                                                                         \
    }

    GETPROC(FSOUND_SetOutput, "_FSOUND_SetOutput@4");
    GETPROC(FSOUND_SetDriver, "_FSOUND_SetDriver@4");
    GETPROC(FSOUND_SetMixer, "_FSOUND_SetMixer@4");
    GETPROC(FSOUND_SetBufferSize, "_FSOUND_SetBufferSize@4");
    GETPROC(FSOUND_SetHWND, "_FSOUND_SetHWND@4");
    GETPROC(FSOUND_SetMinHardwareChannels, "_FSOUND_SetMinHardwareChannels@4");
    GETPROC(FSOUND_SetMaxHardwareChannels, "_FSOUND_SetMaxHardwareChannels@4");
    GETPROC(FSOUND_SetMemorySystem, "_FSOUND_SetMemorySystem@20");
    GETPROC(FSOUND_Init, "_FSOUND_Init@12");
    GETPROC(FSOUND_Close, "_FSOUND_Close@0");
    GETPROC(FSOUND_SetSFXMasterVolume, "_FSOUND_SetSFXMasterVolume@4");
    GETPROC(FSOUND_SetPanSeperation, "_FSOUND_SetPanSeperation@4");
    GETPROC(FSOUND_SetSpeakerMode, "_FSOUND_SetSpeakerMode@4");
    GETPROC(FSOUND_GetError, "_FSOUND_GetError@0");
    GETPROC(FSOUND_GetVersion, "_FSOUND_GetVersion@0");
    GETPROC(FSOUND_GetOutput, "_FSOUND_GetOutput@0");
    GETPROC(FSOUND_GetOutputHandle, "_FSOUND_GetOutputHandle@0");
    GETPROC(FSOUND_GetDriver, "_FSOUND_GetDriver@0");
    GETPROC(FSOUND_GetMixer, "_FSOUND_GetMixer@0");
    GETPROC(FSOUND_GetNumDrivers, "_FSOUND_GetNumDrivers@0");
    GETPROC(FSOUND_GetDriverName, "_FSOUND_GetDriverName@4");
    GETPROC(FSOUND_GetDriverCaps, "_FSOUND_GetDriverCaps@8");
    GETPROC(FSOUND_GetOutputRate, "_FSOUND_GetOutputRate@0");
    GETPROC(FSOUND_GetMaxChannels, "_FSOUND_GetMaxChannels@0");
    GETPROC(FSOUND_GetMaxSamples, "_FSOUND_GetMaxSamples@0");
    GETPROC(FSOUND_GetSFXMasterVolume, "_FSOUND_GetSFXMasterVolume@0");
    GETPROC(FSOUND_GetNumHardwareChannels, "_FSOUND_GetNumHardwareChannels@0");
    GETPROC(FSOUND_GetChannelsPlaying, "_FSOUND_GetChannelsPlaying@0");
    GETPROC(FSOUND_GetCPUUsage, "_FSOUND_GetCPUUsage@0");
    GETPROC(FSOUND_GetMemoryStats, "_FSOUND_GetMemoryStats@8");
    GETPROC(FSOUND_Sample_Load, "_FSOUND_Sample_Load@16");
    GETPROC(FSOUND_Sample_Alloc, "_FSOUND_Sample_Alloc@28");
    GETPROC(FSOUND_Sample_Free, "_FSOUND_Sample_Free@4");
    GETPROC(FSOUND_Sample_Upload, "_FSOUND_Sample_Upload@12");
    GETPROC(FSOUND_Sample_Lock, "_FSOUND_Sample_Lock@28");
    GETPROC(FSOUND_Sample_Unlock, "_FSOUND_Sample_Unlock@20");
    GETPROC(FSOUND_Sample_SetMode, "_FSOUND_Sample_SetMode@8");
    GETPROC(FSOUND_Sample_SetLoopPoints, "_FSOUND_Sample_SetLoopPoints@12");
    GETPROC(FSOUND_Sample_SetDefaults, "_FSOUND_Sample_SetDefaults@20");
    GETPROC(FSOUND_Sample_SetMinMaxDistance, "_FSOUND_Sample_SetMinMaxDistance@12");
    GETPROC(FSOUND_Sample_SetMaxPlaybacks, "_FSOUND_Sample_SetMaxPlaybacks@8");
    GETPROC(FSOUND_Sample_Get, "_FSOUND_Sample_Get@4");
    GETPROC(FSOUND_Sample_GetName, "_FSOUND_Sample_GetName@4");
    GETPROC(FSOUND_Sample_GetLength, "_FSOUND_Sample_GetLength@4");
    GETPROC(FSOUND_Sample_GetLoopPoints, "_FSOUND_Sample_GetLoopPoints@12");
    GETPROC(FSOUND_Sample_GetDefaults, "_FSOUND_Sample_GetDefaults@20");
    GETPROC(FSOUND_Sample_GetMode, "_FSOUND_Sample_GetMode@4");
    GETPROC(FSOUND_PlaySound, "_FSOUND_PlaySound@8");
    GETPROC(FSOUND_PlaySoundEx, "_FSOUND_PlaySoundEx@16");
    GETPROC(FSOUND_StopSound, "_FSOUND_StopSound@4");
    GETPROC(FSOUND_SetFrequency, "_FSOUND_SetFrequency@8");
    GETPROC(FSOUND_SetVolume, "_FSOUND_SetVolume@8");
    GETPROC(FSOUND_SetVolumeAbsolute, "_FSOUND_SetVolumeAbsolute@8");
    GETPROC(FSOUND_SetPan, "_FSOUND_SetPan@8");
    GETPROC(FSOUND_SetSurround, "_FSOUND_SetSurround@8");
    GETPROC(FSOUND_SetMute, "_FSOUND_SetMute@8");
    GETPROC(FSOUND_SetPriority, "_FSOUND_SetPriority@8");
    GETPROC(FSOUND_SetReserved, "_FSOUND_SetReserved@8");
    GETPROC(FSOUND_SetPaused, "_FSOUND_SetPaused@8");
    GETPROC(FSOUND_SetLoopMode, "_FSOUND_SetLoopMode@8");
    GETPROC(FSOUND_IsPlaying, "_FSOUND_IsPlaying@4");
    GETPROC(FSOUND_GetFrequency, "_FSOUND_GetFrequency@4");
    GETPROC(FSOUND_GetVolume, "_FSOUND_GetVolume@4");
    GETPROC(FSOUND_GetPan, "_FSOUND_GetPan@4");
    GETPROC(FSOUND_GetSurround, "_FSOUND_GetSurround@4");
    GETPROC(FSOUND_GetMute, "_FSOUND_GetMute@4");
    GETPROC(FSOUND_GetPriority, "_FSOUND_GetPriority@4");
    GETPROC(FSOUND_GetReserved, "_FSOUND_GetReserved@4");
    GETPROC(FSOUND_GetPaused, "_FSOUND_GetPaused@4");
    GETPROC(FSOUND_GetLoopMode, "_FSOUND_GetLoopMode@4");
    GETPROC(FSOUND_GetCurrentPosition, "_FSOUND_GetCurrentPosition@4");
    GETPROC(FSOUND_SetCurrentPosition, "_FSOUND_SetCurrentPosition@8");
    GETPROC(FSOUND_GetCurrentSample, "_FSOUND_GetCurrentSample@4");
    GETPROC(FSOUND_GetCurrentLevels, "_FSOUND_GetCurrentLevels@12");
    GETPROC(FSOUND_FX_Enable, "_FSOUND_FX_Enable@8");
    GETPROC(FSOUND_FX_Disable, "_FSOUND_FX_Disable@4");
    GETPROC(FSOUND_FX_SetChorus, "_FSOUND_FX_SetChorus@32");
    GETPROC(FSOUND_FX_SetCompressor, "_FSOUND_FX_SetCompressor@28");
    GETPROC(FSOUND_FX_SetDistortion, "_FSOUND_FX_SetDistortion@24");
    GETPROC(FSOUND_FX_SetEcho, "_FSOUND_FX_SetEcho@24");
    GETPROC(FSOUND_FX_SetFlanger, "_FSOUND_FX_SetFlanger@32");
    GETPROC(FSOUND_FX_SetGargle, "_FSOUND_FX_SetGargle@12");
    GETPROC(FSOUND_FX_SetI3DL2Reverb, "_FSOUND_FX_SetI3DL2Reverb@52");
    GETPROC(FSOUND_FX_SetParamEQ, "_FSOUND_FX_SetParamEQ@16");
    GETPROC(FSOUND_FX_SetWavesReverb, "_FSOUND_FX_SetWavesReverb@20");
    GETPROC(FSOUND_Update, "_FSOUND_Update@0");
    GETPROC(FSOUND_3D_SetAttributes, "_FSOUND_3D_SetAttributes@12");
    GETPROC(FSOUND_3D_GetAttributes, "_FSOUND_3D_GetAttributes@12");
    GETPROC(FSOUND_3D_Listener_SetCurrent, "_FSOUND_3D_Listener_SetCurrent@8");
    GETPROC(FSOUND_3D_Listener_SetAttributes, "_FSOUND_3D_Listener_SetAttributes@32");
    GETPROC(FSOUND_3D_Listener_GetAttributes, "_FSOUND_3D_Listener_GetAttributes@32");
    GETPROC(FSOUND_3D_SetDopplerFactor, "_FSOUND_3D_SetDopplerFactor@4");
    GETPROC(FSOUND_3D_SetDistanceFactor, "_FSOUND_3D_SetDistanceFactor@4");
    GETPROC(FSOUND_3D_SetRolloffFactor, "_FSOUND_3D_SetRolloffFactor@4");
    GETPROC(FSOUND_Stream_OpenFile, "_FSOUND_Stream_OpenFile@12");
    GETPROC(FSOUND_Stream_Create, "_FSOUND_Stream_Create@20");
    GETPROC(FSOUND_Stream_Play, "_FSOUND_Stream_Play@8");
    GETPROC(FSOUND_Stream_PlayEx, "_FSOUND_Stream_PlayEx@16");
    GETPROC(FSOUND_Stream_Stop, "_FSOUND_Stream_Stop@4");
    GETPROC(FSOUND_Stream_Close, "_FSOUND_Stream_Close@4");
    GETPROC(FSOUND_Stream_SetEndCallback, "_FSOUND_Stream_SetEndCallback@12");
    GETPROC(FSOUND_Stream_SetSynchCallback, "_FSOUND_Stream_SetSynchCallback@12");
    GETPROC(FSOUND_Stream_GetSample, "_FSOUND_Stream_GetSample@4");
    GETPROC(FSOUND_Stream_CreateDSP, "_FSOUND_Stream_CreateDSP@16");
    GETPROC(FSOUND_Stream_SetBufferSize, "_FSOUND_Stream_SetBufferSize@4");
    GETPROC(FSOUND_Stream_SetPosition, "_FSOUND_Stream_SetPosition@8");
    GETPROC(FSOUND_Stream_GetPosition, "_FSOUND_Stream_GetPosition@4");
    GETPROC(FSOUND_Stream_SetTime, "_FSOUND_Stream_SetTime@8");
    GETPROC(FSOUND_Stream_GetTime, "_FSOUND_Stream_GetTime@4");
    GETPROC(FSOUND_Stream_GetLength, "_FSOUND_Stream_GetLength@4");
    GETPROC(FSOUND_Stream_GetLengthMs, "_FSOUND_Stream_GetLengthMs@4");
    GETPROC(FSOUND_Stream_SetSubStream, "_FSOUND_Stream_SetSubStream@8");
    GETPROC(FSOUND_Stream_GetNumSubStreams, "_FSOUND_Stream_GetNumSubStreams@4");
    GETPROC(FSOUND_Stream_SetLoopPoints, "_FSOUND_Stream_SetLoopPoints@12");
    GETPROC(FSOUND_Stream_AddSynchPoint, "_FSOUND_Stream_AddSynchPoint@12");
    GETPROC(FSOUND_Stream_DeleteSynchPoint, "_FSOUND_Stream_DeleteSynchPoint@8");
    GETPROC(FSOUND_Stream_GetNumSynchPoints, "_FSOUND_Stream_GetNumSynchPoints@4");
    GETPROC(FSOUND_Stream_GetOpenState, "_FSOUND_Stream_GetOpenState@4");
    GETPROC(FSOUND_CD_Play, "_FSOUND_CD_Play@8");
    GETPROC(FSOUND_CD_SetPlayMode, "_FSOUND_CD_SetPlayMode@8");
    GETPROC(FSOUND_CD_Stop, "_FSOUND_CD_Stop@4");
    GETPROC(FSOUND_CD_SetPaused, "_FSOUND_CD_SetPaused@8");
    GETPROC(FSOUND_CD_SetVolume, "_FSOUND_CD_SetVolume@8");
    GETPROC(FSOUND_CD_Eject, "_FSOUND_CD_Eject@4");
    GETPROC(FSOUND_CD_GetPaused, "_FSOUND_CD_GetPaused@4");
    GETPROC(FSOUND_CD_GetTrack, "_FSOUND_CD_GetTrack@4");
    GETPROC(FSOUND_CD_GetNumTracks, "_FSOUND_CD_GetNumTracks@4");
    GETPROC(FSOUND_CD_GetVolume, "_FSOUND_CD_GetVolume@4");
    GETPROC(FSOUND_CD_GetTrackLength, "_FSOUND_CD_GetTrackLength@8");
    GETPROC(FSOUND_CD_GetTrackTime, "_FSOUND_CD_GetTrackTime@4");
    GETPROC(FSOUND_DSP_Create, "_FSOUND_DSP_Create@12");
    GETPROC(FSOUND_DSP_Free, "_FSOUND_DSP_Free@4");
    GETPROC(FSOUND_DSP_SetPriority, "_FSOUND_DSP_SetPriority@8");
    GETPROC(FSOUND_DSP_GetPriority, "_FSOUND_DSP_GetPriority@4");
    GETPROC(FSOUND_DSP_SetActive, "_FSOUND_DSP_SetActive@8");
    GETPROC(FSOUND_DSP_GetActive, "_FSOUND_DSP_GetActive@4");
    GETPROC(FSOUND_DSP_GetClearUnit, "_FSOUND_DSP_GetClearUnit@0");
    GETPROC(FSOUND_DSP_GetSFXUnit, "_FSOUND_DSP_GetSFXUnit@0");
    GETPROC(FSOUND_DSP_GetMusicUnit, "_FSOUND_DSP_GetMusicUnit@0");
    GETPROC(FSOUND_DSP_GetClipAndCopyUnit, "_FSOUND_DSP_GetClipAndCopyUnit@0");
    GETPROC(FSOUND_DSP_GetFFTUnit, "_FSOUND_DSP_GetFFTUnit@0");
    GETPROC(FSOUND_DSP_MixBuffers, "_FSOUND_DSP_MixBuffers@28");
    GETPROC(FSOUND_DSP_ClearMixBuffer, "_FSOUND_DSP_ClearMixBuffer@0");
    GETPROC(FSOUND_DSP_GetBufferLength, "_FSOUND_DSP_GetBufferLength@0");
    GETPROC(FSOUND_DSP_GetBufferLengthTotal, "_FSOUND_DSP_GetBufferLengthTotal@0");
    GETPROC(FSOUND_DSP_GetSpectrum, "_FSOUND_DSP_GetSpectrum@0");
    GETPROC(FSOUND_Reverb_SetProperties, "_FSOUND_Reverb_SetProperties@4");
    GETPROC(FSOUND_Reverb_GetProperties, "_FSOUND_Reverb_GetProperties@4");
    GETPROC(FSOUND_Reverb_SetChannelProperties, "_FSOUND_Reverb_SetChannelProperties@8");
    GETPROC(FSOUND_Reverb_GetChannelProperties, "_FSOUND_Reverb_GetChannelProperties@8");
    GETPROC(FSOUND_Record_SetDriver, "_FSOUND_Record_SetDriver@4");
    GETPROC(FSOUND_Record_GetNumDrivers, "_FSOUND_Record_GetNumDrivers@0");
    GETPROC(FSOUND_Record_GetDriverName, "_FSOUND_Record_GetDriverName@4");
    GETPROC(FSOUND_Record_GetDriver, "_FSOUND_Record_GetDriver@0");
    GETPROC(FSOUND_Record_StartSample, "_FSOUND_Record_StartSample@8");
    GETPROC(FSOUND_Record_Stop, "_FSOUND_Record_Stop@0");
    GETPROC(FSOUND_Record_GetPosition, "_FSOUND_Record_GetPosition@0");
    GETPROC(FSOUND_File_SetCallbacks, "_FSOUND_File_SetCallbacks@20");
    GETPROC(FMUSIC_LoadSong, "_FMUSIC_LoadSong@4");
    GETPROC(FMUSIC_LoadSongMemory, "_FMUSIC_LoadSongMemory@8");
    GETPROC(FMUSIC_FreeSong, "_FMUSIC_FreeSong@4");
    GETPROC(FMUSIC_PlaySong, "_FMUSIC_PlaySong@4");
    GETPROC(FMUSIC_StopSong, "_FMUSIC_StopSong@4");
    GETPROC(FMUSIC_StopAllSongs, "_FMUSIC_StopAllSongs@0");
    GETPROC(FMUSIC_SetZxxCallback, "_FMUSIC_SetZxxCallback@8");
    GETPROC(FMUSIC_SetRowCallback, "_FMUSIC_SetRowCallback@12");
    GETPROC(FMUSIC_SetOrderCallback, "_FMUSIC_SetOrderCallback@12");
    GETPROC(FMUSIC_SetInstCallback, "_FMUSIC_SetInstCallback@12");
    GETPROC(FMUSIC_SetSample, "_FMUSIC_SetSample@12");
    GETPROC(FMUSIC_SetUserData, "_FMUSIC_SetUserData@8");
    GETPROC(FMUSIC_OptimizeChannels, "_FMUSIC_OptimizeChannels@12");
    GETPROC(FMUSIC_SetReverb, "_FMUSIC_SetReverb@4");
    GETPROC(FMUSIC_SetLooping, "_FMUSIC_SetLooping@8");
    GETPROC(FMUSIC_SetOrder, "_FMUSIC_SetOrder@8");
    GETPROC(FMUSIC_SetPaused, "_FMUSIC_SetPaused@8");
    GETPROC(FMUSIC_SetMasterVolume, "_FMUSIC_SetMasterVolume@8");
    GETPROC(FMUSIC_SetMasterSpeed, "_FMUSIC_SetMasterSpeed@8");
    GETPROC(FMUSIC_SetPanSeperation, "_FMUSIC_SetPanSeperation@8");
    GETPROC(FMUSIC_GetName, "_FMUSIC_GetName@4");
    GETPROC(FMUSIC_GetType, "_FMUSIC_GetType@4");
    GETPROC(FMUSIC_GetNumOrders, "_FMUSIC_GetNumOrders@4");
    GETPROC(FMUSIC_GetNumPatterns, "_FMUSIC_GetNumPatterns@4");
    GETPROC(FMUSIC_GetNumInstruments, "_FMUSIC_GetNumInstruments@4");
    GETPROC(FMUSIC_GetNumSamples, "_FMUSIC_GetNumSamples@4");
    GETPROC(FMUSIC_GetNumChannels, "_FMUSIC_GetNumChannels@4");
    GETPROC(FMUSIC_GetSample, "_FMUSIC_GetSample@8");
    GETPROC(FMUSIC_GetPatternLength, "_FMUSIC_GetPatternLength@8");
    GETPROC(FMUSIC_IsFinished, "_FMUSIC_IsFinished@4");
    GETPROC(FMUSIC_IsPlaying, "_FMUSIC_IsPlaying@4");
    GETPROC(FMUSIC_GetMasterVolume, "_FMUSIC_GetMasterVolume@4");
    GETPROC(FMUSIC_GetGlobalVolume, "_FMUSIC_GetGlobalVolume@4");
    GETPROC(FMUSIC_GetOrder, "_FMUSIC_GetOrder@4");
    GETPROC(FMUSIC_GetPattern, "_FMUSIC_GetPattern@4");
    GETPROC(FMUSIC_GetSpeed, "_FMUSIC_GetSpeed@4");
    GETPROC(FMUSIC_GetBPM, "_FMUSIC_GetBPM@4");
    GETPROC(FMUSIC_GetRow, "_FMUSIC_GetRow@4");
    GETPROC(FMUSIC_GetPaused, "_FMUSIC_GetPaused@4");
    GETPROC(FMUSIC_GetTime, "_FMUSIC_GetTime@4");
    GETPROC(FMUSIC_GetRealChannel, "_FMUSIC_GetRealChannel@8");
    GETPROC(FMUSIC_GetUserData, "_FMUSIC_GetUserData@4");

    return instance;
}

void FMOD_FreeInstance(FMOD_INSTANCE *instance)
{
    if (instance)
    {
        if (instance->module)
        {
            FreeLibrary(instance->module);
        }
        free(instance);
    }
}

#endif
