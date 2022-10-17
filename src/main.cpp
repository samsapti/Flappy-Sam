#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

bool intersects(sf::Sprite *a, sf::Sprite *b)
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

    sf::Texture texture_ground;
    sf::Texture texture_sam;
    sf::Texture texture_pipe_small_down;
    sf::Texture texture_pipe_big_down;
    sf::Texture texture_pipe_small_up;
    sf::Texture texture_pipe_big_up;
    sf::Sprite sprite_ground;
    sf::Sprite sprite_sam;
    sf::Sprite sprite_pipe_small_down;
    sf::Sprite sprite_pipe_big_down;
    sf::Sprite sprite_pipe_small_up;
    sf::Sprite sprite_pipe_big_up;
    sf::SoundBuffer beep_buffer;
    sf::SoundBuffer jump_buffer;
    sf::Sound beep_sound;
    sf::Sound jump_sound;

    // Initialize window
    sf::RenderWindow window(sf::VideoMode(400, 650), "Flappy Sam");
    sf::RectangleShape background(sf::Vector2f(400, 650));
    window.setFramerateLimit(60);
    background.setFillColor(sf::Color(97, 166, 255));

    // Configure textures
    if (!texture_ground.loadFromFile("img/ground.png"))
        std::cout << "Error loading ground.png" << std::endl;
    if (!texture_sam.loadFromFile("img/8bit_sam.png"))
        std::cout << "Error loading 8bit_sam.png :(" << std::endl;
    if (!texture_pipe_small_down.loadFromFile("img/small_pipe_down.png"))
        std::cout << "Error loading small_pipe_down.png :(" << std::endl;
    if (!texture_pipe_big_down.loadFromFile("img/big_pipe_down.png"))
        std::cout << "Error loading big_pipe_down.png :(" << std::endl;
    if (!texture_pipe_small_up.loadFromFile("img/small_pipe_up.png"))
        std::cout << "Error loading small_pipe_up.png :(" << std::endl;
    if (!texture_pipe_big_up.loadFromFile("img/big_pipe_up.png"))
        std::cout << "Error loading big_pipe_up.png :(" << std::endl;

    // Configure objects
    sprite_ground.setTexture(texture_ground);
    sprite_sam.setTexture(texture_sam);
    sprite_pipe_small_down.setTexture(texture_pipe_small_down);
    sprite_pipe_big_down.setTexture(texture_pipe_big_down);
    sprite_pipe_small_up.setTexture(texture_pipe_small_up);
    sprite_pipe_big_up.setTexture(texture_pipe_big_up);

    // Configure sounds
    if (!beep_buffer.loadFromFile("sounds/beep.flac"))
        std::cout << "Error loading beep.flac :(" << std::endl;
    if (!jump_buffer.loadFromFile("sounds/jump.flac"))
        std::cout << "Error loading beep.flac :(" << std::endl;
    
    beep_sound.setBuffer(beep_buffer);
    jump_sound.setBuffer(jump_buffer);

start:
    // Initialize/reset variables
    game_over = false;
    hold_space = false;
    points = 0;
    v = 0.0f;
    
    // Set objects in position
    sprite_sam.setPosition(sf::Vector2f(70, 100));
    sprite_ground.setPosition(sf::Vector2f(0, 610));
    sprite_pipe_small_down.setPosition(sf::Vector2f(450, 477));
    sprite_pipe_big_down.setPosition(sf::Vector2f(700, 423));
    sprite_pipe_small_up.setPosition(sf::Vector2f(700, 0));
    sprite_pipe_big_up.setPosition(sf::Vector2f(450, 0));

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;

        if (!game_over) {
            // This makes the pipes move at a constant speed
            sprite_pipe_small_down.move(sf::Vector2f(-2, 0));
            sprite_pipe_big_down.move(sf::Vector2f(-2, 0));
            sprite_pipe_small_up.move(sf::Vector2f(-2, 0));
            sprite_pipe_big_up.move(sf::Vector2f(-2, 0));

            // Move the pipes back to start when they exit the view
            if (sprite_pipe_big_up.getPosition().x == -50) {
               sprite_pipe_big_up.move(sf::Vector2f(500, 0));
               sprite_pipe_small_down.move(sf::Vector2f(500, 0));
            } else if (sprite_pipe_small_up.getPosition().x == -50) {
               sprite_pipe_small_up.move(sf::Vector2f(500, 0));
               sprite_pipe_big_down.move(sf::Vector2f(500, 0));
            }

            // Respond to events
            while (window.pollEvent(event)) {
               if (event.type == sf::Event::Closed) return 0;
            }

            // Movement loop
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !hold_space) {
                v = -14.0f;  // Y-coordinates are reversed, up is lower
                hold_space = true;  // to make sure Sam won't stand still if space key is held
                jump_sound.play();
                sprite_sam.move(sf::Vector2f(0.0f, v));
            } else {
                v = v + 1.0f;
                if (v > 10.0f) v = 10.0f;
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) hold_space = false;
                sprite_sam.move(sf::Vector2f(0.0f, v));
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
            sf::Font font;
            sf::Text text_GameOver;
            sf::Text text_PlayAgain;
            sf::Text text_score;

            if (!font.loadFromFile("fonts/Fipps-Regular.otf"))
                std::cout << "Error loading Fipps-Regular.otf :(" << std::endl;

            // Configure text strings
            text_GameOver.setFont(font);
            text_PlayAgain.setFont(font);
            text_score.setFont(font);

            text_GameOver.setString("GAME OVER");
            text_PlayAgain.setString("Play again? (Y/N)");
            text_score.setString("You scored " + std::to_string(points) + " point" + (points == 1 ? "." : "s."));

            text_GameOver.setCharacterSize(42);
            text_PlayAgain.setCharacterSize(16);
            text_score.setCharacterSize(16);

            text_GameOver.setFillColor(sf::Color::Red);
            text_PlayAgain.setFillColor(sf::Color::Yellow);
            text_score.setFillColor(sf::Color::Yellow);

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                game_over = false;
                goto start;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                break;
            }
        }
    }

    return 0;
}
