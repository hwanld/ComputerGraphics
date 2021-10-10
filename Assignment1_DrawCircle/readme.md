<h3>Assignment1_DrawCircle</h3>
**-Goal : draw circle with using GL_TRIANGLES<br>**
-Using "toys.h" header file, copyright by Hyun Joon Shin (Professor/Digital Media Department/Ajou University)<br>
-Using global variable; Program program, GLuint vertBuf,triBuf,vertArray_can use everywhere like function<br>
-Using 2 functions ; void init(), void render(GLFWwindow* window)<br>
**-Ideas : Using circular coordinate system to represent the vector which is on the circle, than draw the triangles with ther vertices**
-void init()<br>
  Load shades by program.loadShaders(".vert,.frag")<br>
  Make vector container to save the informations of vertice : std::vector<glm::vec3> vert;<br>
    glm::vec3 is the data type which is in glm library, means 3-dimension vector's each value (x,y,z)<br>
  Then push_back the informations of vertice : each vertice's index is same to the index of the vector container<br>
    push_back the origin vector : (0,0,0) <br>
    push_back the vector which is on the circle : we cannot represent the circle with infinitive vectors; so in this, I represent the circle with the number of triangles and circular coordinate systems.
    For declaring the number of triangle with macro; it's easy to control the variable. Each vertice's informations is same as below : <br>
      GLfloat theta = (GLfloat)(2 * PI) / howMuchTriUseForCircle * i;
      x = (GLfloat)RADUIS * std::cos(theta);<br>
		  y = (GLfloat)RADUIS * std::sin(theta);<br>
    Using GLFloat data type is more appropriate when we use computer graphics but the "PI", "howMuchTriUseForCircle" is just macro; the type of these is double
    So I used casting to change data type; (GLfloat)<br>
  Also make vector container to save the informations of triangles_which vertices comprise each triangles_std::vector <glm::u32vec3> triangles;<br>
    glm::u32vec3 is the data type which is in glm library, means unsigned 32 bits vector's each value (x,y,z)<br>
  Then push_back the informations of vertice : each vertice's index is same to the index of the vector container<br>
    All the triangles' starting point is origin vector<br>
    Each triangles' index is like : (0, i, i+1)<br>
    But the last triangles' index is not like above : we have to control the exception by using conditional statement<br>
      if (i == howMuchTriUseForCircle) triangles.push_back(glm::u32vec3(0, i, 1));<br>
		  else triangles.push_back(glm::u32vec3(0, i, i+1));<br>
  After that, make verticeBuffer, TriBuffer like below :<br>
    glGenBuffers(1, &vertBuf);<br>
	  glBindBuffer(GL_ARRAY_BUFFER, vertBuf);<br>
	  glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(glm::vec3), vert.data(), GL_STATIC_DRAW);<br>
  Also, make vertexArray like below :<br>
    glGenVertexArrays(1, &vertArray);<br>
  	glBindVertexArray(vertArray);<br>
	  glEnableVertexAttribArray(0);<br>
	  glBindBuffer(GL_ARRAY_BUFFER, vertBuf);<br>
	  glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);<br><br>
-void render (GLFWwindow* window)<br>
  Easy to render because all the informations of vertices and primitives are in the global variable, and each is binded at init function
  Load program's ID : glUseProgram(program.programID)<br>
  Bind vertexArray and buffers
  After Binding, draw elements : glDrawElements(GL_TRIANGLES, 3*howMuchTriUseForCircle, GL_UNSIGNED_INT, 0);
  
    
  
