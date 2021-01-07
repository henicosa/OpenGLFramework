#ifndef NODE_HPP
#define NODE_HPP

#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <glm/matrix.hpp>

//#include "application_solar.hpp"
//#include "geometry_node.hpp"


class Node {
 public:

  Node();
  Node(std::shared_ptr<Node> pr, std::string const& n, glm::fmat4 const& lmat, glm::fmat4 const& wmat, float r);
  //
  // getter
  //
  std::shared_ptr<Node> getParent() const;
  // uses name to identify children
  std::shared_ptr<Node> getChildren(std::string node_name) const;
  std::list<std::shared_ptr<Node>>  getChildrenList() const;
  std::string getName() const;
  glm::fmat4 getLocalTransform() const;
  glm::fmat4 getWorldTransform() const;
  std::string getPath() const;
  int getDepth() const;
  float getRotation() const;


  //
  // setter
  //
  void setParent(std::shared_ptr<Node> node);
  void setLocalTransform(glm::fmat4 mat);
  void setWorldTransform(glm::fmat4 mat);
  void setRotation(float r);
  // modify Children List
  void addChildren(std::shared_ptr<Node> node);
  std::shared_ptr<Node> removeChildren(std::string node_name);

  // render
  bool isType(std::string typ);
  //void render(std::map<std::string, shader_program> m_shaders, std::map<std::string, model_object> model_objects, const ApplicationSolar* appSol);

  // protected for child classes access 
 protected:
  // parent node (for root nullptr)
  std::shared_ptr<Node> parent;
  // name
  std::string name;
  // local Transformation
  glm::fmat4 localTransform;
  // world Transformation
  glm::fmat4 worldTransform;
  // path (root/node/children_node)
  std::string path;
  // depth (root = 0, root/node = 1 ...)
  int depth;
  // list of children nodes
  std::list<std::shared_ptr<Node>> children;
  // rotation factor applied in rendering
  float rotation;
  std::string type = "node";

};

#endif