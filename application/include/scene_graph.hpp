#ifndef SCENE_GRAPH_HPP
#define SCENE_GRAPH_HPP

#include "model.hpp"
#include "node.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>

#include <memory>

// Singleton pattern inspired by https://cplusplus-development.de/c/cplusplus-erweitert/entwurfsmuster-singleton-pattern

class SceneGraph {
 public:

  // Singleton
  // only instancable with controlling method
  static SceneGraph* getInstance(std::string n, std::shared_ptr<Node> node);
  // Reset flag if deleted
  ~SceneGraph()
		{
			instanceFlag = false;
		}
  //
  // getter
  //
  std::string getName() const;
  Node getRoot() const;

  //
  // setter
  //
  void setName(std::string n);
  void setRoot(std::shared_ptr<Node> node);

 private:
  std::string name;
  std::shared_ptr<Node> root;

  // Singleton Pattern
  static bool instanceFlag;
	static SceneGraph *single;
	SceneGraph(std::string n, std::shared_ptr<Node> node);
};

#endif