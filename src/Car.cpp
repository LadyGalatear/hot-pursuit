#include "Car.h"

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

Car::Car(int starting_x,int starting_y, bn::fixed car_speed, bn::size car_size) :
        sprite(bn::sprite_items::car.create_sprite(starting_x, starting_y)),
        speed(car_speed),
        size(car_size),
        bounding_box(create_bounding_box(sprite, size))
    {
    }
void Car::update()
{


    bounding_box = create_bounding_box(sprite, size);
}