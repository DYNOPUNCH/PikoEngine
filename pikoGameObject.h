#ifndef PIKOGAMEOBJECT
#define PIKOGAMEOBJECT

// Base class for all game objects
class GameObject 
{
private:


public:

    // 2D Cartesian world position 
    int x = 0;
    int y = 0;

    // Object origin
    int xOrigin = 0;
    int yOrigin = 0;

    // Animation Speed
    int fps = 30;

    // The update method, which should be overridden by derived classes
    virtual void update(double deltaTime) = 0;

    virtual void step() = 0;

    virtual void draw(double deltaTime) = 0;
};

#endif