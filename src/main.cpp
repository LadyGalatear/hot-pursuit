#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"
#include "Player.h"
#include "Enemy.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

// Number of characters required to show two of the longest numer possible in an int (-2147483647)
static constexpr int MAX_SCORE_CHARS = 22;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// High score location
static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;

/**
 * Displays a score and high score.
 *
 * Score starts a 0 and is increased each time update is called, and reset to 0 when resetScore is
 * called. High score tracks the highest score ever reached.
 */
class ScoreDisplay
{
public:
    ScoreDisplay() : score(0),                                                                 // Start score at 0
                     high_score(0),                                                            // Start high score at 0
                     score_sprites(bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS>()),             // Start with empty vector for score sprites
                     text_generator(bn::sprite_text_generator(common::fixed_8x16_sprite_font)) // Use a new text generator
    {
    }

    /**
     * Increases score by 1 and updates high score if needed. Displays score and high score.
     */
    void update()
    {
        // increase score and update high score if this is the new highest
        score++;
        if (score > high_score)
        {
            high_score = score;
        }

        // Stop displaying previous scores
        score_sprites.clear();

        // Display new scores
        show_number(SCORE_X, SCORE_Y, score);
        show_number(HIGH_SCORE_X, HIGH_SCORE_Y, high_score);
    }

    /**
     * Displays a number at the given position
     */
    void show_number(int x, int y, int number)
    {
        // Convert number to a string and then display it
        bn::string<MAX_SCORE_CHARS> number_string = bn::to_string<MAX_SCORE_CHARS>(number);
        text_generator.generate(x, y, number_string, score_sprites);
    }

    /**
     * Sets score back to 0. Does NOT reset high score.
     */
    void resetScore()
    {
        score = 0;
    }

    int score;                                                 // current score
    int high_score;                                            // best core
    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites; // Sprites to display scores
    bn::sprite_text_generator text_generator;                  // Text generator for scores
};

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