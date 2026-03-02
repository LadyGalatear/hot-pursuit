#ifndef CAR_H
#define CAR_H

#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>

#include "Player.h"
#include "bn_sprite_items_car.h"

class Car
{
public:
    Car(int starting_x, int starting_y, bn::fixed car_speed, bn::size car_size);

    void update();

    // Create the sprite. This will be moved to a constructor
    bn::sprite_ptr sprite; // Sprite pointer
    bn::fixed speed;       // The speed of the car
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision
};

#endif