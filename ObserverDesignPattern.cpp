/**
 * There are multiple observers which observe a particular subject
 * If the state of the subject changes, the observers are notified
 * and then response is taken based on it
 * E.g. use it in the AngryBirds game, when the bird collides, mulitple
 * responses are seen like, bird sound, bricks falling, score increment, pig
 * sounds, game physics etc all of these happens based on an event (or change
 * in state) of the subject (the bird here)
 *
 * The subject is sometimes called the Publisher and the observer called the
 * Subscriber
 */

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Abstract class of the Observer
 */
class IObserver
{
public:
    virtual ~IObserver() {}
    virtual void onNotify() = 0; // purely virtual function
};

/**
 * @brief Concrete implementation of the Observer
 * @brief Derives from the base class IObserver
 */
class Watcher : public IObserver
{
private:
    std::string _name;

public:
    Watcher(const std::string &);
    ~Watcher();

    void onNotify() override; // when the Observer is notified of the change in state of
                              // the subject
};

Watcher::Watcher(const std::string &name) : _name{name} {}

Watcher::~Watcher() {}

void Watcher::onNotify()
{
    std::cout << "Notified by subject to observer/watcher " << _name << std::endl;
}

/**
 * @brief Abstract class of the Subject
 */
class ISubject
{
public:
    virtual ~ISubject() {}
    virtual void AddObserver(IObserver *) = 0;
    virtual void RemoveObserver(IObserver *) = 0;
    virtual void NotifyAll() = 0;
};

/**
 * @brief Concrete implementation of the Subject
 * @brief Derives from the base class ISubject
 */
class Subject : public ISubject
{
private:
    std::vector<IObserver *> allObservers;

public:
    Subject() {}
    ~Subject() {}

    void AddObserver(IObserver *) override;
    void RemoveObserver(IObserver *) override;

    void NotifyAll() override;
};

void Subject::AddObserver(IObserver *obs)
{
    allObservers.push_back(obs);
    std::cout << "Added observer to allObserver vector" << std::endl;
}

void Subject::RemoveObserver(IObserver *obs)
{
    std::remove(allObservers.begin(), allObservers.end(), obs);
    std::cout << "Removed observer from allObserver vector" << std::endl;
}

void Subject::NotifyAll()
{
    for (const auto &obs : allObservers)
    {
        obs->onNotify(); // notify the observer
    }
}

int main()
{
    Subject sub;
    Watcher obs1("Observer1");
    Watcher obs2("Observer2");
    Watcher obs3("Observer3");

    sub.AddObserver(&obs1);
    sub.AddObserver(&obs2);
    sub.AddObserver(&obs3);
    sub.RemoveObserver(&obs3);

    sub.NotifyAll();

    return 0;
}