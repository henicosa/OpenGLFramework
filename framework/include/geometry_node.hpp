#ifndef GEOMETRY_NODE_HPP
#define GEOMETRY_NODE_HPP

#include "node.hpp"
#include "model.hpp"

class GeometryNode : protected Node {
 public:
  GeometryNode(std::shared_ptr<Node> pr, std::string const& n, glm::fmat4 const& lmat, glm::fmat4 const& wmat, float r, model geo, glm::vec3 col);

  //
  // getter
  //
  model getGeometry() const;
  glm::vec3 getColor() const;

  //
  // setter
  //
  void setGeometry(model geo);
  void setColor(glm::vec3 col);

 protected:
  model geometry;
  glm::vec3 color;
};

#endif