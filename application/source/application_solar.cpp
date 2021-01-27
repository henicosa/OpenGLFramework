#include "application_solar.hpp"
#include "window_handler.hpp"

#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"
#include "node.hpp"
#include "geometry_node.hpp"
#include "scene_graph.hpp"
#include "texture_loader.hpp"

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
 ,model_objects{}
 ,m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 4.0f})}
 ,m_view_projection{utils::calculate_projection_matrix(initial_aspect_ratio)}
{
  //bool SceneGraph::instanceFlag = false;
  //SceneGraph* SceneGraph::single = NULL;
  std::vector<std::shared_ptr<Node>> nodes{};

  scene = SceneGraph::getInstance();
  std::shared_ptr<Node> p0 = std::make_shared<Node>(Node(scene->getRoot(), "sun_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.0f));
  scene->getRoot()->addChildren(p0);
  nodes.push_back(p0);
  std::shared_ptr<Node> pp0 = std::make_shared<Node>(GeometryNode(p0, "sun", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.0f, model{}, glm::vec3(1.0,1.0,1.0)));
  p0->addChildren(pp0);
  planet_colors["sun"] = glm::vec3(1.0,1.0,1.0);

  std::shared_ptr<Node> p1 = std::make_shared<Node>(Node(scene->getRoot(), "mercury_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 5.0f}), glm::fmat4(), 2.0f));
  scene->getRoot()->addChildren(p1);
  nodes.push_back(p1);
  std::shared_ptr<Node> pp1 = std::make_shared<Node>(GeometryNode(p1, "mercury", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.0f, model{}, glm::vec3(1.0,0.5,0.2)));
  p1->addChildren(pp1);
  planet_colors["mercury"] = glm::vec3(1.0,0.5,0.2);

  std::shared_ptr<Node> p2 = std::make_shared<Node>(Node(scene->getRoot(), "venus_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 8.0f}), glm::fmat4(), 0.6f));
  scene->getRoot()->addChildren(p2);
  nodes.push_back(p2);
  std::shared_ptr<Node> pp2 = std::make_shared<Node>(GeometryNode(p2, "venus", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.3f, model{}, glm::vec3(0.5,0.5,0.2)));
  p2->addChildren(pp2);
  planet_colors["venus"] = glm::vec3(0.5,0.5,0.2);

  std::shared_ptr<Node> p3 = std::make_shared<Node>(Node(scene->getRoot(), "earth_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 12.0f}), glm::fmat4(), 0.3f));
  scene->getRoot()->addChildren(p3);
  nodes.push_back(p3);
  std::shared_ptr<Node> pp3 = std::make_shared<Node>(GeometryNode(p3, "earth", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.2f, model{}, glm::vec3(0.2,0.4,1.0)));
  p3->addChildren(pp3);
  planet_colors["earth"] = glm::vec3(0.2,0.4,1.0);

  std::shared_ptr<Node> p4 = std::make_shared<Node>(Node(scene->getRoot(), "mars_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 15.0f}), glm::fmat4(), 0.34f));
  scene->getRoot()->addChildren(p4);
  nodes.push_back(p4);
  std::shared_ptr<Node> pp4 = std::make_shared<Node>(GeometryNode(p4, "mars", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.0f, model{}, glm::vec3(0.2,0.1,1.0)));
  p4->addChildren(pp4);
  planet_colors["mars"] = glm::vec3(0.2,0.1,1.0);

  std::shared_ptr<Node> p5 = std::make_shared<Node>(Node(scene->getRoot(), "jupiter", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 30.0f}), glm::fmat4(), 0.6f));
  //scene->getRoot()->addChildren(p5);
  //nodes.push_back(p5);


  std::shared_ptr<Node> p6 = std::make_shared<Node>(Node(scene->getRoot(), "saturn_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 50.0f}), glm::fmat4(), 0.2f));
  scene->getRoot()->addChildren(p6);
  nodes.push_back(p6);
  std::shared_ptr<Node> pp6 = std::make_shared<Node>(GeometryNode(p6, "saturn", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.3f, model{}, glm::vec3(1.0,1.0,0.2)));
  p6->addChildren(pp6);
  planet_colors["saturn"] = glm::vec3(1.0,1.0,0.2);

  std::shared_ptr<Node> p7 = std::make_shared<Node>(Node(scene->getRoot(), "uranus_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 57.0f}), glm::fmat4(), 0.1f));
  scene->getRoot()->addChildren(p7);
  nodes.push_back(p7);
  std::shared_ptr<Node> pp7 = std::make_shared<Node>(GeometryNode(p7, "uranus", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.1f, model{}, glm::vec3(0.7,0.5,1.0)));
  p7->addChildren(pp7);
  planet_colors["uranus"] = glm::vec3(0.7,0.5,1.0);

  std::shared_ptr<Node> p8 = std::make_shared<Node>(Node(scene->getRoot(), "jupiter_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 70.0f}), glm::fmat4(), 0.3f));
  scene->getRoot()->addChildren(p8);
  nodes.push_back(p8);
  std::shared_ptr<Node> pp8 = std::make_shared<Node>(GeometryNode(p8, "jupiter", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.3f, model{}, glm::vec3(0.9,1.0,0.4)));
  p8->addChildren(pp8);
  planet_colors["jupiter"] = glm::vec3(0.9,1.0,0.4);

  std::shared_ptr<Node> m1 = std::make_shared<Node>(Node(p3, "moon_handle", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 2.0f}), glm::fmat4(), 1.0f));
  scene->getRoot()->getChildren("earth_handle")->addChildren(m1);
  std::shared_ptr<Node> mm1 = std::make_shared<Node>(GeometryNode(m1, "moon", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 0.0f}), glm::fmat4(), 0.2f, model{}, glm::vec3(0.4,0.4,0.4)));
  m1->addChildren(mm1);
  planet_colors["moon"] = glm::vec3(0.4,0.4,0.4);
  //std::shared_ptr<Node> cam = std::make_shared<Node>(CameraNode(p3, "moon", glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 2.0f}), glm::fmat4(), 1.0f, true, true, glm::fmat4()));


  model_objects["planet"] = model_object{};
  model_objects["stars"] = model_object{};

  // for moon
  
  // for orbits
  for (auto node : nodes) {
    std::string orbit_name = "orbit";//node->getName() + "_orbit";
    model_objects[orbit_name] = model_object{};
    // generate orbit data
    auto tmat = node->getLocalTransform();
    float distance = tmat[3][0] + tmat[3][1] + tmat[3][2];
    //std::cout << distance;
    // reduce number of iterations (50)
    std::vector<float> orbit_data{};
    for (int d = 0; d< 256; d++) {
      orbit_data.push_back(sin(double(d)/256*2*M_PI)*distance);
      orbit_data.push_back(0);
      orbit_data.push_back(cos(double(d)/256*2*M_PI)*distance);
      orbit_data.push_back(0.8f);
      orbit_data.push_back(0.8f);
      orbit_data.push_back(0.8f);
    }

    // generate vertex array object
    glGenVertexArrays(1, &model_objects.at(orbit_name).vertex_AO);
    // bind the array for attaching buffers
    glBindVertexArray(model_objects.at(orbit_name).vertex_AO);

    // generate generic buffer
    glGenBuffers(1, &model_objects.at(orbit_name).vertex_BO);
    // bind this as an vertex array buffer containing all attributes
    glBindBuffer(GL_ARRAY_BUFFER, model_objects.at(orbit_name).vertex_BO);
    // configure currently bound array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * orbit_data.size(), orbit_data.data(), GL_STATIC_DRAW);

    // activate first attribute on gpu
    glEnableVertexAttribArray(0);
    // first attribute is 3 floats with no offset & stride (https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLsizei(6*sizeof(float)), 0);
    // activate second attribute on gpu
    glEnableVertexAttribArray(1);
    // second attribute is 3 floats with no offset & stride
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GLsizei(6*sizeof(float)), (void*)(sizeof(float)*3));
    // store type of primitive to draw
    model_objects.at(orbit_name).draw_mode = GL_LINE_LOOP;
    // transfer number of indices to model object 
    model_objects.at(orbit_name).num_elements = GLsizei(orbit_data.size()/6);
  }
  

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
  glGenVertexArrays(1, &model_objects["stars"].vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(model_objects["stars"].vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &model_objects["stars"].vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, model_objects["stars"].vertex_BO);
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
  glGenBuffers(1, &model_objects["stars"].element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_objects["stars"].element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, stars_data.size(), stars_data.data(), GL_STATIC_DRAW);
 */
  // store type of primitive to draw
  model_objects["stars"].draw_mode = GL_POINTS;
  // transfer number of indices to model object 
  model_objects["stars"].num_elements = GLsizei(stars_data.size()/6);

  //glGenVertexArrays() generates new Vertex arrays
  //glBindVertexArray() 

  //glGenBuffers()
  //glBindBuffer(GL_ARRAY_BUFFER, )
  //glBufferData(GL_ARRAY_BUFFER, )

  //glEnableVertexAttribArray()
  //glVertexAttribPointer()

  initializeGeometry();
  initializeShaderPrograms();
}

ApplicationSolar::~ApplicationSolar() {
  std::for_each(model_objects.begin(), model_objects.end(),
                [](std::pair<std::string, model_object> model_pair){
    glDeleteBuffers(1, &model_pair.second.vertex_BO);
    glDeleteBuffers(1, &model_pair.second.element_BO);
    glDeleteVertexArrays(1, &model_pair.second.vertex_AO);
  });
}


// starts rendering process 
void ApplicationSolar::render() const {
  traverse_render(scene->getRoot());


  for (auto model_pair : model_objects) {
    if (model_pair.first != "planet") {
      // Loading shader for stars
      glUseProgram(m_shaders.at(model_pair.first).handle);
      // bind the VAO to draw
      glBindVertexArray(model_objects.at(model_pair.first).vertex_AO);
      // draw bound vertex array using bound shader
      glDrawArrays(model_objects.at(model_pair.first).draw_mode, 0, model_objects.at(model_pair.first).num_elements);
    }
  }

}

// traverses the SceneGraph recursively, repeats rendering process
void ApplicationSolar::traverse_render(std::shared_ptr<Node> node) const {

  // TODO exclude cameras with "and node.getTypeID()"
  if ((node->getName() != "root") ) {

    node->setLocalTransform(glm::rotate(glm::fmat4{}, node->getRotation()*float(0.001), glm::fvec3{0.0f, 1.0f, 0.0f}) * node->getLocalTransform());

    if (node->isType("geometry_node")) {

      std::string render_option = "planet_cel";
      if (cel_render) {
        render_option = "planet";
      }

      glUseProgram(m_shaders.at(render_option).handle);

      // Transformation from parent * Rotation from Time (scale with factor), rotation axis

      

      // save transformation in WorldTransformation node

      glUniformMatrix4fv(m_shaders.at(render_option).u_locs.at("ModelMatrix"),
                        1, GL_FALSE, glm::value_ptr(node->getWorldTransform()));

      // extra matrix for normal transformation to keep them orthogonal to surface
      glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * node->getWorldTransform());
      glUniformMatrix4fv(m_shaders.at(render_option).u_locs.at("NormalMatrix"),
                        1, GL_FALSE, glm::value_ptr(normal_matrix));

     // GeometryNode* test = std::static_cast<GeometryNode *> (node);
      //std::cout <<  << std::endl;
      std::string name = node->getName();
      glUniform3fv(m_shaders.at(render_option).u_locs.at("Color"),
                          1, glm::value_ptr(planet_colors.at(name))
                          );
      
      glUniform3fv(m_shaders.at(render_option).u_locs.at("CameraPosition"),
                          1, glm::value_ptr(glm::vec3(m_view_transform[3].x, m_view_transform[3].y, m_view_transform[3].z))
                          );

      glUniform3fv(m_shaders.at(render_option).u_locs.at("LightColor"),
                          1, glm::value_ptr(glm::vec3(1,1,1))
                          );

      glUniform3fv(m_shaders.at(render_option).u_locs.at("LightPosition"),
                          1, glm::value_ptr(glm::vec3(0,0,2))
                          );
      
      glUniform1f(m_shaders.at(render_option).u_locs.at("LightIntensity"), 100.0f);
                          
      // bind the VAO to draw
      glBindVertexArray(model_objects.at(render_option).vertex_AO);

      // draw bound vertex array using bound shader
      glDrawElements(model_objects.at(render_option).draw_mode, model_objects.at("planet").num_elements, model::INDEX.type, NULL);

      //node->render(m_shaders, model_objects, this);
      // Handle orbits here


      //glUniformMatrix4fv(m_shaders.at("orbit").u_locs.at("ModelMatrix"),
      //                  1, GL_FALSE, glm::value_ptr(node->getWorldTransform()));
    }
  }

  // Repeat rendering for all childrens
  std::list<std::shared_ptr<Node>> planet_list = node->getChildrenList();
  for (auto planet : planet_list) traverse_render(planet);
  
}

void ApplicationSolar::uploadView() {
  // vertices are transformed in camera space, so camera transform must be inverted
  glm::fmat4 view_matrix = glm::inverse(m_view_transform);
  // upload matrix to gpu for each model
  for (auto model_pair : model_objects) {
    glUseProgram(m_shaders.at(model_pair.first).handle);
    glUniformMatrix4fv(m_shaders.at(model_pair.first).u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));
  }
}

void ApplicationSolar::uploadProjection() {
  // upload matrix to gpu for each model
  for (auto model_pair : model_objects) {
    glUseProgram(m_shaders.at(model_pair.first).handle);
    glUniformMatrix4fv(m_shaders.at(model_pair.first).u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));
  }
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
                                           {GL_FRAGMENT_SHADER, m_resource_path + "shaders/cel.frag"}}});
  // request uniform locations for shader program
  m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
  m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
  m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
  m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;
  m_shaders.at("planet").u_locs["Color"] = -1;
  m_shaders.at("planet").u_locs["CameraPosition"] = -1;
  m_shaders.at("planet").u_locs["LightColor"] = -1;
  m_shaders.at("planet").u_locs["LightPosition"] = -1;
  m_shaders.at("planet").u_locs["LightIntensity"] = -1;

  // store shader program objects in container
  m_shaders.emplace("planet_cel", shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/simple copy.vert"},
                                           {GL_FRAGMENT_SHADER, m_resource_path + "shaders/simple.frag"}}});
  // request uniform locations for shader program
  m_shaders.at("planet_cel").u_locs["NormalMatrix"] = -1;
  m_shaders.at("planet_cel").u_locs["ModelMatrix"] = -1;
  m_shaders.at("planet_cel").u_locs["ViewMatrix"] = -1;
  m_shaders.at("planet_cel").u_locs["ProjectionMatrix"] = -1;
  m_shaders.at("planet_cel").u_locs["Color"] = -1;
  m_shaders.at("planet_cel").u_locs["CameraPosition"] = -1;
  m_shaders.at("planet_cel").u_locs["LightColor"] = -1;
  m_shaders.at("planet_cel").u_locs["LightPosition"] = -1;
  m_shaders.at("planet_cel").u_locs["LightIntensity"] = -1;
  // for stars

  /*for (auto model_pair : model_objects) {
    if (model_pair.first != "planet") {
      m_shaders.emplace(model_pair.first, shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/" + model_pair.first + ".vert"},
                                              {GL_FRAGMENT_SHADER, m_resource_path + "shaders/" + model_pair.first +  ".frag"}}});
      // request uniform locations for shader program
      //m_shaders.at("stars").u_locs["NormalMatrix"] = -1;
      if (model_pair.first == "orbit") m_shaders.at(model_pair.first).u_locs["ModelMatrix"] = -1;
      m_shaders.at(model_pair.first).u_locs["ViewMatrix"] = -1;
      m_shaders.at(model_pair.first).u_locs["ProjectionMatrix"] = -1;
    }
  }*/

  // initialize each shader without loop
  for (auto model_pair : model_objects) {
    if (model_pair.first != "planet") {
      m_shaders.emplace(model_pair.first, shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/"+model_pair.first+".vert"},
                                              {GL_FRAGMENT_SHADER, m_resource_path + "shaders/"+model_pair.first+".frag"}}});
      // request uniform locations for shader program
      //m_shaders.at("stars").u_locs["NormalMatrix"] = -1;
      //if (model_pair.first == "orbit") m_shaders.at(model_pair.first).u_locs["ModelMatrix"] = -1;
      if (model_pair.first == "orbit") m_shaders.at(model_pair.first).u_locs["ModelMatrix"] = -1;
      m_shaders.at(model_pair.first).u_locs["ViewMatrix"] = -1;
      m_shaders.at(model_pair.first).u_locs["ProjectionMatrix"] = -1;
    }
  }
}

// load models
void ApplicationSolar::initializeGeometry() {
  model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL);

  pixel_data texture = texture_loader::file(m_resource_path + "textures/sunmap.jpg");
  // generate vertex array object
  glGenVertexArrays(1, &model_objects.at("planet").vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(model_objects.at("planet").vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &model_objects.at("planet").vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, model_objects.at("planet").vertex_BO);
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
  glGenBuffers(1, &model_objects.at("planet").element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_objects.at("planet").element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

  // store type of primitive to draw
  model_objects.at("planet").draw_mode = GL_TRIANGLES;
  // transfer number of indices to model object 
  model_objects.at("planet").num_elements = GLsizei(planet_model.indices.size());
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
  } else if (key == GLFW_KEY_1  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    cel_render = false;
  } else if (key == GLFW_KEY_2  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    cel_render = true;
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

glm::fmat4 ApplicationSolar::getMViewTransform() {
  return m_view_transform;
}
