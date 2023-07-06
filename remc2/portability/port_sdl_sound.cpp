#include <iostream>
#include <fcntl.h>
#include "../engine/engine_support.h"
#include "port_openal.h"
#include "port_sdl_sound.h"

#ifdef __linux__
#include <limits>
#define MAX_PATH PATH_MAX
#endif

/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

bool debug_first_sound = true;

bool hqsound = false;
bool oggmusic = false;
bool oggmusicalternative = false;
char oggmusicFolder[512];
char speech_folder[512];

bool fixspeedsound = false;

int32_t last_sequence_num = 0;

int lastMusicVolume = -1;
int settingsMusicVolume = 127;
int num_IO_configurations = 3;
int service_rate = -1;
int master_volume = -1;

#ifdef SOUND_SDLMIXER
Mix_Music *GAME_music[20] =
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL
};
#endif

Mix_Chunk gamechunk[32];        //OPENAL_CHANNELS];
HSAMPLE gamechunkHSAMPLE[32];   //OPENAL_CHANNELS];

extern char x_BYTE_E2A28_speech;

uint8_t sound_buffer[4][20000];
/*
10
29

128-0
0-0
0-10
0-29
0-80
0-76
0-78
0-78

 channel 1
 2

*/

void SOUND_start_sequence(int32_t sequence_num)
{
    if (unitTests)
        return;
    //3 - menu
    //4 - intro
#ifdef SOUND_SDLMIXER
    last_sequence_num = sequence_num;
    //volume fix
    if (lastMusicVolume == -1) {
        SOUND_set_sequence_volume(0x64, 0);
    }
    if (lastMusicVolume != settingsMusicVolume) {
        SOUND_set_sequence_volume(settingsMusicVolume, 0);
    }
    //volume fix

    if (Mix_PlayingMusic() == 0) {
        if (Mix_PlayMusic(GAME_music[sequence_num], -1) == -1)
            if (Mix_PausedMusic() == 1) {
                Mix_ResumeMusic();
            } else {
                Mix_PauseMusic();
            }
    }
#endif                          //SOUND_SDLMIXER
};

void SOUND_pause_sequence(int32_t /*sequence_num */ )
{
    if (unitTests)
        return;
#ifdef SOUND_SDLMIXER
    Mix_PauseMusic();
#endif                          //SOUND_SDLMIXER
};

void SOUND_stop_sequence(int32_t /*sequence_num */ )
{
    if (unitTests)
        return;
#ifdef SOUND_SDLMIXER
    Mix_HaltMusic();
#endif                          //SOUND_SDLMIXER
};

void SOUND_resume_sequence(int32_t /*sequence_num */ )
{
    if (unitTests)
        return;
#ifdef SOUND_SDLMIXER
    Mix_ResumeMusic();
#endif                          //SOUND_SDLMIXER
};

void SOUND_set_sequence_volume(int32_t volume, int32_t milliseconds)
{
    if (unitTests)
        return;
    //Logger->info("SOUND_set_sequence_volume  vol {}  ms {}", volume, milliseconds);
#ifdef SOUND_SDLMIXER
#ifndef __linux__
    if ((milliseconds > 0) && (volume == 0)) {
        if (GAME_music[last_sequence_num]) {
            double position = Mix_GetMusicPosition(GAME_music[last_sequence_num]);
            if (position != 0) {
                Mix_FadeOutMusic(milliseconds);
                Mix_SetMusicPosition(position);
            }
        }
    } else if ((milliseconds > 0) && (lastMusicVolume == 0)) {
        if (GAME_music[last_sequence_num]) {
            double position = Mix_GetMusicPosition(GAME_music[last_sequence_num]);
            if (position != 0) {
                Mix_FadeInMusicPos(GAME_music[last_sequence_num], 1, milliseconds, position);
            }
        }
    } else
#endif                          //__linux__
        Mix_VolumeMusic(volume);
    lastMusicVolume = volume;
    if (milliseconds == 0)
        settingsMusicVolume = volume;
#endif                          //SOUND_SDLMIXER
}

void SOUND_init_MIDI_sequence(uint8_t * /*datax */ , type_E3808_music_header *headerx,
                              int32_t track_number)
{
    //Logger->info("SOUND_init_MIDI_sequence {}", track_number);
    if (unitTests)
        return;
    //uint8_t* acttrack = &header[32 + track_number * 32];
    uint8_t *acttrack = headerx->str_8.track_10[track_number].xmiData_0;
    //int testsize = *(uint32_t*)(&header[32 + (track_number + 1) * 32] + 18) - *(uint32_t*)(acttrack + 18);
    int testsize2 = *(uint32_t *) (acttrack + 26);

    //we can translate datax from xmi to mid and play(with bad quality or slow midi emulators), at now but we use ogg samples
    //unsigned char* TranscodeXmiToMid(const unsigned char* pXmiData,       size_t iXmiLength, size_t* pMidLength);
    size_t iXmiLength = testsize2; // FIXME this size is completely bogus - between 0.8 and 1.2TB!!!
    size_t pMidLength;
    dirsstruct helpdirsstruct;

    if (oggmusic) {

        std::string oggmusicPath = GetSubDirectoryPath(oggmusicFolder);
        // FIXME 1024bytes added to the stack
        char alternativeMusicPath[512] = "";
        char selectedTrackPath[512] = "";
        //if (track_number > 1)track_number = 0;
        if (oggmusicalternative)        ///&&track_number==4
        {
            if (track_number == 0) {
                sprintf(alternativeMusicPath, "%s/alternative/day", oggmusicPath.c_str());
            } else if (track_number == 1) {
                sprintf(alternativeMusicPath, "%s/alternative/night", oggmusicPath.c_str());
            } else if (track_number == 2) {
                sprintf(alternativeMusicPath, "%s/alternative/cave", oggmusicPath.c_str());
            } else if (track_number == 3) {
                sprintf(alternativeMusicPath, "%s/alternative/cave", oggmusicPath.c_str());
            } else if (track_number == 4) {
                sprintf(alternativeMusicPath, "%s/alternative/cave", oggmusicPath.c_str());
            } else if (track_number == 5) {
                sprintf(alternativeMusicPath, "%s/alternative/cave", oggmusicPath.c_str());
            } else {
                sprintf(alternativeMusicPath, "%s/alternative/cave", oggmusicPath.c_str());
            }

            helpdirsstruct = getListDir(alternativeMusicPath);

            if (helpdirsstruct.number > 0) {
                int randtrack = rand() % (helpdirsstruct.number + 1);
                if (randtrack == 0)
                    sprintf(selectedTrackPath, "%s/music%d.ogg", oggmusicPath.c_str(),
                            track_number);
                else
                    sprintf(selectedTrackPath, "%s/%s", alternativeMusicPath,
                            helpdirsstruct.dir[randtrack - 1]);
            } else
                sprintf(selectedTrackPath, "%s/music%d.ogg", oggmusicPath.c_str(), track_number);
        } else
            sprintf(selectedTrackPath, "%s/music%d.ogg", oggmusicPath.c_str(), track_number);
#ifdef SOUND_SDLMIXER
        GAME_music[track_number] = Mix_LoadMUS(selectedTrackPath);
#endif                          //SOUND_SDLMIXER
    } else {
        uint8_t *outmidi =
            TranscodeXmiToMid( /*(const uint8_t*)*(uint32_t*)( */ acttrack /* + 18) */ , iXmiLength,
                              &pMidLength);
        SDL_RWops *rwmidi = SDL_RWFromMem(outmidi, pMidLength);
        //Logger->info("SOUND_init_MIDI_sequence  xmi {}  mid {}", iXmiLength, pMidLength);
        //alsound_save_chunk(outmidi, pMidLength, NULL);
        //Timidity_Init();
#ifdef SOUND_SDLMIXER
        GAME_music[track_number] = Mix_LoadMUSType_RW(rwmidi, MUS_MID, SDL_TRUE); // FIXME
#endif                          //SOUND_SDLMIXER
        //music2 = Mix_LoadMUSType_RW(rwmidi, MIX_MUSIC_TIMIDITY, SDL_TRUE);

    }
}

void SOUND_start_speech(const uint8_t track, const uint16_t offset, const uint16_t len)
{
    size_t track_str_len;
    char *track_filename = NULL;
    uint8_t *track_data = NULL;
    uint32_t track_data_len;
    uint32_t track_offset;
    int fd;
    Mix_Chunk chunk = {};

    Logger->debug("SOUND_start_speech  track {}  offset {}  len {}", track, offset, len);

    std::string speech_path = GetSubDirectoryPath(speech_folder);
    track_str_len = speech_path.length() + 13;

    track_filename = (char *) calloc(track_str_len, sizeof(char));
    if (!track_filename) {
        return;
    }

    snprintf(track_filename, track_str_len, "%s/track%02d.cdr", speech_path.c_str(), track);

	if (!std::filesystem::exists(track_filename))
		snprintf(track_filename, track_str_len, "%s/track%02d.wav", speech_path.c_str(), track);

    Logger->debug("track: {}", track_filename);

    track_data_len = len * 2360;
    track_offset = offset * 2360;
    track_data = (uint8_t *) calloc(track_data_len, sizeof(uint8_t));
    if (!track_data) {
        goto cleanup_nofreedata;
    }

    if ((fd = open(track_filename, O_RDONLY)) < 0) {
        Logger->warn("unable to open speech file {}", track_filename);
        goto cleanup_nofreedata;
    }

    if (lseek(fd, track_offset, SEEK_SET) != track_offset) {
        Logger->warn("wrong offset {} in speech file {}", track_offset, track_filename);
        goto cleanup;
    }

    if (read(fd, track_data, track_data_len) == -1) {
        Logger->warn("can't read speech file {}", track_filename);
        goto cleanup;
    }

    chunk.allocated = 1;
    chunk.alen = track_data_len;
    chunk.abuf = track_data;
    chunk.volume = 127;

    //alsound_save_chunk(track_data, track_data_len, NULL);

#ifdef SOUND_OPENAL
    uint16_t format;

    format = alsound_get_chunk_flags(OPENAL_CC_SZ - 1);
    alsound_play(OPENAL_CC_SZ - 1, &chunk, nullptr, nullptr, format | AL_TYPE_SPEECH);
    free(track_data);

#elif defined (SOUND_SDLMIXER)

    Mix_PlayChannel(-1, &chunk, 0);
    // due to chunk.allocated == 1, track_data will be freed by sdlmixer once the chunk has been played

#endif

cleanup: 
    close(fd);
cleanup_nofreedata:
    free(track_filename);
}

void clean_up_sound()
{
    if (unitTests)
        return;

#ifdef SOUND_SDLMIXER
    for (int i = 0; i < 10; i++) {
        Mix_FreeMusic(GAME_music[i]);
    }

    Mix_CloseAudio();
#endif
}

void playmusic2(int32_t track_number)
{
    //Logger->info("playmusic2 {}", track_number);
    if (unitTests)
        return;
#ifdef SOUND_SDLMIXER
    if (Mix_PlayingMusic() == 0) {
        //Play the music
        if (Mix_PlayMusic(GAME_music[track_number], -1) == -1)
            if (Mix_PausedMusic() == 1) {
                //Resume the music
                Mix_ResumeMusic();
            }
        //If the music is playing
            else {
                //Pause the music
                Mix_PauseMusic();
            }
    }
#endif                          //SOUND_SDLMIXER
}

struct {
    int a;
} common_IO_configurations;

struct {
    int a;
} environment_string;

int32_t ac_sound_call_driver(AIL_DRIVER *drvr, int32_t fn, VDI_CALL *out)
{
    switch (fn) {
    case 0x300:{               //AIL_API_install_driver
            drvr->VHDR_4->VDI_HDR_var10 = (void *)&common_IO_configurations;
            drvr->VHDR_4->num_IO_configurations_14 = num_IO_configurations;
            drvr->VHDR_4->environment_string_16 = environment_string.a;
            drvr->VHDR_4->VDI_HDR_var46 = service_rate;
            break;
        }
    case 0x301:{               //AIL_API_install_DIG_driver_file/AIL_API_install_MDI_driver_file          
            out->AX = 1;        //offset
            out->BX = 2;        //offset
            out->SI = 0;
            out->DI = 0;
            break;
        }
    case 0x304:{               //AIL_API_install_DIG_driver_file/AIL_API_install_MDI_driver_file
            break;
        }
    case 0x305:{               //AIL_API_install_DIG_driver_file/AIL_API_install_MDI_driver_file
            break;
        }
    case 0x306:{               //AIL_API_uninstall_driver/AIL_API_uninstall_MDI_driver_file
            break;
        }
    case 0x401:{
            /*              mychunk.abuf=(uint8_t*)last_sample->start_2_3[0];
               mychunk.alen = last_sample->len_4_5[0];
               mychunk.volume = last_sample->volume_16;
               //mychunk.allocated = 0;

               #ifdef USE_SDL2
               Mix_PlayChannel(-1, &mychunk, 0);
               #else
               Mix_PlayChannel(-1, &mychunk, 0);
               #endif */
            break;
        }
    case 0x501:{               //AIL_API_install_MDI_INI
            break;
        }
    case 0x502:{               //AIL_API_install_MDI_INI
            break;
        }
    default:
        {
            break;
        }
    }
    return 1;
};

void SOUND_set_master_volume(int32_t volume)
{
#ifdef SOUND_SDLMIXER
    master_volume = volume;

    for (int i = 0; i < 32; i++)
        Mix_Volume(i, (int)((gamechunk[i].volume * master_volume) / 127));
#endif

    //may be can fix - must analyze
}

void SOUND_set_sample_volume(HSAMPLE S, int32_t volume)
{
#ifdef SOUND_OPENAL
    //Logger->info("SOUND_set_sample_volume id {}  vol {}", S->id, volume);
    alsound_set_sample_volume(S->id, volume);
#elif defined(SOUND_SDLMIXER)
    if (master_volume == -1)
        master_volume = 127;
    gamechunk[S->index_sample].volume = volume;
    Mix_Volume(S->index_sample, (int)((gamechunk[S->index_sample].volume * master_volume) / 127));
#endif                          //SOUND_SDLMIXER
}

void SOUND_start_sample(HSAMPLE S)
{
    if (unitTests)
        return;

#ifdef SOUND_OPENAL
    uint16_t format;

    format = alsound_get_chunk_flags(S->id);

    if (format & AL_FORMAT_STEREO8_22050) {
        gamechunk[S->index_sample].abuf = (uint8_t *) S->wavbuff;
        gamechunk[S->index_sample].alen = S->len_4_5[0] * 2;
    } else {
        gamechunk[S->index_sample].abuf = (uint8_t *) S->start_2_3[0];
        gamechunk[S->index_sample].alen = S->len_4_5[0];
    }
    gamechunk[S->index_sample].volume = S->volume_16;
    gamechunkHSAMPLE[S->index_sample] = S;

    alsound_play(S->id, &gamechunk[S->index_sample], nullptr, nullptr, format);

    //alsound_update();
#elif defined (SOUND_SDLMIXER)
    if (hqsound) {
        gamechunk[S->index_sample].abuf = /*sample->abuf;// */ (uint8_t *) S->start_44mhz;
        if (fixspeedsound)
            gamechunk[S->index_sample].alen = /*sample->alen;// */ S->len_4_5[0] * 16;
        else
            gamechunk[S->index_sample].alen = /*sample->alen;// */ S->len_4_5[0] * 8;
        if (debug_first_sound) {
            Logger->trace("SOUND_start_sample-hq:{}", S->start_44mhz);
            debug_first_sound = false;
        }
    } else {
        if (debug_first_sound) {
            Logger->trace("SOUND_start_sample:{}", S->start_44mhz);
            debug_first_sound = false;
        }
        gamechunk[S->index_sample].abuf = (uint8_t *) S->start_2_3[0];
        gamechunk[S->index_sample].alen = S->len_4_5[0];
    }

    gamechunk[S->index_sample].volume = S->volume_16;
    gamechunkHSAMPLE[S->index_sample] = S;

    //alsound_save_chunk(gamechunk[S->index_sample].abuf, gamechunk[S->index_sample].alen, NULL);

    Mix_PlayChannel(S->index_sample, &gamechunk[S->index_sample], 0);
#endif
};

uint32_t SOUND_sample_status(HSAMPLE S)
{
    if (unitTests)
        return 0;

#ifdef SOUND_OPENAL
    if (alsound_sample_status(S->id) == 0) {
        return 2;
    }
#elif defined(SOUND_SDLMIXER)
    if (Mix_Playing(S->index_sample) == 0)
        return 2;
#endif                          //SOUND_SDLMIXER
    return 0;
}

void SOUND_end_sample(HSAMPLE S)
{

#ifdef SOUND_OPENAL
    //Logger->info("SOUND_end_sample {} {}", S->id, S->len_4_5[0] * 2);
    alsound_end_sample(S->id);
#elif defined(SOUND_SDLMIXER)
    Mix_HaltChannel(-1);
#endif                          //SOUND_SDLMIXER
};

void SOUND_finalize(int channel)
{
    HSAMPLE S = gamechunkHSAMPLE[channel];
    if (S) {
        if (S->status_1 != 1) {
            if (S->status_1 != 2) {
                S->status_1 = 2;
            }
        }
        S->vol_scale_18[0][0] = 0;
        S->flags_14 = 0;
        S->vol_scale_18[0][2] = 0;
        S->vol_scale_18[0][3] = 0;
    }
}

bool init_sound()
{
    //#define MUSIC_MID_FLUIDSYNTH
    srand(time(NULL));
#ifdef SOUND_SDLMIXER
    if (hqsound) {
        if (Mix_OpenAudio(44100, AUDIO_S16, 2, 4096) == -1)     //4096
            //if (Mix_OpenAudio(44100, AUDIO_S16, 2, 4096) == -1)//4096
            //if (Mix_OpenAudio(11025, AUDIO_S8, 1, 4096) == -1)//4096
        {
            return false;
        }
    } else {
        if (Mix_OpenAudio(22050, AUDIO_U8 /*MIX_DEFAULT_FORMAT */ , 2, 4096) == -1)     //4096
            //if (Mix_OpenAudio(11025/*22050*/, AUDIO_U8/*MIX_DEFAULT_FORMAT*/, 1, 4096) == -1)//4096
        {
            return false;
        }
    }

    //Mix_SetSoundFonts("c:\\prenos\\Magic2\\sf2\\TOM-SF2.sf2");
    //Mix_SetSoundFonts("touhou.sf2");
    //load_sound_files();
    /*if(mp3music)
       load_music_files(); */
    /*
       Mix_HookMusicFinished(void (SDLCALL *music_finished)(void));
     */
    Mix_ChannelFinished(SOUND_finalize);
#endif
#ifdef SOUND_OPENAL
    alsound_init();
#endif
    return true;
}

AIL_DRIVER *ac_AIL_API_install_driver(int /*a1 */ , uint8_t * /*a2 */ , int /*a3 */ )   /*driver_image,n_bytes *///27f720
{

    //printf("drvr:%08X, fn:%08X, in:%08X, out:%08X\n", drvr, fn, in, out);
    return 0;
}

uint16_t actvect[4096];

void ac_set_real_vect(uint32_t vectnum, uint16_t real_ptr)
{
    actvect[vectnum] = real_ptr;
    //66
};

uint16_t ac_get_real_vect(uint32_t vectnum)
{
    return actvect[vectnum];
};

void SOUND_UPDATE()
{
#ifdef SOUND_OPENAL
    alsound_update();
#endif
};
