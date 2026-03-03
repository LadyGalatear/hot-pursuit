#ifndef ENEMY_H
#define ENEMY_H

#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>

#include "Player.h"
#include "bn_sprite_items_wingra.h"

class Enemy
{
public:
    Enemy(int starting_x, int starting_y, bn::fixed enemy_speed, bn::size enemy_size);

    // LOGIC: Setting position for enemy. Does not currently move, yet.
    void update(Player &player);

    // Create the sprite. This will be moved to a constructor
    bn::sprite_ptr sprite; // Sprite pointer
    bn::fixed speed;       // The speed of the enemy
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision
};

#endif