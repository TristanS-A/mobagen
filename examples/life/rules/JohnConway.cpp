#include "JohnConway.h"

#include <iostream>

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  //Iterates over the whole grid
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      const bool currSpace = world.Get({i, j}); //Gets the current space state
      const int liveNeighborCount = CountNeighbors(world, {i, j}); //Gets the live neighbor count of that point
      if (currSpace) { //Conditions for if the currSpace state is alive
        if (liveNeighborCount < 2) { //Rule for killing space due to underpopulation
          world.SetNext({i, j}, false);
        }
        else if (liveNeighborCount <= 3) { //Rule for setting space to alive for next generation
          world.SetNext({i, j}, true);
        }
        else { //Rule for killing space due to overpopulation
          world.SetNext({i, j}, false);
        }
      }
      else { //Rules for dead particles
        if (liveNeighborCount == 3) { //Rule for birthing new particle
          world.SetNext({i, j}, true);
        }
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int count = 0;

  //Iterates through the 3 by 3 grid of points surrounding the current point
  for (int i = point.x - 1; i < point.x + 2; i++) {
    for (int j = point.y - 1; j < point.y + 2; j++) {
      if (point.x != i || point.y != j) { //Excludes the current point
        count += static_cast<int>(world.Get({i, j})); //Increments the count if neighbor is alive
      }
    }
  }

  return count; //Returns the total live neighbor count
}
