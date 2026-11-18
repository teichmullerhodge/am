
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>


struct RGBAColor {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

};

RGBAColor background_colors[] = {
  {0,0,0,255},
  {0,0,255,255},
  {0,255,0,255},
  {255,0,0,255},
  {0,255,255,255},
};

size_t color_idx = 0;

void process_input_cb(GLFWwindow* window, int key, int scancode, int action, int mods){
  (void)scancode;
  (void)mods;

  printf("Key callback called: %d\n", key);
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    return;
  }
  if(key == GLFW_KEY_SPACE && action == GLFW_RELEASE){
    if(color_idx >= 4) {
      color_idx = 0;
      return;
    }
    color_idx++;
    return;
  }
}


void error_cb(int error, const char* description){

    fprintf(stderr, "Error: %s\n", description);

}

void window_resize_cb(GLFWwindow *window, int width, int height){
  glViewport(0, 0, width, height);
  printf("Window resized to: (W: %d, H: %d)\n", width, height);
  return;
}

GLFWwindow* init_window(int width, int height, const char *window_name){

  GLFWwindow *window = glfwCreateWindow(800, 600, window_name, NULL, NULL);
  glfwMakeContextCurrent(window);
  return window;

}

#define W_NAME "AM Engine - Lesson 01"

int main(int argc, char **argv){

  (void)argc;
  (void)argv;
  
  int initialization = glfwInit();

  if(initialization != GLFW_TRUE){
    perror("Error initializing GLFW");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  GLFWwindow *window = init_window(800, 600, W_NAME);
 

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    perror("Glad initialization failed");
    return -2;
  }
  

  const unsigned char *open_gl_version = glGetString(GL_VERSION);

  const unsigned char *gpu_manufacturer = glGetString(GL_VENDOR);

  const unsigned char *renderer = glGetString(GL_RENDERER);


  printf("Version: %s. - Vendor: %s. - Renderer: %s.\n", 
      open_gl_version,
      gpu_manufacturer,
      renderer
  );

  glfwSetErrorCallback(error_cb);
  glfwSetKeyCallback(window, process_input_cb);
  glfwSetWindowSizeCallback(window, window_resize_cb);
  while(!glfwWindowShouldClose(window)){

    float seconds_elapsed = glfwGetTime();
    /// at index 0 we change the background color to blue...

    printf("Seconds elapsed: %d\n", (int)seconds_elapsed);
    float r = background_colors[color_idx].r / 255.0f;
    float g = background_colors[color_idx].g / 255.0f;
    float b = background_colors[color_idx].b / 255.0f;
    float a = background_colors[color_idx].a / 255.0f;

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
 

    glfwSwapBuffers(window);
    glfwPollEvents();




  }
      

    
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;


}
