<h2>Assignment1_DrawCircle</h2>
<b>-Goal : draw circle with using GL_TRIANGLES</b><br>
-Using "toys.h" header file, copyright by Hyun Joon Shin (Professor/Digital Media Department/Ajou University)<br>
-Using global variable; Program program, GLuint vertBuf,triBuf,vertArray_can use everywhere like function<br>
-Using 2 functions ; void init(), void render(GLFWwindow* window)<br>
<b>-Ideas : Using circular coordinate system to represent the vector which is on the circle, than draw the triangles with ther vertices</b><br>
-void init()<br>
  &nbsp; &nbsp; &nbsp; &nbsp;Load shades by program.loadShaders(".vert,.frag")<br>
  &nbsp; &nbsp; &nbsp; &nbsp;Make vector container to save the informations of vertice : std::vector<glm::vec3> vert;<br>
    &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glm::vec3 is the data type which is in glm library, means 3-dimension vector's each value (x,y,z)<br>
  &nbsp; &nbsp; &nbsp; &nbsp;Then push_back the informations of vertice : each vertice's index is same to the index of the vector container<br>
   &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;push_back the origin vector : (0,0,0) <br>
   &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;push_back the vector which is on the circle : we cannot represent the circle with infinitive vectors; so in this, I represent the circle with  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbspthe number of triangles and circular coordinate systems.<br>
    &nbsp; &nbsp; &nbsp; &nbsp;For declaring the number of triangle with macro; it's easy to control the variable. Each vertice's informations is same as below : <br>
     &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;GLfloat theta = (GLfloat)(2 * PI) / howMuchTriUseForCircle * i;<br>
     &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;x = (GLfloat)RADUIS * std::cos(theta);<br>
     &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;y = (GLfloat)RADUIS * std::sin(theta);<br>
    &nbsp; &nbsp; &nbsp; &nbsp;Using GLFloat data type is more appropriate when we use computer graphics but the "PI", "howMuchTriUseForCircle" is just macro; the type of these is double
    &nbsp; &nbsp; &nbsp; &nbsp;So I used casting to change data type; (GLfloat)<br>
  &nbsp; &nbsp; &nbsp; &nbsp;Also make vector container to save the informations of triangles_which vertices comprise each triangles_std::vector <glm::u32vec3> triangles;<br>
    &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glm::u32vec3 is the data type which is in glm library, means unsigned 32 bits vector's each value (x,y,z)<br>
  &nbsp; &nbsp; &nbsp; &nbsp;Then push_back the informations of vertice : each vertice's index is same to the index of the vector container<br>
    &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;All the triangles' starting point is origin vector<br>
    &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;Each triangles' index is like : (0, i, i+1)<br>
    &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;But the last triangles' index is not like above : we have to control the exception by using conditional statement<br>
      &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;if (i == howMuchTriUseForCircle) triangles.push_back(glm::u32vec3(0, i, 1));<br>
		  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;else triangles.push_back(glm::u32vec3(0, i, i+1));<br>
  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;After that, make verticeBuffer, TriBuffer like below :<br>
    &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glGenBuffers(1, &vertBuf);<br>
	  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glBindBuffer(GL_ARRAY_BUFFER, vertBuf);<br>
	  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(glm::vec3), vert.data(), GL_STATIC_DRAW);<br>
  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;Also, make vertexArray like below :<br>
    &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glGenVertexArrays(1, &vertArray);<br>
  	&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glBindVertexArray(vertArray);<br>
	  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glEnableVertexAttribArray(0);<br>
	  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glBindBuffer(GL_ARRAY_BUFFER, vertBuf);<br>
	  &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);<br><br>
-void render (GLFWwindow* window)<br>
  &nbsp; &nbsp; &nbsp; &nbsp;Easy to render because all the informations of vertices and primitives are in the global variable, and each is binded at init function
  &nbsp; &nbsp; &nbsp; &nbsp;Load program's ID : glUseProgram(program.programID)<br>
  &nbsp; &nbsp; &nbsp; &nbsp;Bind vertexArray and buffers
  &nbsp; &nbsp; &nbsp; &nbsp;After Binding, draw elements : glDrawElements(GL_TRIANGLES, 3*howMuchTriUseForCircle, GL_UNSIGNED_INT, 0);
  
    
  
