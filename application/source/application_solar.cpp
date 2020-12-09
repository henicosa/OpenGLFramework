#include "application_solar.hpp"
#include "window_handler.hpp"

#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"
#include "node.hpp"
#include "scene_graph.hpp"

// foreach
#include <algorithm>

#include <glbinding/gl/gl.h>
#include <iterator>
#include <memory>
// use gl definitions from glbinding 
using namespace gl;

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

ApplicationSolar::ApplicationSolar(std::string const& resource_path)
 :Application{resource_path}
 ,planet_object{}
 ,stars_object{}
 ,m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 4.0f})}
 ,m_view_projection{utils::calculate_projection_matrix(initial_aspect_ratio)}
{
  initializeGeometry();
  initializeShaderPrograms();
  //bool SceneGraph::instanceFlag = false;
  //SceneGraph* SceneGraph::single = NULL;
  std::vector<std::shared_ptr<Node>> nodes{};

  scene = SceneGraph::getInstance();
  std::shared_ptr<Node> p0 = std::make_shared<Node>(Node(scene->getRoot(), "sun", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.5f));
  scene->getRoot()->addChildren(p0);
  nodes.push_back(p0);
  std::shared_ptr<Node> p1 = std::make_shared<Node>(Node(scene->getRoot(), "mercury", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 5.0f}), glm::fmat4(), 2.0f));
  scene->getRoot()->addChildren(p1);
  nodes.push_back(p1);
  std::shared_ptr<Node> p2 = std::make_shared<Node>(Node(scene->getRoot(), "venus", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 8.0f}), glm::fmat4(), 0.6f));
  scene->getRoot()->addChildren(p2);
  nodes.push_back(p2);
  std::shared_ptr<Node> p3 = std::make_shared<Node>(Node(scene->getRoot(), "earth", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 12.0f}), glm::fmat4(), 0.3f));
  scene->getRoot()->addChildren(p3);
  nodes.push_back(p3);
  std::shared_ptr<Node> p4 = std::make_shared<Node>(Node(scene->getRoot(), "mars", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 15.0f}), glm::fmat4(), 0.34f));
  scene->getRoot()->addChildren(p4);
  nodes.push_back(p4);
  std::shared_ptr<Node> p5 = std::make_shared<Node>(Node(scene->getRoot(), "jupiter", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 40.0f}), glm::fmat4(), 0.6f));
  scene->getRoot()->addChildren(p5);
  nodes.push_back(p5);
  std::shared_ptr<Node> p6 = std::make_shared<Node>(Node(scene->getRoot(), "saturn", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 50.0f}), glm::fmat4(), 0.2f));
  scene->getRoot()->addChildren(p6);
  nodes.push_back(p6);
  std::shared_ptr<Node> p7 = std::make_shared<Node>(Node(scene->getRoot(), "uranus", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 57.0f}), glm::fmat4(), 0.1f));
  scene->getRoot()->addChildren(p7);
  nodes.push_back(p7);
  std::shared_ptr<Node> p8 = std::make_shared<Node>(Node(scene->getRoot(), "jupiter", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 70.0f}), glm::fmat4(), 0.3f));
  scene->getRoot()->addChildren(p8);
  nodes.push_back(p8);
  std::shared_ptr<Node> m1 = std::make_shared<Node>(Node(p3, "moon", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 2.0f}), glm::fmat4(), 1.0f));
  scene->getRoot()->getChildren("earth")->addChildren(m1);
  //std::shared_ptr<Node> cam = std::make_shared<Node>(CameraNode(p3, "moon", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 2.0f}), glm::fmat4(), 1.0f, true, true, glm::fmat4()));
  scene->getRoot()->getChildren("earth")->addChildren(m1);

  /* 
  //for (auto node : nodes) {
    auto node = p2;

    // generate orbit data
    auto tmat = node->getLocalTransform();
    float distance = tmat[3][0] + tmat[3][1] + tmat[3][2];
    std::cout << distance;
    std::vector<float> orbit_data{};
    for (int d = 0; d< 256; d++) {
      orbit_data.push_back(0);
      orbit_data.push_back(sin(d/256*2*M_PI)*distance);
      orbit_data.push_back(cos(d/256*2*M_PI)*distance);
    }

    // generate vertex array object
    glGenVertexArrays(1, &stars_object.vertex_AO);
    // bind the array for attaching buffers
    glBindVertexArray(stars_object.vertex_AO);

    // generate generic buffer
    glGenBuffers(1, &stars_object.vertex_BO);
    // bind this as an vertex array buffer containing all attributes
    glBindBuffer(GL_ARRAY_BUFFER, stars_object.vertex_BO);
    // configure currently bound array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * stars_data.size(), stars_data.data(), GL_STATIC_DRAW);

    // activate first attribute on gpu
    glEnableVertexAttribArray(0);
    // first attribute is 3 floats with no offset & stride (https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLsizei(6*sizeof(float)), 0);
    // activate second attribute on gpu
    glEnableVertexAttribArray(1);
    // second attribute is 3 floats with no offset & stride
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GLsizei(6*sizeof(float)), (void*)(sizeof(float)*3));
    // store type of primitive to draw
    stars_object.draw_mode = GL_POINTS;
    // transfer number of indices to model object 
    stars_object.num_elements = GLsizei(stars_data.size()/6);
  //} */
  

  std::vector<float> stars_data{};

  int starCount=500;
  int maxDist = 50;
  int minDist = 40;
  // randomly generate alot of stars
  for (int i = 0; i < starCount; i++) {
    // x, y, z
    for (int j = 0; j < 3; j++) {
      //float position = ((rand()%200 - 100)/100)*(maxDist-minDist) ;
      float position = 3.0f*((rand()%maxDist)-maxDist/2) ;
      stars_data.push_back(position);//float(pow(-1, (i+j)) * ((rand() % 10) + 50)) );
    }
    // r, g, b
    for (int j = 0; j < 3; j++) {
      stars_data.push_back(1 - float(rand() % 200)/500.0f);
    }
  }

  /*DEBUG for (auto i : stars_data)
    std::cout << i << " , ";*/

  // generate vertex array object
  glGenVertexArrays(1, &stars_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(stars_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &stars_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, stars_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * stars_data.size(), stars_data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride (https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLsizei(6*sizeof(float)), 0);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GLsizei(6*sizeof(float)), (void*)(sizeof(float)*3));

/*    // generate generic buffer
  glGenBuffers(1, &stars_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, stars_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, stars_data.size(), stars_data.data(), GL_STATIC_DRAW);
 */
  // store type of primitive to draw
  stars_object.draw_mode = GL_POINTS;
  // transfer number of indices to model object 
  stars_object.num_elements = GLsizei(stars_data.size()/6);

  //glGenVertexArrays() generates new Vertex arrays
  //glBindVertexArray() 

  //glGenBuffers()
  //glBindBuffer(GL_ARRAY_BUFFER, )
  //glBufferData(GL_ARRAY_BUFFER, )

  //glEnableVertexAttribArray()
  //glVertexAttribPointer()
}

ApplicationSolar::~ApplicationSolar() {
  glDeleteBuffers(1, &stars_object.vertex_BO);
  glDeleteBuffers(1, &stars_object.element_BO);
  glDeleteVertexArrays(1, &stars_object.vertex_AO);

  //stars

  glDeleteBuffers(1, &stars_object.vertex_BO);
  glDeleteBuffers(1, &stars_object.element_BO);
  glDeleteVertexArrays(1, &stars_object.vertex_AO);
}

// starts rendering process 
void ApplicationSolar::render() const {
  traverse_render(scene->getRoot());

  // Loading shader for stars
  glUseProgram(m_shaders.at("stars").handle);
  // bind the VAO to draw
  glBindVertexArray(stars_object.vertex_AO);

  // draw bound vertex array using bound shader
  glDrawArrays(stars_object.draw_mode, 0, stars_object.num_elements);
}

// traverses the SceneGraph recursively, repeats rendering process
void ApplicationSolar::traverse_render(std::shared_ptr<Node> node) const {

  // TODO exclude cameras with "and node.getTypeID()"
  if ((node->getName() != "root") ) {
    glUseProgram(m_shaders.at("planet").handle);

    // Transformation from parent * Rotation from Time (scale with factor), rotation axis

    node->setLocalTransform(glm::rotate(glm::fmat4{}, node->getRotation()*float(0.001), glm::fvec3{0.0f, 1.0f, 0.0f}) * node->getLocalTransform());

    // save transformation in WorldTransformation

    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                      1, GL_FALSE, glm::value_ptr(node->getWorldTransform()));

    // extra matrix for normal transformation to keep them orthogonal to surface
    glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * node->getWorldTransform());
    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
                      1, GL_FALSE, glm::value_ptr(normal_matrix));

    // bind the VAO to draw
    glBindVertexArray(planet_object.vertex_AO);

    // draw bound vertex array using bound shader
    glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);
  }

  // Repeat rendering for all childrens
  std::list<std::shared_ptr<Node>> planet_list = node->getChildrenList();
  for (auto planet : planet_list) traverse_render(planet);
  
}

void ApplicationSolar::uploadView() {
  // vertices are transformed in camera space, so camera transform must be inverted
  glm::fmat4 view_matrix = glm::inverse(m_view_transform);
  // upload matrix to gpu
  glUseProgram(m_shaders.at("planet").handle);
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));
  // for stars
  glUseProgram(m_shaders.at("stars").handle);
  glUniformMatrix4fv(m_shaders.at("stars").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));
}

void ApplicationSolar::uploadProjection() {
  glUseProgram(m_shaders.at("planet").handle);
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));
  // stars
  glUseProgram(m_shaders.at("stars").handle);
  glUniformMatrix4fv(m_shaders.at("stars").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));
}

// update uniform locations
void ApplicationSolar::uploadUniforms() { 
  // bind shader to which to upload unforms
  //glUseProgram(m_shaders.at("planet").handle);
  // stars
  //glUseProgram(m_shaders.at("stars").handle);
  // upload uniform values to new locations
  uploadView();
  uploadProjection();
}

///////////////////////////// intialisation functions /////////////////////////
// load shader sources
void ApplicationSolar::initializeShaderPrograms() {
  // store shader program objects in container
  m_shaders.emplace("planet", shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/simple.vert"},
                                           {GL_FRAGMENT_SHADER, m_resource_path + "shaders/simple.frag"}}});
  // request uniform locations for shader program
  m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
  m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
  m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
  m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;
  // for stars
  m_shaders.emplace("stars", shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/stars.vert"},
                                           {GL_FRAGMENT_SHADER, m_resource_path + "shaders/stars.frag"}}});
  // request uniform locations for shader program
  //m_shaders.at("stars").u_locs["NormalMatrix"] = -1;
  //m_shaders.at("stars").u_locs["ModelMatrix"] = -1;
  m_shaders.at("stars").u_locs["ViewMatrix"] = -1;
  m_shaders.at("stars").u_locs["ProjectionMatrix"] = -1;
}

// load models
void ApplicationSolar::initializeGeometry() {
  model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL);

  // generate vertex array object
  glGenVertexArrays(1, &planet_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(planet_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &planet_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);

   // generate generic buffer
  glGenBuffers(1, &planet_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

  // store type of primitive to draw
  planet_object.draw_mode = GL_TRIANGLES;
  // transfer number of indices to model object 
  planet_object.num_elements = GLsizei(planet_model.indices.size());
}

///////////////////////////// callback functions for window events ////////////
// handle key input
void ApplicationSolar::keyCallback(int key, int action, int mods) {
  if (key == GLFW_KEY_W  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, -0.1f});
    uploadView();
  } else if (key == GLFW_KEY_S  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, 0.1f});
    uploadView();
  } else if (key == GLFW_KEY_A  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.1f, 0.0f, 0.0f});
    uploadView();
  } else if (key == GLFW_KEY_D  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.1f, 0.0f, 0.0f});
    uploadView();
  } else if (key == GLFW_KEY_SPACE  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.1f, 0.0f});
    uploadView();
  } else if (key == GLFW_KEY_X  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, -0.1f, 0.0f});
    uploadView();
  }
}

//handle delta mouse movement input
void ApplicationSolar::mouseCallback(double pos_x, double pos_y) {
  m_view_transform = glm::rotate(m_view_transform, 0.01f, glm::fvec3{-pos_y, -pos_x, 0.0f});
  uploadView();
}

//handle resizing
void ApplicationSolar::resizeCallback(unsigned width, unsigned height) {
  // recalculate projection matrix for new aspect ration
  m_view_projection = utils::calculate_projection_matrix(float(width) / float(height));
  // upload new projection matrix
  uploadProjection();
}


// exe entry point
int main(int argc, char* argv[]) {
  Application::run<ApplicationSolar>(argc, argv, 3, 2);
}