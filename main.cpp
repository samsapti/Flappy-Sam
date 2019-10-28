#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>

int p=1;

int main()
{

// Here the window is created with the title "flappy sam"
 sf::RenderWindow window( sf::VideoMode(432, 700 ), "Flappy Sam" );

// Here the background is defined
sf::RectangleShape background(sf::Vector2f(432, 700));
background.setFillColor(sf::Color(97, 166, 255));


 // LAV OM TIL SPRITE!!!!!!!

 // Here the TEST OBSTACLES ARE DEFINED
 sf::RectangleShape pipe(sf::Vector2f(50, 200));
 pipe.setFillColor(sf::Color(0, 255, 0));
 pipe.setPosition(sf::Vector2f(300, 500));



// Here the textures are defined
 sf::Texture texture_sam;

 if (!texture_sam.loadFromFile("8bit-sam.png"))
 {

     std::cout << "Error loading 8bit-sam.png :(\n";
 }


// Here the object Sam is created
 sf::Sprite sprite_sam;
 sprite_sam.setTexture(texture_sam);

 // Here he is placed in the middle
 sprite_sam.setPosition(sf::Vector2f(75, 220));

 // !!POSITION TEST!!
 std::cout << "x-position: " << sprite_sam.getPosition().x << std::endl;

 // This makes sure the window is active and that it can be moved and closed manually
 while (window.isOpen( ) )
 {

     sf::Event event;
     pipe.move(sf::Vector2f(-0.01, 0));

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
    std::cout << "Collision!\n";
}



    // Here his movement loop is configured
 if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space))
       {
           sprite_sam.move(sf::Vector2f(0, -0.1));

       } else {
       sprite_sam.move(sf::Vector2f(0, 0.1));
       }




     window.clear();

     window.draw(background);

     window.draw(sprite_sam);

     window.draw(pipe);

     window.display();
 }

}
