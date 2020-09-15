#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <character.h>

class GameManager
{
public:
  static GameManager* Instance();
  void Battle(std::shared_ptr<Character> character1, std::shared_ptr<Character> character2);

private:
  ~GameManager();
  static GameManager* instance;
};

#endif // GAMEMANAGER_H
