#ifndef APPLICATION_SOLAR_HPP
#define APPLICATION_SOLAR_HPP

#include "application.hpp"
#include "application_vao.hpp"
#include "model.hpp"
#include "structs.hpp"

#include "node.hpp"
#include "geometry_node.hpp"
#include "camera_node.hpp"
#include "scene_graph.hpp"
#include <memory>

// gpu representation of model
class ApplicationSolar : public Application {
 public:
  // allocate and initialize objects
  ApplicationSolar(std::string const& resource_path);
  // free allocated objects
  ~ApplicationSolar();

  // react to key input
  void keyCallback(int key, int action, int mods);
  //handle delta mouse movement input
  void mouseCallback(double pos_x, double pos_y);
  //handle resizing
  void resizeCallback(unsigned width, unsigned height);

  // draw all objects
  void render() const;
  void traverse_render(std::shared_ptr<Node> node) const;
  void initializeTexture(std::string planet_name);
  
  // getter
  glm::fmat4 getMViewTransform();

 protected:
  void initializeShaderPrograms();
  void initializeGeometry();
  // update uniform values
  void uploadUniforms();
  // upload projection matrix
  void uploadProjection();
  // upload view matrix
  void uploadView();

  // map for cpu representation of models
  std::map<std::string, model_object> model_objects{};
  std::map<std::string, glm::vec3> planet_colors{};
  std::map<std::string, int> planet_textures{};

  // change render to cel render flag
  bool cel_render = true;

  // camera transform matrix
  glm::fmat4 m_view_transform;
  // camera projection matrix
  glm::fmat4 m_view_projection;

  // SceneGraph
  SceneGraph* scene;

  // FrameBuffer
  unsigned int myFbo;
  unsigned int screenTexture;
  // Post Processing
  bool mirrorV = false;
  bool mirrorH = false;
  bool luminance = false;
  bool blur = false;
  bool negation = false;
  //std::shared_ptr<ApplicationVao> appvao;
};

#endif