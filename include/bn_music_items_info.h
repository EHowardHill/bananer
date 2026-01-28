#ifndef BN_MUSIC_ITEMS_INFO_H
#define BN_MUSIC_ITEMS_INFO_H

#include "bn_span.h"
#include "bn_music_item.h"
#include "bn_string_view.h"
#include "bn_music_items.h"

namespace bn::music_items_info
{
    struct pair { music_item item; string_view name; };

    constexpr inline pair array[] = {
        { music_items::ambient_birds, "ambient_birds" },
        { music_items::ambient_heartbeat, "ambient_heartbeat" },
        { music_items::ambient_wind, "ambient_wind" },
        { music_items::bg_avalon, "bg_avalon" },
        { music_items::bg_canter_02, "bg_canter_02" },
        { music_items::bg_channel, "bg_channel" },
        { music_items::bg_dixieland, "bg_dixieland" },
        { music_items::bg_flayithro, "bg_flayithro" },
        { music_items::bg_friend, "bg_friend" },
        { music_items::bg_garbage, "bg_garbage" },
        { music_items::bg_hotel, "bg_hotel" },
        { music_items::bg_paschal, "bg_paschal" },
        { music_items::bg_sorry, "bg_sorry" },
        { music_items::bg_sorry_train, "bg_sorry_train" },
        { music_items::bg_spamton, "bg_spamton" },
        { music_items::boss, "boss" },
        { music_items::cave_01, "cave_01" },
        { music_items::forest_01, "forest_01" },
        { music_items::intro, "intro" },
        { music_items::intro_02, "intro_02" },
        { music_items::intro_guitar, "intro_guitar" },
        { music_items::shop, "shop" },
        { music_items::theme_anata, "theme_anata" },
        { music_items::theme_ginger, "theme_ginger" },
        { music_items::theme_sans, "theme_sans" },
        { music_items::theme_visker, "theme_visker" },
        { music_items::z02_the_champ, "z02_the_champ" },
    };

    constexpr inline span<const pair> span(array);
}

#endif
