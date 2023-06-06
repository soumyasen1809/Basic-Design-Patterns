/**
 * Factory Design Pattern is a Creational Design pattern
 * Provides a way to create objects such that the implementation details
 * are hidden to the derived class
 * Inhertience based Polymorphism is used here
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

    virtual void Update() = 0;
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

std::unique_ptr<IGameObject> MakeGameObjectFactory(ObjectType type)
{
    if (type == ObjectType::PLANE)
    {
        std::cout << "Plane created" << std::endl;
        return std::make_unique<Plane>();
    }
    else if (type == ObjectType::BOAT)
    {
        std::cout << "Boat created" << std::endl;
        return std::make_unique<Boat>();
    }
    std::cout << "None created" << std::endl;
    return nullptr;
}

int main()
{
    std::unique_ptr<IGameObject> myObjBoat = MakeGameObjectFactory(ObjectType::BOAT);
    std::unique_ptr<IGameObject> myObjPlane = MakeGameObjectFactory(ObjectType::PLANE);

    return 0;
}