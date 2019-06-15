#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {

public:			Box();
				Box(glm::vec3 const& min_, glm::vec3 const& max_);
				glm::vec3 getMin();
				glm::vec3 getMax();
				virtual float area() const override;
				virtual float volume() const override;

private:		glm::vec3 min_;
				glm::vec3 max_;
};

#endif // !BOX_HPP
