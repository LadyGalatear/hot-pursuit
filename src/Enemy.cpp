#include "Enemy.h"

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
static bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size)
{
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

Enemy::Enemy(int starting_x, int starting_y, bn::fixed enemy_speed, bn::size enemy_size) :
        sprite(bn::sprite_items::wingra.create_sprite(starting_x, starting_y)),
        speed(enemy_speed),
        size(enemy_size),
        bounding_box(create_bounding_box(sprite, size))
    {
    }

void Enemy::update(Player &player)
{
    // Move enemy towards player, if statements compare each x and y position.
    if (sprite.x() < player.sprite.x())
    {
        sprite.set_x(sprite.x() + speed);
        sprite.set_horizontal_flip(false);
    }
    if (sprite.x() > player.sprite.x())
    {
        sprite.set_x(sprite.x() - speed);
        sprite.set_horizontal_flip(true);
    }
    if (sprite.y() < player.sprite.y())
    {
        sprite.set_y(sprite.y() + speed);
    }
    if (sprite.y() > player.sprite.y())
    {
        sprite.set_y(sprite.y() - speed);
    }

    bounding_box = create_bounding_box(sprite, size);
}