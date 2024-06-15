#ifndef BOW_H
#define BOW_H

#include "RangedWeapon.h"  // Include the header file for the base class

class Bow :  // Define the Bow class, inheriting from RangedWeapon
    public RangedWeapon
{
private:
  
public:
    // Constructor: initializes a Bow object with specified level, value, and texture file
    Bow(unsigned level, unsigned value, std::string texture_file);

    // Destructor: virtual destructor to ensure correct cleanup when derived classes are deleted
    virtual ~Bow();

    // Clone function: returns a pointer to a new Bow object, making polymorphic copying possible
    virtual Bow* clone();

    // Update function: updates the state of the Bow based on mouse position and center position
    virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center);

    // Render function: renders the Bow onto a render target, optionally using a shader
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

#endif // BOW_H
