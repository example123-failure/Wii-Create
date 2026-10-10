Notes on how to use OpenGL 1.x


Make sure to make the glfw Context current though

glfwMakeContextCurrent(window);





Enable depth testing so 3D objects hide faces properly
 glEnable(GL_DEPTH_TEST);
 
 
 use glClear to clear the color and depth buffers in the game loop
 at the beginning
 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
 
 
   Set Up Perspective (Lens Matrix)
glMatrixMode(GL_PROJECTION);
glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
glLoadMatrixf(glm::value_ptr(projection));



// 4. Set Up Camera and Position (ModelView Matrix)
glMatrixMode(GL_MODELVIEW);