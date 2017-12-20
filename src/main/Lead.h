#include "Boid.h"

class Lead : public Boid
{

    vec dest;

public:

    void init(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<float>& colors, const vec& pos, BoidState state);

    void steer(vec dest);

    void update(float dt);
};
