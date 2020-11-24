#ifndef CAMERA_NODE_HPP
#define CAMERA_NODE_HPP

#include "node.hpp"
#include "model.hpp"

class CameraNode : protected Node {
 public:

  CameraNode(std::shared_ptr<Node> pr, std::string const& n, std::string const& p, int d, glm::fmat4 const& lmat, glm::fmat4 const& wmat, bool perspective, bool enabled, glm::fmat4 pmat);

  //
  // getter
  //
  bool getPerspective() const;
  bool getEnabled() const;
  glm::fmat4 getProjectionMatrix();

  //
  // setter
  //
  void setEnabled(bool enabled);
  void setProjectionMatrix(glm::fmat4 mat);

 protected:
  bool isPerspective;
  bool isEnabled;
  glm::fmat4 projectionMatrix;
};

#endif