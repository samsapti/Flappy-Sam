#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace sf;

int p = 1;
float v = 0;
bool holdKey = false;

int main()
{

    // Here the window is created with the title "Flappy Sam"
    RenderWindow window(VideoMode(400, 650 ), "Flappy Sam" );

    // Here the background is defined
    RectangleShape background(Vector2f(400, 650));
    background.setFillColor(Color(97, 166, 255));


    // Here the textures are defined

    //Ground
    Texture texture_ground;

    if (!texture_ground.loadFromFile("ground.png")) {

        cout << "Error loading ground.png" << endl;

    }

    //Sam
    Texture texture_sam;

    if (!texture_sam.loadFromFile("8bit-sam.png")) {

    cout << "Error loading 8bit-sam.png :(" << endl;

    }

    //Small lower pipe
    Texture texture_pipe_small_down;

    if (!texture_pipe_small_down.loadFromFile("small_pipe_down.png")) {

        cout << "Error loading small_pipe_down.png :(" << endl;

    }

    //Big lower pipe
    Texture texture_pipe_big_down;

    if (!texture_pipe_big_down.loadFromFile("big_pipe_down.png")) {

        cout << "Error loading big_pipe_down.png :(" << endl;

    }

    //Small upper pipe
    Texture texture_pipe_small_up;

    if (!texture_pipe_small_up.loadFromFile("small_pipe_up.png")) {

        cout << "Error loading small_pipe_up.png :(" << endl;

    }

    //Big upper pipe
    Texture texture_pipe_big_up;

    if (!texture_pipe_big_up.loadFromFile("big_pipe_up.png")) {

        cout << "Error loading big_pipe_up.png :(" << endl;

    }


    /************OBJECTS************/

    //Here the object ground is created
    Sprite sprite_ground;
    sprite_ground.setTexture(texture_ground);

    //Here it is placed
    sprite_ground.setPosition(Vector2f(0, 610));

    // Here the object Sam is created
    Sprite sprite_sam;
    sprite_sam.setTexture(texture_sam);

    // Here he is placed in the middle
    sprite_sam.setPosition(Vector2f(75, 100));

    //Here the pipe objects are created
    Sprite sprite_pipe_small_down;
    sprite_pipe_small_down.setTexture(texture_pipe_small_down);

    Sprite sprite_pipe_big_down;
    sprite_pipe_big_down.setTexture(texture_pipe_big_down);

    Sprite sprite_pipe_small_up;
    sprite_pipe_small_up.setTexture(texture_pipe_small_up);

    Sprite sprite_pipe_big_up;
    sprite_pipe_big_up.setTexture(texture_pipe_big_up);

    //Here they are placed in the map
    sprite_pipe_small_down.setPosition(Vector2f(450, 477));
    sprite_pipe_big_down.setPosition(Vector2f(700, 423));
    sprite_pipe_small_up.setPosition(Vector2f(700, 0));
    sprite_pipe_big_up.setPosition(Vector2f(450, 0));

    // !!POSITION TEST!!
    cout << "x-position: " << sprite_sam.getPosition().x << endl;

    // This makes sure the window is active and that it can be moved and closed manually
    while (window.isOpen()) {

        Event event;

        sprite_pipe_small_down.move(Vector2f(-0.07, 0));
        sprite_pipe_big_down.move(Vector2f(-0.07, 0));
        sprite_pipe_small_up.move(Vector2f(-0.07, 0));
        sprite_pipe_big_up.move(Vector2f(-0.07, 0));

        if (sprite_pipe_small_down.getPosition().x < -50 && sprite_pipe_big_up.getPosition().x < -50) {

            sprite_pipe_small_down.move(Vector2f(500, 0));
            sprite_pipe_big_up.move(Vector2f(500, 0));

        } else if (sprite_pipe_big_down.getPosition().x < -50 && sprite_pipe_small_up.getPosition().x < -50) {

            sprite_pipe_big_down.move(Vector2f(500, 0));
            sprite_pipe_small_up.move(Vector2f(500, 0));

        }

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {

                window.close();

            }

        }

        // Here his movement loop is configured
        if (Keyboard::isKeyPressed(Keyboard::Space) && !holdKey) {

            v = -1.5;

            // This will make sure that the space key isn't held, otherwise Sam will stand still
            holdKey = true;

        } else {

            v = v + 0.01;

            if (v > 2.0) {

                v = 2.0;

            }

            sprite_sam.move(Vector2f(0, v));

        }

        // If the space key isn't pressed/held, allow another jump
        if (!Keyboard::isKeyPressed(Keyboard::Space) && holdKey) {

            holdKey = false;

        }

        //Here are the collision functions
        if (sprite_sam.getGlobalBounds().intersects(sprite_ground.getGlobalBounds())) {

            cout << "Collision with ground!" << endl;
            break;

        } else if (sprite_sam.getGlobalBounds().intersects(sprite_pipe_small_down.getGlobalBounds()) || sprite_sam.getGlobalBounds().intersects(sprite_pipe_big_down.getGlobalBounds())) {

            cout << "Collision with lower pipe!" << endl;
            break;

        } else if (sprite_sam.getGlobalBounds().intersects(sprite_pipe_small_up.getGlobalBounds()) || sprite_sam.getGlobalBounds().intersects(sprite_pipe_big_up.getGlobalBounds())) {

            cout << "Collision with upper pipe!" << endl;
            break;

        }

        window.clear();
        window.draw(background);
        window.draw(sprite_sam);
        window.draw(sprite_pipe_small_down);
        window.draw(sprite_pipe_big_down);
        window.draw(sprite_pipe_small_up);
        window.draw(sprite_pipe_big_up);
        window.draw(sprite_ground);
        window.display();

    }

    //system("pause");
    return 0;
}
