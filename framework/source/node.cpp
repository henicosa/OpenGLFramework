#include "node.hpp"

#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>

void Node::test() {
  std::cout << "test";
}

Node::Node() 
 :parent(nullptr)
 ,name{"root"}
 ,localTransform{glm::fmat4()}
 ,worldTransform{glm::fmat4()}
 ,path{"root"}
 ,depth{0}
{}

Node::Node(std::shared_ptr<Node> pr, std::string const& n, glm::fmat4 const& lmat, glm::fmat4 const& wmat)
 :parent(pr)
 ,name{n}
 ,localTransform{lmat}
 ,worldTransform{wmat}
{
  depth = pr->getDepth() + 1;
  path = pr->getPath() + "/" + name;
}

  //
  // getter
  //
  std::shared_ptr<Node> Node::getParent() const {
    return parent;
  }

  std::shared_ptr<Node> Node::getChildren(std::string node_name) const {
    for (auto node : children) {
      if (node->getName().compare(node_name) == 0) return node;
    }
    return nullptr;
  }

  std::list<std::shared_ptr<Node>> Node::getChildrenList() const {
    return children;
  }

  std::string Node::getName() const {
    return name;
  }

  std::string Node::getPath() const {
    return path;
  }

  int Node::getDepth() const {
    return depth;
  }

  glm::fmat4 Node::getLocalTransform() const {
    return localTransform;
  }

  glm::fmat4 Node::getWorldTransform() const {
    return worldTransform;
  }


  //
  // setter
  //
  void Node::setParent(std::shared_ptr<Node> node) {
    parent = node;
  }

  void Node::setLocalTransform(glm::fmat4 mat) {
    localTransform = mat;
  }

  void Node::setWorldTransform(glm::fmat4 mat) {
    worldTransform = mat;
  }

  // modify Children List
  void Node::addChildren(std::shared_ptr<Node> node) {
    children.push_back(node);
  }

  std::shared_ptr<Node> Node::removeChildren(std::string node_name) {
    auto element = children.begin();
    while (element != children.end()) {
      if ((*element)->getName() == node_name) {
        element = children.erase(element);
      } else {
        element++;
      }
    }
  }
  


