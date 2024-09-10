#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {

    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int count = 0;

  for (int i = point.x - 1; i < point.x + 1; i++) {
    for (int j = point.y - 1; j < point.y + 1; j++) {
      if (point.x != i && point.y != j) {
        count += static_cast<int>(world.Get({i, j}));
      }
    }
  }

  return count;
}
