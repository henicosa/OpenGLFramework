#include "geometry_node.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>

GeometryNode::GeometryNode(std::shared_ptr<Node> pr, std::string const& n, std::string const& p, int d, glm::fmat4 const& lmat, glm::fmat4 const& wmat, model geo)
 :Node(pr,n, p, d, lmat, wmat)
 ,geometry(geo)
{};

  //
  // getter
  //
  model GeometryNode::getGeometry() const {
    return geometry;
  };

  //
  // setter
  //
  void GeometryNode::setGeometry(model geo) {
    geometry = geo;
  };



