#ifndef BN_SOUND_ITEMS_INFO_H
#define BN_SOUND_ITEMS_INFO_H

#include "bn_span.h"
#include "bn_sound_item.h"
#include "bn_string_view.h"
#include "bn_sound_items.h"

namespace bn::sound_items_info
{
    struct pair { sound_item item; string_view name; };

    constexpr inline pair array[] = {
        { sound_items::drone, "drone" },
        { sound_items::sfx_boom, "sfx_boom" },
        { sound_items::sfx_bottle, "sfx_bottle" },
        { sound_items::sfx_click, "sfx_click" },
        { sound_items::sfx_damage, "sfx_damage" },
        { sound_items::sfx_door, "sfx_door" },
        { sound_items::sfx_drag, "sfx_drag" },
        { sound_items::sfx_fall, "sfx_fall" },
        { sound_items::sfx_fire, "sfx_fire" },
        { sound_items::sfx_knock, "sfx_knock" },
        { sound_items::sfx_roar, "sfx_roar" },
        { sound_items::sfx_wack_his_pipis, "sfx_wack_his_pipis" },
        { sound_items::snd_alert, "snd_alert" },
        { sound_items::snd_chime, "snd_chime" },
        { sound_items::snd_cnaut, "snd_cnaut" },
        { sound_items::snd_dialogue_berdly, "snd_dialogue_berdly" },
        { sound_items::snd_dialogue_death, "snd_dialogue_death" },
        { sound_items::snd_dialogue_generic, "snd_dialogue_generic" },
        { sound_items::snd_dialogue_greyfriar, "snd_dialogue_greyfriar" },
        { sound_items::snd_dialogue_kiara, "snd_dialogue_kiara" },
        { sound_items::snd_dialogue_lancer, "snd_dialogue_lancer" },
        { sound_items::snd_dialogue_matt, "snd_dialogue_matt" },
        { sound_items::snd_dialogue_mcwebb, "snd_dialogue_mcwebb" },
        { sound_items::snd_dialogue_noelle, "snd_dialogue_noelle" },
        { sound_items::snd_dialogue_ralsei, "snd_dialogue_ralsei" },
        { sound_items::snd_dialogue_sans, "snd_dialogue_sans" },
        { sound_items::snd_dialogue_sebellus, "snd_dialogue_sebellus" },
        { sound_items::snd_dialogue_susie, "snd_dialogue_susie" },
        { sound_items::snd_dialogue_temmie, "snd_dialogue_temmie" },
        { sound_items::snd_dialogue_togore, "snd_dialogue_togore" },
        { sound_items::snd_dialogue_typewriter, "snd_dialogue_typewriter" },
        { sound_items::snd_dialogue_visker, "snd_dialogue_visker" },
        { sound_items::snd_dialogue_visker_wife, "snd_dialogue_visker_wife" },
        { sound_items::snd_dialogue_vista, "snd_dialogue_vista" },
        { sound_items::snd_explosion, "snd_explosion" },
        { sound_items::snd_fight_start, "snd_fight_start" },
        { sound_items::snd_hit, "snd_hit" },
        { sound_items::snd_intro, "snd_intro" },
        { sound_items::snd_miss, "snd_miss" },
        { sound_items::snd_select, "snd_select" },
    };

    constexpr inline span<const pair> span(array);
}

#endif