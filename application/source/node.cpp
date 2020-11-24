#include "node.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>

Node::Node(std::shared_ptr<Node> pr, std::string const& n, std::string const& p, int d, glm::fmat4 const& lmat, glm::fmat4 const& wmat)
 :parent(pr)
 ,name{n}
 ,path{p}
 ,depth{d}
 ,localTransform{lmat}
 ,worldTransform{wmat}
{};

  //
  // getter
  //
  std::shared_ptr<Node> Node::getParent() const {
    return parent;
  };

  std::shared_ptr<Node> Node::getChildren(std::string node_name) const {
    return parent;
  };

  std::list<Node> Node::getChildrenList() const {
    return children;
  };

  std::string Node::getName() const {
    return name;
  };

  std::string Node::getPath() const {
    return path;
  };

  int Node::getDepth() const {
    return depth;
  };

  glm::fmat4 Node::getLocalTransform() const {
    return localTransform;
  };

  glm::fmat4 Node::getWorldTransform() const {
    return worldTransform;
  };


  //
  // setter
  //
  void Node::setParent(std::shared_ptr<Node> node) {
    parent = node;
  };

  void Node::setLocalTransform(glm::fmat4 mat) {
    localTransform = mat;
  };

  void Node::setWorldTransform(glm::fmat4 mat) {
    worldTransform = mat;
  };

  // modify Children List
  void Node::addChildren(std::shared_ptr<Node> node) {
    children.push_back(node);
  };

  std::shared_ptr<Node> Node::removeChildren(std::string node_name) {
    auto element = children.begin();
    while (element != children.end()) {
      if ((*element)->getName() == node_name) {
        element = children.erase(element);
      } else {
        element++;
      }
    }
  };


