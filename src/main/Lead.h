#include "Boid.h"

class Lead : public Boid
{

    vec dest;

public:

    void init(std::vector<float>& vertices, std::vector<unsigned char>& indices, std::vector<float>& colors, const vec& pos, const vec& vel);

    void steer(vec dest);

    void update(float dt);
};