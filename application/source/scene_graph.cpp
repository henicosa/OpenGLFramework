
#include "scene_graph.hpp"

// Singleton pattern inspired by https://cplusplus-development.de/c/cplusplus-erweitert/entwurfsmuster-singleton-pattern


  // Singleton
  // only instancable with controlling method
  static SceneGraph* SceneGraph::getInstance(std::string n, std::shared_ptr<Node> node) {
    if (!instanceFlag)
	  {
		  single = new SceneGraph(n, node);
		  instanceFlag = true;
		  return single;
	  } else {
		  return single;
	  }
  };

  //
  // getter
  //
  std::string SceneGraph::getName() const {
    return name;
  };
  
  std::shared_ptr<Node> SceneGraph::getRoot() const {
    return node;
  };

  //
  // setter
  //
  void SceneGraph::setName(std::string n) {
    name = n;
  };

  void SceneGraph::setRoot(std::shared_ptr<Node> node) {
    root = node;
  };

  // Singleton Pattern
	SceneGraph::SceneGraph(std::string n, std::shared_ptr<Node> node)
    :name(n)
    ,root(node) 
  {}; 

