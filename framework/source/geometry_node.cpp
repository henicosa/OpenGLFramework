#include "geometry_node.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>

GeometryNode::GeometryNode(std::shared_ptr<Node> pr, std::string const& n, glm::fmat4 const& lmat, glm::fmat4 const& wmat, float r, model geo, glm::vec3 col)
 :Node(pr, n, lmat, wmat, r)
 ,geometry(geo)
 ,color(col)
{
  type = "geometry_node";
}

  //
  // getter
  //
  model GeometryNode::getGeometry() const {
    return geometry;
  }
  glm::vec3 GeometryNode::getColor() const{
    return color;
  }

  //
  // setter
  //
  void GeometryNode::setGeometry(model geo) {
    geometry = geo;
  }
  void GeometryNode::setColor(glm::vec3 col) {
    color = col;
  }



