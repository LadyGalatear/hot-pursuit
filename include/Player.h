#ifndef PLAYER_H
#define PLAYER_H

#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_kaiju.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

class Player
{
public:
    Player(int starting_x, int starting_y, bn::fixed player_speed, bn::size player_size);

    /**
     * Update the position and bounding box of the player based on d-pad movement.
     */
    void update();

    // Create the sprite. This will be moved to a constructor
    bn::sprite_ptr sprite; // Sprite pointer
    bn::fixed speed;       // The speed of the player
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision
};

#endif