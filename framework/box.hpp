#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {

public:			Box();
				Box(glm::vec3 const& min_, glm::vec3 const& max_);
				Box(glm::vec3 const& min_, glm::vec3 const& max_, std::string const& name_, Color const& color_);
				~Box() override;
				glm::vec3 getMin() const;
				glm::vec3 getMax() const;
				virtual float area() const override;
				virtual float volume() const override;
				virtual std::ostream& print(std::ostream& os) const override;

private:		glm::vec3 min_;
				glm::vec3 max_;
};

#endif // !BOX_HPP
