#include "utils.h"
#include <vector>
#define BOID_POINTS 3
#define BOID_LENGTH 4.
#define BOID_WIDTH 1.

class Boid
{
public:
  float* vertex;
  //vec velocity;
  //unsigned oldIndex;

  Boid(std::vector<float>& vertices, std::vector<int>& indices, std::vector<float>& colors, const vec& pos)
    : vertex(vertices.data()+vertices.size())
  {
    indices.push_back(vertices.size()/2);
    indices.push_back((vertices.size()/2)+1);
    indices.push_back((vertices.size()/2)+2);

    vertices.push_back(pos.x);
    vertices.push_back(pos.y);
    vertices.push_back(pos.x+BOID_WIDTH);
    vertices.push_back(pos.y+BOID_LENGTH);
    vertices.push_back(pos.x-BOID_WIDTH);
    vertices.push_back(pos.y+BOID_LENGTH);

    for (unsigned i=0; i<BOID_POINTS; ++i){
      colors.push_back(1);
      colors.push_back(1);
      colors.push_back(1);
    }
  }
};

