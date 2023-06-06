#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

struct Character
{
    int x;
    int y;

    Character()
        : x{0}, y{0} {};

    void update_position(int _x, int _y)
    {
        x += _x;
        y += _y;
    }
};

class CommandPattern
{
private:
public:
    CommandPattern() {}
    virtual ~CommandPattern() {}

    virtual void execute(Character &) = 0;
    virtual void undo(Character &) = 0; // opposite of whatever execute does
};

class Move : public CommandPattern
{
private:
    int movement_distance_x;
    int movement_distance_y;

public:
    Move() {}
    ~Move() {}

    void execute(Character &) override;
    void undo(Character &) override;
};

void Move::execute(Character &character)
{
    movement_distance_x = rand() % 10;
    movement_distance_y = rand() % 10;
    character.update_position(movement_distance_x, movement_distance_y);
    std::cout << "Character moved by: " << movement_distance_x << ", "
              << movement_distance_y << std::endl;
}

void Move::undo(Character &character)
{
    character.update_position(-movement_distance_x, -movement_distance_y);
    std::cout << "Character moved by: " << -movement_distance_x << ", "
              << -movement_distance_y << std::endl;
}

int main()
{
    Character player;
    std::cout << "Start Position: " << player.x << ", " << player.y << std::endl;

    std::vector<std::unique_ptr<CommandPattern>> commands;
    for (size_t i = 0; i < 4; i++)
    {
        std::unique_ptr<CommandPattern> m = std::make_unique<Move>();
        commands.push_back(std::move(m));
        // commands.push_back(std::move(std::make_unique<Move>()));    // one-liner
    }
    for (int i = 0; i < commands.size(); i++)
    {
        commands[i]->execute(player);
        std::cout << "Position: " << player.x << ", " << player.y << std::endl;
    }
    for (int i = commands.size() - 1; i >= 0; i--)
    {
        commands[i]->undo(player);
        std::cout << "Position: " << player.x << ", " << player.y << std::endl;
    }

    // A better data-structure is to use a Stack instead of a Vector

    return 0;
}
