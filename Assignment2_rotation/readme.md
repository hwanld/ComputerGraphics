<h2>Assignment2_Rotation</h2>

<b>-Goal : Rotate triangle with control the vertex file.</b>

-First, control the vertex file.

​	Make uniform mat3 rotation (means 3*3 matrix) with standard basis.

​	Make vec3 with multiply rotation and in_Position.

​	After that, make gl_Position = vec4 (p.xy, 1, 1);

-Second, control the render functions.

​	Make glm::mat3 which contains the information of rotation.

​		In this assignment, we have to rotate the object 5 degrees per frame.

​		Have to control this things with global variable.

​	After make matrix, send the information of matrix with using location = glGetUniformLocation (program.programID, "rotation"); glUniformMatrix3fv(location, 1, false, value_ptr(rotation));

