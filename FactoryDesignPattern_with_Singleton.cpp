/**
 * I want to count the number of planes and number of boats in the code (or game)
 * Recap C++: a normal function can access both non-static as well as static data members
 *            but a static member function can only access the static data member.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

enum class ObjectType
{
    PLANE,
    BOAT,
};

class IGameObject
{
private:
    /* data */
public:
    IGameObject() {}
    virtual ~IGameObject() {}

    virtual void Update() = 0;      // Some methods relevant for the class... (not important here)
    virtual void Render() = 0;
};

class Plane : public IGameObject
{
private:
    /* data */
public:
    Plane() {}
    ~Plane() {}

    void Update() {}
    void Render() {}
};

class Boat : public IGameObject
{
private:
    /* data */
public:
    Boat() {}
    ~Boat() {}

    void Update() {}
    void Render() {}
};

// We move the MakeGameObjectFactory(renamed to CreateObject) method to a new class (Singleton)
class FactoryGameClass
{
private:
    FactoryGameClass() {}
    FactoryGameClass(const FactoryGameClass &) = delete; // deleting the copy constructor
    ~FactoryGameClass() {}

    static int num_planes;
    static int num_boats;

public:
    static FactoryGameClass &getInstance();

    static std::unique_ptr<IGameObject> CreateObject(ObjectType);

    void printCounts();
};

int FactoryGameClass::num_planes = 0; // initialize static variables outside the class
int FactoryGameClass::num_boats = 0;

std::unique_ptr<IGameObject> FactoryGameClass::CreateObject(ObjectType type)
{
    if (type == ObjectType::PLANE)
    {
        std::cout << "Plane created" << std::endl;
        num_planes++;
        return std::make_unique<Plane>();
    }
    else if (type == ObjectType::BOAT)
    {
        std::cout << "Boat created" << std::endl;
        num_boats++;
        return std::make_unique<Boat>();
    }
    std::cout << "None created" << std::endl;
    return nullptr;
}

FactoryGameClass &FactoryGameClass::getInstance()
{
    static FactoryGameClass *_my_instance = new FactoryGameClass();
    return *_my_instance;
}

void FactoryGameClass::printCounts()
{
    std::cout << "Planes count: " << num_planes << std::endl;
    std::cout << "Boats count: " << num_boats << std::endl;
}

int main()
{
    // We always want to access through the getInstance() method
    for (size_t i = 0; i < 3; i++)
    {
        // Creating planes
        std::unique_ptr<IGameObject> planeObj = FactoryGameClass::getInstance().CreateObject(ObjectType::PLANE);
    }
    for (size_t i = 0; i < 5; i++)
    {
        // Creating boats
        std::unique_ptr<IGameObject> boatObj = FactoryGameClass::getInstance().CreateObject(ObjectType::BOAT);
    }

    FactoryGameClass::getInstance().printCounts(); // printing the number of planes and boats created

    return 0;
}