#include "camera_node.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>

CameraNode::CameraNode(std::shared_ptr<Node> pr, std::string const& n, glm::fmat4 const& lmat, glm::fmat4 const& wmat, bool perspective, bool enabled, glm::fmat4 pmat)
 :Node(pr,n, lmat, wmat)
 ,isPerspective(perspective)
 ,isEnabled(enabled)
 ,projectionMatrix(pmat)
{}


  //
  // getter
  //
  bool CameraNode::getPerspective() const {
    return isPerspective;
  }

  bool CameraNode::getEnabled() const {
    return isEnabled;
  }

  glm::fmat4 CameraNode::getProjectionMatrix() const {
    return projectionMatrix;
  }


  //
  // setter
  //
  void CameraNode::setEnabled(bool enabled) {
    isEnabled = enabled;
  }

  void CameraNode::setProjectionMatrix(glm::fmat4 mat) {
    projectionMatrix = mat;
  }




