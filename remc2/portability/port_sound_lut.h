#pragma once
#ifndef PORT_SOUND_LUT_H
#define PORT_SOUND_LUT_H

#include "port_sdl_joystick.h"

#define   OPENAL_CHANNELS  24
#define       OPENAL_C_SZ  OPENAL_CHANNELS     ///< number of chunks that can play at the same time (aka number of voices)
#define      OPENAL_CC_SZ  128     ///< number of chunks the cache can hold

////< flags used by alsound_set_env()
#define       AL_SET_BANK  0x1

#define   AL_BANK_MAP_DAY  0x0
#define AL_BANK_MAP_NIGHT  0x1
#define  AL_BANK_MAP_CAVE  0x2
#define      AL_BANK_MENU  0x4

#define   AL_FORMAT_STEREO8_22050  0x01
#define     AL_FORMAT_MONO8_22050  0x02
#define  AL_FORMAT_STEREO16_44100  0x04
#define               AL_TYPE_ENV  0x08
#define        AL_TYPE_POSITIONAL  0x10
#define            AL_TYPE_SPEECH  0x20
#define          AL_IGNORE_RECODE  0x40

#define          AL_REPLAY_RARELY  0x01 // long intervals of silence
#define      AL_REPLAY_FREQUENTLY  0x02 // short intervals of silence
#define         AL_POWERFUL_SHOUT  0x04 // controls the reference distance and gain
#define                AL_WHISPER  0x08 // controls the reference distance and gain

struct al_chunk_table {
    uint8_t flags;              // sound format, type, extra options 
    int8_t ff_fx;               // force-feedback effect id
};
typedef struct al_chunk_table al_ct_t;

const al_ct_t alct[3][70] = {
    {                           // day
     {0, -1},                    // id_0 -
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_1 OCEAN.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_2 WIND.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_3 EXPLOD3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_4 GAINMANA.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_5 FIRE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_6 ALLY.WAV
     {0, -1},                    // id_7 NULL.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_8 DRAGROAR.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_9 FIREBAL1.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_QUAKE},        // id_10 QUAKE4.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_11 FOOLMANA.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_12 BEE1.WAV
     {0, -1},                    // id_13 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_14 SELECT.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_15 FIREBAL2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_16 DIE.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_17 HYDRA.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_18 GETSPELL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_19 SPEEDUP.WAV
     {0, -1},                    // id_20 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_21 PORTMAKE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_22 PORTUSE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_23 LITNING.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_24 EXPLOD3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_25 HEAL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_26 CLANG.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_27 SPLASH2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_28 REBOUND.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_29 CANTUSE.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_METEOR},        // id_30 METEOREX.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_31 MARKET.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_32 SPIDER.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_33 ARROW1.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_34 ARROW2.WAV
     {0, -1},                    // id_35 NULL.WAV
     {0, -1},                    // id_36 NULL.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_37 CYMERIAN.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_38 DEEPONE.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_39 WYVERN.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_40 MANASHOT.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_41 SWITCH.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_42 DEVIL.WAV
     {0, -1},                    // id_43 NULL.WAV
     {0, -1},                    // id_44 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_45 FIRE.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1}, // id_46 GOAT.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_47 DOORC2.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_48 MWORM3.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_TORNADO},        // id_49 TORNADO.WAV
     {0, -1},                    // id_50 NULL.WAV
     {0, -1},                    // id_51 NULL.WAV
     {0, -1},                    // id_52 NULL.WAV
     {0, -1},                    // id_53 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_54 HIT1.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_55 HIT2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_56 HIT3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_57 HIT4.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_58 MADDOG.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_59 MDWELLER.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_60 MORPH.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_61 SUCCESS2.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_62 ZOMBIE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_63 SPELLUP.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_64 GWELL.WAV
     {0, -1},                    // id_65 -
     {0, -1},                    // id_66 -
     {0, -1},                    // id_67 -
     {0, -1},                    // id_68 -
     {0, -1}                     // id_69 -
     },
    {                           // night
     {0, -1},                    // id_0 -
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_1 OCEAN.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_2 CRICKET2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_3 EXPLOD3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_4 GAINMANA.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_5 FIRE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_6 ALLY.WAV
     {0, -1},                    // id_7 NULL.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_8 DRAGROAR.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_9 FIREBAL1.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_QUAKE},        // id_10 QUAKE4.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_11 FOOLMANA.WAV
     {0, -1},                    // id_12 NULL.WAV
     {0, -1},                    // id_13 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_14 SELECT.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_15 FIREBAL2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_16 DIE.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_17 HYDRA.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_18 GETSPELL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_19 SPEEDUP.WAV
     {0, -1},                    // id_20 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_21 PORTMAKE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_22 PORTUSE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_23 LITNING.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_24 EXPLOD3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_25 HEAL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_26 CLANG.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_27 SPLASH2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_28 REBOUND.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_29 CANTUSE.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_METEOR},        // id_30 METEOREX.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_31 MARKET.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_32 SPIDER.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_33 ARROW1.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_34 ARROW2.WAV
     {0, -1},                    // id_35 NULL.WAV
     {0, -1},                    // id_36 NULL.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_37 CYMERIAN.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_38 DEEPONE.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_39 WYVERN.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_40 MANASHOT.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_41 SWITCH.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_42 DEVIL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_43 FIREFLY1.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_44 FIREFLY2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_45 FIRE.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1}, // id_46 GOAT.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_47 DOORC2.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_48 MWORM3.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_TORNADO},        // id_49 TORNADO.WAV
     {0, -1},                    // id_50 NULL.WAV
     {0, -1},                    // id_51 NULL.WAV
     {0, -1},                    // id_52 NULL.WAV
     {0, -1},                    // id_53 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_54 HIT1.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_55 HIT2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_56 HIT3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_57 HIT4.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_58 MADDOG.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_59 MDWELLER.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_60 MORPH.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_61 SUCCESS2.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_62 ZOMBIE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_63 SPELLUP.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_64 GWELL.WAV
     {0, -1},                    // id_65 -
     {0, -1},                    // id_66 -
     {0, -1},                    // id_67 -
     {0, -1},                    // id_68 -
     {0, -1}                     // id_69 -
     },
    {                           // cave
     {0, -1},                    // id_0 -
     {0, -1},                    // id_1 NULL.WAV
     {0, -1},                    // id_2 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_3 EXPLOD3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_4 GAINMANA.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_5 FIRE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_6 ALLY.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_7 CAVEMAN.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_8 DRAGROAR.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_9 FIREBAL1.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_QUAKE},        // id_10 QUAKE4.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_11 FOOLMANA.WAV
     {0, -1},                    // id_12 NULL.WAV
     {0, -1},                    // id_13 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_14 SELECT.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_15 FIREBAL2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_16 DIE.WAV
     {0, -1},                    // id_17 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_18 GETSPELL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_19 SPEEDUP.WAV
     {0, -1},                    // id_20 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_21 PORTMAKE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_22 PORTUSE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_23 LITNING.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_24 EXPLOD3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_25 HEAL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_26 CLANG.WAV
     {0, -1},                    // id_27 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_28 REBOUND.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_29 CANTUSE.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_METEOR},        // id_30 METEOREX.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_31 MARKET.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_32 SPIDER.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_33 ARROW1.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_34 ARROW2.WAV
     {0, -1},                    // id_35 NULL.WAV
     {0, -1},                    // id_36 NULL.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_37 CYMERIAN.WAV
     {0, -1},                    // id_38 NULL.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1}, // id_39 WYVERN.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_40 MANASHOT.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_41 SWITCH.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_42 DEVIL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_43 FIREFLY1.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_44 FIREFLY2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_45 FIRE.WAV
     {0, -1},                    // id_46 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_47 DOORC2.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_48 MWORM3.WAV
     {AL_FORMAT_MONO8_22050, GP_HAPTIC_TORNADO},        // id_49 TORNADO.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_50 GLOOP1.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_51 GLOOP2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_52 GLOOP3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_53 GLOOP4.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_54 HIT1.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_55 HIT2.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_56 HIT3.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_57 HIT4.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_58 MADDOG.WAV
     {0, -1},                    // id_59 NULL.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_60 MORPH.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_61 SUCCESS2.WAV
     {AL_FORMAT_MONO8_22050 | AL_IGNORE_RECODE, -1},        // id_62 ZOMBIE.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_63 SPELLUP.WAV
     {AL_FORMAT_MONO8_22050, -1},        // id_64 GWELL.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_65 DRIP1.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_66 DRIP2.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_67 DRIP3.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1},        // id_68 DRIP4.WAV
     {AL_FORMAT_STEREO8_22050 | AL_TYPE_ENV, -1} // id_69 DRIP5.WAV
     }
};


const char alct_name[3][70][9] = {
    { // day
        "null",
        "ocean",
        "wind",
        "explod3",
        "gainmana",
        "fire",
        "ally",
        "null",
        "dragroar",
        "firebal1",
        "quake4",
        "foolmana",
        "bee1",
        "null",
        "select",
        "firebal2",
        "die",
        "hydra",
        "getspell",
        "speedup",
        "null",
        "portmake",
        "portuse",
        "litning",
        "explod3",
        "heal",
        "clang",
        "splash2",
        "rebound",
        "cantuse",
        "meteorex",
        "market",
        "spider",
        "arrow1",
        "arrow2",
        "null",
        "null",
        "cymerian",
        "deepone",
        "wyvern",
        "manashot",
        "switch",
        "devil",
        "null",
        "null",
        "fire",
        "goat",
        "doorc2",
        "mworm3",
        "tornado",
        "null",
        "null",
        "null",
        "null",
        "hit1",
        "hit2",
        "hit3",
        "hit4",
        "maddog",
        "mdweller",
        "morph",
        "success2",
        "zombie",
        "spellup",
        "gwell",
        "null",
        "null",
        "null",
        "null",
        "null"
    },
    { // night
        "null",
        "ocean",
        "cricket2",
        "explod3",
        "gainmana",
        "fire",
        "ally",
        "null",
        "dragroar",
        "firebal1",
        "quake4",
        "foolmana",
        "null",
        "null",
        "select",
        "firebal2",
        "die",
        "hydra",
        "getspell",
        "speedup",
        "null",
        "portmake",
        "portuse",
        "litning",
        "explod3",
        "heal",
        "clang",
        "splash2",
        "rebound",
        "cantuse",
        "meteorex",
        "market",
        "spider",
        "arrow1",
        "arrow2",
        "null",
        "null",
        "cymerian",
        "deepone",
        "wyvern",
        "manashot",
        "switch",
        "devil",
        "firefly1",
        "firefly2",
        "fire",
        "goat",
        "doorc2",
        "mworm3",
        "tornado",
        "null",
        "null",
        "null",
        "null",
        "hit1",
        "hit2",
        "hit3",
        "hit4",
        "maddog",
        "mdweller",
        "morph",
        "success2",
        "zombie",
        "spellup",
        "gwell",
        "null",
        "null",
        "null",
        "null",
        "null"
    },
    { // cave
        "null",
        "null",
        "null",
        "explod3",
        "gainmana",
        "fire",
        "ally",
        "caveman",
        "dragroar",
        "firebal1",
        "quake4",
        "foolmana",
        "null",
        "null",
        "select",
        "firebal2",
        "die",
        "null",
        "getspell",
        "speedup",
        "null",
        "portmake",
        "portuse",
        "litning",
        "explod3",
        "heal",
        "clang",
        "null",
        "rebound",
        "cantuse",
        "meteorex",
        "market",
        "spider",
        "arrow1",
        "arrow2",
        "null",
        "null",
        "cymerian",
        "null",
        "wyvern",
        "manashot",
        "switch",
        "devil",
        "firefly1",
        "firefly2",
        "fire",
        "null",
        "doorc2",
        "mworm3",
        "tornado",
        "gloop1",
        "gloop2",
        "gloop3",
        "gloop4",
        "hit1",
        "hit2",
        "hit3",
        "hit4",
        "maddog",
        "null",
        "morph",
        "success2",
        "zombie",
        "spellup",
        "gwell",
        "drip1",
        "drip2",
        "drip3",
        "drip4",
        "drip5"
    }
};

struct al_creature_table {
    uint8_t flags;              // sound-related options
    int16_t chunk_id;           // chunk identifier to play
};
typedef struct al_creature_table al_crt_t;

const al_crt_t alcrt[29] = {
    {0, 8}, // 0 dragons
    {AL_REPLAY_RARELY | AL_WHISPER, 46}, // 1 goat
    {0, 12}, // 2 bee
    {0, 8}, // 3 worms
    {0, -1}, // 4 archer - creature is silent
    {0, -1}, // 5 -
    {0, -1}, // 6 -
    {0, -1}, // 7 -
    {0, -1}, // 8 -
    {0, -1}, // 9 skeleton
    {0, -1}, // 10 vissuluth - creature is normally silent
    {0, -1}, // 11 -
    {0, -1}, // 12 builder
    {0, -1}, // 13 townie
    {0, -1}, // 14 trader
    {0, -1}, // 15 castle archer  - it's sound sample is in sync with him shooting, so don't schedule
    {AL_POWERFUL_SHOUT, 39}, // 16 wyvern
    {AL_POWERFUL_SHOUT, 58}, // 17 manticore
    {0, -1}, // 18 sentinel - this creature is quiet afaict
    {AL_WHISPER, 44}, // 19 firefly
    {0, 32}, // 20 spider
    {0, 42}, // 21 devil
    {0, 48}, // 22 mana worm
    {0, 59}, // 23 moon dweller
    {0, 7}, // 24 troglodyte
    {0, 37}, // 25 cymmerian
    {AL_WHISPER, 62}, // 26 zombie
    {AL_POWERFUL_SHOUT, 17}, // 27 hydra
    {0, -1}, // 28 leviathan - it has a syncronized attack/sound pattern, so don't schedule
};

const char creature_name[29][16] = {
    "dragon",        // 0
    "goat",          // 1
    "bee",           // 2
    "worm",          // 3
    "archer",        // 4
    "unknown",       // 5
    "unknown",       // 6
    "unknown",       // 7
    "unknown",       // 8
    "skeleton",      // 9
    "vissuluth",     // 10
    "unknown",       // 11
    "builder",       // 12
    "townie",        // 13
    "trader",        // 14
    "castle archer", // 15
    "wyvern",        // 16
    "manticore",     // 17
    "sentinel",      // 18
    "firefly",       // 19
    "spider",        // 20
    "devil",         // 21
    "mana worm",     // 22
    "moon dweller",  // 23
    "troglodyte",    // 24
    "cymmerian",     // 25
    "zombie",       // 26
    "hydra",         // 27
    "leviathan",     // 28
};



#endif
