#include <list>
#include <vector>
#include <glm/glm.hpp>
class World
{
public:
	~World();
	void Step(float dt);
	void Draw(class Graphics* graphics);
	void AddBody(class Body* bod);
	void RemoveBody(class Body* bod);
	void AddJoint(class Joint* join);
	void RemoveJoint(class Joint* join);
	void AddForceGen(class ForceGenerator* fg);
public:
	static glm::vec2 gravity;
private:
	std::list<class Body*> m_bodies;
	std::list<class Joint*> m_joints;
	std::vector<class ForceGenerator*> m_forceGenerators;
};
