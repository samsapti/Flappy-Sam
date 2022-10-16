#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

bool intersects(Sprite *a, Sprite *b)
{
    return a->getGlobalBounds().intersects(b->getGlobalBounds());
}

int main()
{
    // Declare variables
    bool game_over;
    bool hold_space;
    int points;
    float v;

    Texture texture_ground;
    Texture texture_sam;
    Texture texture_pipe_small_down;
    Texture texture_pipe_big_down;
    Texture texture_pipe_small_up;
    Texture texture_pipe_big_up;
    
    Sprite sprite_ground;
    Sprite sprite_sam;
    Sprite sprite_pipe_small_down;
    Sprite sprite_pipe_big_down;
    Sprite sprite_pipe_small_up;
    Sprite sprite_pipe_big_up;

    SoundBuffer beep_buffer;
    SoundBuffer jump_buffer;
    Sound beep_sound;
    Sound jump_sound;

    // Initialize window
    RenderWindow window(VideoMode(400, 650), "Flappy Sam");
    RectangleShape background(Vector2f(400, 650));
    window.setFramerateLimit(60);
    background.setFillColor(Color(97, 166, 255));

    // Configure textures
    if (!texture_ground.loadFromFile("img/ground.png"))
        cout << "Error loading ground.png" << endl;
    if (!texture_sam.loadFromFile("img/8bit_sam.png"))
        cout << "Error loading 8bit_sam.png :(" << endl;
    if (!texture_pipe_small_down.loadFromFile("img/small_pipe_down.png"))
        cout << "Error loading small_pipe_down.png :(" << endl;
    if (!texture_pipe_big_down.loadFromFile("img/big_pipe_down.png"))
        cout << "Error loading big_pipe_down.png :(" << endl;
    if (!texture_pipe_small_up.loadFromFile("img/small_pipe_up.png"))
        cout << "Error loading small_pipe_up.png :(" << endl;
    if (!texture_pipe_big_up.loadFromFile("img/big_pipe_up.png"))
        cout << "Error loading big_pipe_up.png :(" << endl;

    // Configure objects
    sprite_ground.setTexture(texture_ground);
    sprite_sam.setTexture(texture_sam);
    sprite_pipe_small_down.setTexture(texture_pipe_small_down);
    sprite_pipe_big_down.setTexture(texture_pipe_big_down);
    sprite_pipe_small_up.setTexture(texture_pipe_small_up);
    sprite_pipe_big_up.setTexture(texture_pipe_big_up);

    // Configure sounds
    if (!beep_buffer.loadFromFile("sounds/beep.flac"))
        cout << "Error loading beep.flac :(" << endl;
    if (!jump_buffer.loadFromFile("sounds/jump.flac"))
        cout << "Error loading beep.flac :(" << endl;
    
    beep_sound.setBuffer(beep_buffer);
    jump_sound.setBuffer(jump_buffer);

start:
    // Initialize/reset variables
    game_over = false;
    hold_space = false;
    points = 0;
    v = 0.0f;
    
    // Set objects in position
    sprite_sam.setPosition(Vector2f(70, 100));
    sprite_ground.setPosition(Vector2f(0, 610));
    sprite_pipe_small_down.setPosition(Vector2f(450, 477));
    sprite_pipe_big_down.setPosition(Vector2f(700, 423));
    sprite_pipe_small_up.setPosition(Vector2f(700, 0));
    sprite_pipe_big_up.setPosition(Vector2f(450, 0));

    // Main game loop
    while (window.isOpen()) {
        Event event;

        if (!game_over) {
            // This makes the pipes move at a constant speed
            sprite_pipe_small_down.move(Vector2f(-2, 0));
            sprite_pipe_big_down.move(Vector2f(-2, 0));
            sprite_pipe_small_up.move(Vector2f(-2, 0));
            sprite_pipe_big_up.move(Vector2f(-2, 0));

            // Move the pipes back to start when they exit the view
            if (sprite_pipe_big_up.getPosition().x == -50) {
               sprite_pipe_big_up.move(Vector2f(500, 0));
               sprite_pipe_small_down.move(Vector2f(500, 0));
            } else if (sprite_pipe_small_up.getPosition().x == -50) {
               sprite_pipe_small_up.move(Vector2f(500, 0));
               sprite_pipe_big_down.move(Vector2f(500, 0));
            }

            // Respond to events
            while (window.pollEvent(event)) {
               if (event.type == Event::Closed) return 0;
            }

            // Movement loop
            if (Keyboard::isKeyPressed(Keyboard::Space) && !hold_space) {
                v = -14.0f;  // Y-coordinates are reversed, up is lower
                hold_space = true;  // to make sure Sam won't stand still if space key is held
                jump_sound.play();
                sprite_sam.move(Vector2f(0.0f, v));
            } else {
                v = v + 1.0f;
                if (v > 10.0f) v = 10.0f;
                if (!Keyboard::isKeyPressed(Keyboard::Space)) hold_space = false;
                sprite_sam.move(Vector2f(0.0f, v));
            }

            // Collision/point checks
            if (intersects(&sprite_sam, &sprite_ground)) {
                game_over = true;
            } else if (intersects(&sprite_sam, &sprite_pipe_small_down) || intersects(&sprite_sam, &sprite_pipe_big_down)) {
                game_over = true;
            } else if (intersects(&sprite_sam, &sprite_pipe_small_up) || intersects(&sprite_sam, &sprite_pipe_big_up)) {
                game_over = true;
            } else if (sprite_pipe_small_up.getPosition().x == sprite_sam.getPosition().x + 60 || sprite_pipe_big_up.getPosition().x == sprite_sam.getPosition().x + 60) {
                beep_sound.play();
                points++;
            }

            // Redraw window
            window.clear();
            window.draw(background);
            window.draw(sprite_ground);
            window.draw(sprite_sam);
            window.draw(sprite_pipe_small_down);
            window.draw(sprite_pipe_big_down);
            window.draw(sprite_pipe_small_up);
            window.draw(sprite_pipe_big_up);
            window.display();
        } else {
            // Configure font
            Font font;
            Text text_GameOver;
            Text text_PlayAgain;
            Text text_score;

            if (!font.loadFromFile("fonts/Fipps-Regular.otf"))
                cout << "Error loading Fipps-Regular.otf :(" << endl;

            // Configure text strings
            text_GameOver.setFont(font);
            text_PlayAgain.setFont(font);
            text_score.setFont(font);

            text_GameOver.setString("GAME OVER");
            text_PlayAgain.setString("Play again? (Y/N)");
            text_score.setString("You scored " + to_string(points) + " point" + (points == 1 ? "." : "s."));

            text_GameOver.setCharacterSize(42);
            text_PlayAgain.setCharacterSize(16);
            text_score.setCharacterSize(16);

            text_GameOver.setFillColor(Color::Red);
            text_PlayAgain.setFillColor(Color::Yellow);
            text_score.setFillColor(Color::Yellow);

            text_GameOver.setPosition(20, 250);
            text_PlayAgain.setPosition(60, 350);
            text_score.setPosition(60, 320);

            // Redraw window
            window.clear();
            window.draw(background);
            window.draw(sprite_ground);
            window.draw(text_GameOver);
            window.draw(text_score);
            window.draw(text_PlayAgain);
            window.display();

            // Handle user action
            if (Keyboard::isKeyPressed(Keyboard::Y)) {
                game_over = false;
                goto start;
            } else if (Keyboard::isKeyPressed(Keyboard::N)) {
                break;
            }
        }
    }

    return 0;
}
