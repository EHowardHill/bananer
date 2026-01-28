#ifndef BN_SPRITE_TILES_ITEM_H
#define BN_SPRITE_TILES_ITEM_H

namespace bn
{
    class sprite_item;

    class sprite_tiles_item
    {
    private:
        const sprite_item *_item_ref;

    public:
        constexpr sprite_tiles_item(const sprite_item &item) : _item_ref(&item) {}

        // Accessor to get back to the main item
        constexpr const sprite_item &item() const { return *_item_ref; }
    };
}

#endif