#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>

int p=1;



float v = 0;
int main()
{

// Here the window is created with the title "flappy sam"
 sf::RenderWindow window( sf::VideoMode(400, 650 ), "Flappy Sam" );

// Here the background is defined
sf::RectangleShape background(sf::Vector2f(400, 650));
background.setFillColor(sf::Color(97, 166, 255));


// Here the textures are defined

//Ground
 sf::Texture texture_ground;
 if (!texture_ground.loadFromFile("img\\ground.png"))
 {
     std::cout << "Error loading ground.png\n";
 }

//Sam
 sf::Texture texture_sam;
 if (!texture_sam.loadFromFile("img\\8bit-sam.png"))
 {

     std::cout << "Error loading 8bit-sam.png :(\n";
 }

//Pipe
 sf::Texture texture_pipe;
 if (!texture_pipe.loadFromFile("img\\pipe.png"))
 {
     std::cout << "Error loading pipe.png :(\n";
 }

//OBJECTS

//Here the object ground is created
 sf::Sprite sprite_ground;
 sprite_ground.setTexture(texture_ground);

     //Here it is placed
     sprite_ground.setPosition(sf::Vector2f(0, 610));

// Here the object Sam is created
 sf::Sprite sprite_sam;
 sprite_sam.setTexture(texture_sam);

     // Here he is placed in the middle
     sprite_sam.setPosition(sf::Vector2f(75, 220));

 //Here the object pipe is created
 sf::Sprite sprite_pipe;
 sprite_pipe.setTexture(texture_pipe);

     //Here it is placed in the map
     sprite_pipe.setPosition(sf::Vector2f(300, 500));



 // !!POSITION TEST!!
 std::cout << "x-position: " << sprite_sam.getPosition().x << std::endl;

 // This makes sure the window is active and that it can be moved and closed manually
 while (window.isOpen( ) )
 {

     sf::Event event;
     sprite_pipe.move(sf::Vector2f(-0.1, 0));

     while ( window.pollEvent( event ) )
     {


         switch (event.type)
         {
         case sf::Event::Closed:
            window.close();




            break;




         }
     }



{

}




    // Here his movement loop is configured
 if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space))
       {
           v = -1.5;

       } else {
           v = v + 0.01;
           if (v > 2.0)
           {
               v = 2.0;
           }
       sprite_sam.move(sf::Vector2f(0, v));
       }


       //Here are the collision functions
if (sprite_sam.getGlobalBounds().intersects(sprite_ground.getGlobalBounds()))
     {

         std::cout << "Collision with ground!\n";
         break;

     }
    else if (sprite_sam.getGlobalBounds().intersects(sprite_pipe.getGlobalBounds()))
     {

         std::cout << "Collision with pipe!\n";
         break;

    }





     window.clear();

     window.draw(background);

     window.draw(sprite_sam);

     window.draw(sprite_pipe);

     window.draw(sprite_ground);

     window.display();
 }


 system("pause");
    return 0;
}
