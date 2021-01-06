#include "point_light_node.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>

PointLightNode::PointLightNode(std::shared_ptr<Node> pr, std::string const& n, glm::fmat4 const& lmat, glm::fmat4 const& wmat, float r, bool perspective,  float lint, glm::vec3 lcol)
 :Node(pr,n, lmat, wmat, r)
 ,lightIntensity(lint)
 ,lightColor(lcol)
{}


//
// getter
//
float PointLightNode::getLightIntensity() {
  return lightIntensity;
}

glm::vec3 PointLightNode::getLightColor() {
  return lightColor;
}

//
// setter
//
void PointLightNode::setLightIntensity(float lint) {
  lightIntensity = lint;
}

void PointLightNode::setLightColor(glm::vec3 lcol) {
  lightColor = lcol;
}



