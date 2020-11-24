#ifndef NODE_HPP
#define NODE_HPP

#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <glm/matrix.hpp>


class Node {
 public:

  Node();

  //
  // getter
  //
  Node getParent() const;
  Node getChildren(std::string node_name) const;
  std::list<Node>  getChildrenList() const;
  std::string getName() const;
  std::string getPath() const;
  int getDepth() const;
  glm::fmat4 getLocalTransform() const;
  glm::fmat4 getWorldTransform() const;

  //
  // setter
  //
  void setParent(Node node);
  void setLocalTransform(glm::fmat4 mat);
  void setWorldTransform(glm::fmat4 mat);
  // modify Children List
  void addChildren(Node node);
  Node removeChildren(std::string node_name);

 protected:
  std::shared_ptr<Node> parent;
  std::list<std::shared_ptr<Node>> children;
  std::string name;
  std::string path;
  int depth;
  glm::fmat4 localTransform;
  glm::fmat4 worldTransform;

};

#endif