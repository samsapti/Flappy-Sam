#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

int points;
float v = 0;
bool holdKey = false;
bool playAgain = true;
bool gameOver = false;


int main()
{

    while (playAgain) {

        points = 0;

        // Here the window is created with the title "Flappy Sam"
        RenderWindow window(VideoMode(400, 650 ), "Flappy Sam");


        // Here the timer is set, framerate is now locked at 60fps
        Clock clock;
        window.setFramerateLimit(60);

        // Here the background is defined
        RectangleShape background(Vector2f(400, 650));
        background.setFillColor(Color(97, 166, 255));


        /************ TEXTURES ***********/

        // Ground
        Texture texture_ground;

        if (!texture_ground.loadFromFile("img/ground.png")) {

            cout << "Error loading ground.png" << endl;

        }

        // Sam
        Texture texture_sam;

        if (!texture_sam.loadFromFile("img/8bit-sam.png")) {

            cout << "Error loading 8bit-sam.png :(" << endl;

        }

        // Small lower pipe
        Texture texture_pipe_small_down;

        if (!texture_pipe_small_down.loadFromFile("img/small_pipe_down.png")) {

            cout << "Error loading small_pipe_down.png :(" << endl;

        }

        // Big lower pipe
        Texture texture_pipe_big_down;

        if (!texture_pipe_big_down.loadFromFile("img/big_pipe_down.png")) {

            cout << "Error loading big_pipe_down.png :(" << endl;

        }

        // Small upper pipe
        Texture texture_pipe_small_up;

        if (!texture_pipe_small_up.loadFromFile("img/small_pipe_up.png")) {

            cout << "Error loading small_pipe_up.png :(" << endl;

        }

        // Big upper pipe
        Texture texture_pipe_big_up;

        if (!texture_pipe_big_up.loadFromFile("img/big_pipe_up.png")) {

            cout << "Error loading big_pipe_up.png :(" << endl;

        }


        /************* SOUNDS ************/

        // Beep sound
        SoundBuffer beep;

        if (!beep.loadFromFile("sounds/beep.flac")) {

            cout << "Error loading beep.flac :(" << endl;

        }

        Sound beeps;
        beeps.setBuffer(beep);

        // Jump sound
        SoundBuffer jump;

        if (!jump.loadFromFile("sounds/jump.flac")) {

            cout << "Error loading beep.flac :(" << endl;

        }

        Sound jumps;
        jumps.setBuffer(jump);


        /************ OBJECTS ************/

        // Ground object
        Sprite sprite_ground;
        sprite_ground.setTexture(texture_ground);

        // Ground gets placed
        sprite_ground.setPosition(Vector2f(0, 610));

        // Sam object
        Sprite sprite_sam;
        sprite_sam.setTexture(texture_sam);

        // Sam gets placed
        sprite_sam.setPosition(Vector2f(70, 100));

        // Pipe objects
        Sprite sprite_pipe_small_down;
        sprite_pipe_small_down.setTexture(texture_pipe_small_down);

        Sprite sprite_pipe_big_down;
        sprite_pipe_big_down.setTexture(texture_pipe_big_down);

        Sprite sprite_pipe_small_up;
        sprite_pipe_small_up.setTexture(texture_pipe_small_up);

        Sprite sprite_pipe_big_up;
        sprite_pipe_big_up.setTexture(texture_pipe_big_up);

        // Pipes get placed
        sprite_pipe_small_down.setPosition(Vector2f(450, 477));
        sprite_pipe_big_down.setPosition(Vector2f(700, 423));
        sprite_pipe_small_up.setPosition(Vector2f(700, 0));
        sprite_pipe_big_up.setPosition(Vector2f(450, 0));


        /************ THE GAME ***********/

        // This makes sure the window is active and that it can be moved and closed manually
		while (window.isOpen()) {

			//This starts our event, which is what happens in the window
			Event event;

			if (!gameOver) {

				// This makes the pipes move at a constant speed:
				sprite_pipe_small_down.move(Vector2f(-2, 0));
				sprite_pipe_big_down.move(Vector2f(-2, 0));
				sprite_pipe_small_up.move(Vector2f(-2, 0));
				sprite_pipe_big_up.move(Vector2f(-2, 0));

				if (sprite_pipe_small_down.getPosition().x == -50 && sprite_pipe_big_up.getPosition().x == -50) {

				   sprite_pipe_small_down.move(Vector2f(500, 0));
				   sprite_pipe_big_up.move(Vector2f(500, 0));

				} else if (sprite_pipe_big_down.getPosition().x == -50 && sprite_pipe_small_up.getPosition().x == -50) {

				   sprite_pipe_big_down.move(Vector2f(500, 0));
				   sprite_pipe_small_up.move(Vector2f(500, 0));

				}

				// This makes sure the window stays open and can be closed manually when the event is over
				while (window.pollEvent(event)) {

				   if (event.type == Event::Closed) {

					   window.close();

				   }

				}

				// Here Sam's movement loop is configured
				if (Keyboard::isKeyPressed(Keyboard::Space) && !holdKey) {

				   jumps.play();
				   v = -13;

				   // This will make sure that the space key isn't held, otherwise Sam will stand still
				   holdKey = true;

				} else {

				   v = v + 0.8;

				   if (v > 9.0) {

					   v = 9.0;

				   }

				   sprite_sam.move(Vector2f(0, v));

				}

				// If the space key isn't pressed/held, allow another jump
				if (!Keyboard::isKeyPressed(Keyboard::Space) && holdKey) {

				   holdKey = false;

				}

				//Here are the collision functions
				if (sprite_sam.getGlobalBounds().intersects(sprite_ground.getGlobalBounds())) {

				   gameOver = true;

				} else if (sprite_sam.getGlobalBounds().intersects(sprite_pipe_small_down.getGlobalBounds()) || sprite_sam.getGlobalBounds().intersects(sprite_pipe_big_down.getGlobalBounds())) {

				   gameOver = true;

				} else if (sprite_sam.getGlobalBounds().intersects(sprite_pipe_small_up.getGlobalBounds()) || sprite_sam.getGlobalBounds().intersects(sprite_pipe_big_up.getGlobalBounds())) {

				   gameOver = true;

				} else {

				   if (sprite_sam.getPosition().x + 60 == sprite_pipe_small_down.getPosition().x || sprite_sam.getPosition().x + 60 == sprite_pipe_big_down.getPosition().x) {

					   beeps.play();
					   points += 1;

				   }

				}

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

				/********* GAME OVER MENU ********/

				Font font;
				Text text_GameOver;
				Text text_score;
				Text text_PlayAgain;

				// Load font from file
				if (!font.loadFromFile("fonts/Fipps-Regular.otf"))
				{

					cout << "Error loading Fipps-Regular.otf :(" << endl;

				}

				// Set font
				text_GameOver.setFont(font);
				text_score.setFont(font);
				text_PlayAgain.setFont(font);

				// Set strings
				if (points == 1) {

                    text_score.setString("You scored 1 point.");

				} else {

                    text_score.setString("You scored " + to_string(points) + " points.");

				}

				text_GameOver.setString("GAME OVER");
				text_PlayAgain.setString("Play again? (Y/N)");

				// Character size in pixels and colors
				text_GameOver.setCharacterSize(42);
				text_GameOver.setFillColor(Color::Red);
				text_score.setCharacterSize(16);
				text_score.setFillColor(Color::Yellow);
				text_PlayAgain.setCharacterSize(16);
				text_PlayAgain.setFillColor(Color::Yellow);

				// Text positions
				text_GameOver.setPosition(20, 250);
				text_score.setPosition(60, 320);
				text_PlayAgain.setPosition(60, 350);

				// Display texts
				window.clear();
				window.draw(background);
				window.draw(sprite_ground);
				window.draw(text_GameOver);
				window.draw(text_score);
				window.draw(text_PlayAgain);
				window.display();

				if (Keyboard::isKeyPressed(Keyboard::Y)) {

					gameOver = false;
					break;

				} else if (Keyboard::isKeyPressed(Keyboard::N)) {

					playAgain = false;
					break;

				}

			}

	    }

	}

    return 0;

}
