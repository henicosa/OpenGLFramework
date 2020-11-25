#ifndef GEOMETRY_NODE_HPP
#define GEOMETRY_NODE_HPP

#include "node.hpp"
#include "model.hpp"

class GeometryNode : protected Node {
 public:
  GeometryNode(std::shared_ptr<Node> pr, std::string const& n, glm::fmat4 const& lmat, glm::fmat4 const& wmat, model geo);

  //
  // getter
  //
  model getGeometry() const;

  //
  // setter
  //
  void setGeometry(model geo);

 protected:
  model geometry;
};

#endif