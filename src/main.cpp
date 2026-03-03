#include <bn_core.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_random.h>
#include <bn_sprite_text_generator.h>

#include "Player.h"
#include "Enemy.h"
#include "Car.h"
#include "ScoreDisplay.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {16,16};
static constexpr bn::size ENEMY_SIZE = {8, 8};
static constexpr bn::size CAR_SIZE = {16, 8};

// Car & Enemy vector variables
static constexpr int MAX_ENEMIES = 4; // Max number of enemies
static constexpr int MAX_CARS = 2;
static bn::random rng = bn::random();

int main()
{
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Enemy vector
    bn::vector<Enemy, MAX_ENEMIES> enemies = {}; // Start with empty vector for enemies

    // Car vector
    bn::vector<Car, MAX_CARS> cars = {}; // Start with empty vector for cars

    // Initialize enemies
    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player(-19, 22, 2.0, PLAYER_SIZE);

    // Create two cars at the top and bottom of the screen, always starting at random X variables
    cars.push_back(Car(rng.get_int(-40, 40), MAX_Y, 1.0, CAR_SIZE));
    cars.push_back(Car(rng.get_int(-40, 40), MIN_Y, 1.0, CAR_SIZE));
    // Create enemies
    enemies.push_back(Enemy(30, -12, 1.0, ENEMY_SIZE));

    // FRAME COUNTER
    int current_frame = 0;

    while (true)
    {
        int rng_x = rng.get_int(-40, 40); // Random x position enemy
        int rng_y = rng.get_int(-30, 30); // Random y position enemy
        current_frame++;
        // Every 4 seconds - add a new enemy with random position
        if(current_frame % 240 == 0 && enemies.size() < MAX_ENEMIES)
        {
            current_frame = 0; // Reset frame counter after spawning an enemy

            enemies.push_back(Enemy(rng_x, rng_y, 1.0, ENEMY_SIZE)); // Add a new enemy with random position
        }
        player.update();

        if (current_frame % 240 == 0 && enemies.size() < MAX_ENEMIES)
        {
            current_frame = 0; // Reset frame counter after spawning an enemy
            // Spawn a new enemy every 240 frames (4 seconds at 60 fps)
            enemies.push_back(Enemy(rng_x, rng_y, 1.0, ENEMY_SIZE)); // Add a new enemy with random position
        }
        // for loop to update each car
        for (Car &car : cars)
        {
            car.update();
            // Reset the current score and player position if the player collides with car
            if (car.bounding_box.intersects(player.bounding_box))
            { // -- refers to car class
                scoreDisplay.resetScore();
                player.sprite.set_x(-19);
                player.sprite.set_y(22); // Random x position for car
            }
        }
        // for loop to update each enemy
        for (Enemy &enemy : enemies)
        {
            enemy.update(player);
            // Reset the current score and player position if the player collides with enemy
            if (enemy.bounding_box.intersects(player.bounding_box))
            { // -- refers to enemy class
                scoreDisplay.resetScore();
                player.sprite.set_x(-19);
                player.sprite.set_y(22);
                enemy.sprite.set_x(rng_x);
                enemy.sprite.set_y(rng_y);

                if(enemies.size() > 1)
                {
                    enemies.erase(enemies.begin() + 1, enemies.end());
                }
            }
        }

        // Update the scores and display them
        scoreDisplay.update();

        bn::core::update();
    }
}