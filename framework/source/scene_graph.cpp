
#include "scene_graph.hpp"
#include <memory>

// Singleton pattern inspired by https://cplusplus-development.de/c/cplusplus-erweitert/entwurfsmuster-singleton-pattern


// Singleton
// only instancable with controlling method

/*SceneGraph* SceneGraph::getInstance() {
    if (!instanceFlag)
	  {
		  single = new SceneGraph();
		  instanceFlag = true;
		  return single;
	  } else {
		  return single;
	  }
  }
  
  */

  SceneGraph::SceneGraph()
    :name("scene")
    ,root(std::make_shared<Node>(Node()))
  {}

  //
  // getter
  //
  std::string SceneGraph::getName() const {
    return name;
  }
  
  std::shared_ptr<Node> SceneGraph::getRoot() const {
    return root;
  }

  //
  // setter
  //
  void SceneGraph::setName(std::string n) {
    name = n;
  }

  void SceneGraph::setRoot(std::shared_ptr<Node> node) {
    root = node;
  }

