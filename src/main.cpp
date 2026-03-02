#include <bn_core.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>

#include "Player.h"
#include "Enemy.h"
#include "ScoreDisplay.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

int main()
{
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    //Enemy vector
    bn::vector<bn::sprite_ptr, 2> enemy_sprites; // Sprites to display enemies
    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player(-19, 22, 2.0, PLAYER_SIZE);
    Enemy enemy = Enemy(30, -12, 1.3, ENEMY_SIZE); // Enemy object from Enemy class

    while (true)
    {
        player.update();
        enemy.update(player);

        // Reset the current score and player position if the player collides with enemy
        if (enemy.bounding_box.intersects(player.bounding_box))
        { // -- refers to enemy class
            scoreDisplay.resetScore();
            player.sprite.set_x(-19);
            player.sprite.set_y(22);
            enemy.sprite.set_x(30);
            enemy.sprite.set_y(-12);
        }

        // Update the scores and display them
        scoreDisplay.update();

        bn::core::update();
    }
}