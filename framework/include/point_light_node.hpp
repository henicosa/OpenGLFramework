#ifndef POINT_LIGHT_NODE_HPP
#define POINT_LIGHT_NODE_HPP

#include "node.hpp"
#include "model.hpp"

class PointLightNode : protected Node {
 public:

  PointLightNode(std::shared_ptr<Node> pr, std::string const& n, glm::fmat4 const& lmat, glm::fmat4 const& wmat, float r, bool perspective,  float lint, glm::vec3 lcol);

  //
  // getter
  //
  float getLightIntensity();
  glm::vec3 getLightColor();

  //
  // setter
  //
  void setLightIntensity(float lint);
  void setLightColor(glm::vec3 lcol);

 protected:
  float lightIntensity;
  glm::vec3 lightColor;
};

#endif