#include<iostream>
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"CVector.h"
#include<fstream>
#include<sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include"camera.h"
#include"graph.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
using namespace std;






Camera camera;//相机

glm::mat4 proj = glm::mat4(1.0f);//透视投影矩阵
glm::mat4 view = glm::mat4(1.0f);//观察矩阵
glm::mat4* model;//模型矩阵
bool sign_2;//判断是否按了‘2’
bool sign_1;
GLFWwindow* window;
GLuint  program, Texture;
GLuint* vao;
CreateGraph graph;//图形
float R = 0.0f;









GLFWwindow* GLInit(int width,int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "my first opengl", NULL, NULL);
	return window;
}
//窗口大小变化回调
void farmbuffer_size_callback(GLFWwindow* window,int width,int height) {
	cout << "size: " << width << "*" << height << endl;
	glViewport(0, 0, width, height);
}

//键盘消息回调(key:字母按键码，scancode：物理按键码，action：按下还是抬起，mods：是否有shift或ctrl）
void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods) {
	if(key==GLFW_KEY_ENTER) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if(key==GLFW_KEY_ESCAPE) 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (camera.firstMouse)
	{
		camera.lastX = xpos;
		camera.lastY = ypos;
		camera.firstMouse = false;
	}

	float xoffset = xpos - camera.lastX;
	float yoffset = camera.lastY - ypos;
	camera.lastX = xpos;
	camera.lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.yaw += xoffset;
	camera.pitch += yoffset;

	if (camera.pitch > 89.0f)
		camera.pitch = 89.0f;
	if (camera.pitch < -89.0f)
		camera.pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
	front.y = sin(glm::radians(camera.pitch));
	front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
	camera.cameraDirection = glm::normalize(front);
	camera.recomp();
}

void preparesinglebuffer() {


	graph.create();

	//VBO
	GLuint posVBO[5] = { 0 }, colorVBO[4] = { 0 }, Ebo[5] = { 0 };

	GLuint uvVBO = 0;


	glGenBuffers(5, posVBO);
	glGenBuffers(4, colorVBO);
	glGenBuffers(5, Ebo);
	glGenBuffers(1, &uvVBO);


	glBindBuffer(GL_ARRAY_BUFFER, posVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, graph.axis.postions_Size, graph.axis.postions, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, graph.axis.colors_Size, graph.axis.colors[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, graph.axis.indices_Size, graph.axis.indices, GL_STATIC_DRAW);



	glBindBuffer(GL_ARRAY_BUFFER, posVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, graph.diams.postions_Size, graph.diams.postions, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, graph.diams.colors_Size, graph.diams.colors[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, graph.diams.indices_Size, graph.diams.indices, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, posVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, graph.stages1.postions_Size, graph.stages1.postions, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, graph.stages1.colors_Size, graph.stages1.colors[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, graph.stages1.indices_Size, graph.stages1.indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, posVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, graph.stages2.postions_Size, graph.stages2.postions, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, graph.stages2.colors_Size, graph.stages2.colors[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, graph.stages2.indices_Size, graph.stages2.indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, posVBO[4]);
	glBufferData(GL_ARRAY_BUFFER, graph.scream.postions_Size, graph.scream.postions, GL_STATIC_DRAW);


	//glBindBuffer(GL_ARRAY_BUFFER, colorVBO[4]);
	//glBufferData(GL_ARRAY_BUFFER, graph.scream.colors_Size, graph.scream.colors[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[4]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, graph.scream.indices_Size, graph.scream.indices, GL_STATIC_DRAW);


	//纹理
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glBufferData(GL_ARRAY_BUFFER, graph.scream.uvs_Size, graph.scream.uvs, GL_STATIC_DRAW);

	//VAO



	glGenVertexArrays(5, vao);

	//VAO1
	glBindVertexArray(vao[1]);



	glBindBuffer(GL_ARRAY_BUFFER, posVBO[1]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[1]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[1]);

	//VAO0
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[0]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[0]);
	//VAO2
	glBindVertexArray(vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO[2]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[2]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[2]);
	//VAO3
	glBindVertexArray(vao[3]);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO[3]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[3]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[3]);
	//VAO4
	glBindVertexArray(vao[4]);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO[4]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[3]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo[4]);
}

////////shader编译////////
void prepareShader() {
	ifstream fvs;
	ifstream ffs;
	string vscode;
	string fscode;
	fvs.open("Shader/vertexShader.glsl",ios::in);
	ffs.open("Shader/fragmentShader.glsl",ios::in);
	if (!fvs.is_open()) {
		cout << "open error" << endl;
	}
	stringstream vss, fss;
	vss << fvs.rdbuf();
	fss << ffs.rdbuf();
	fvs.close();
	ffs.close();

	vscode = vss.str();
	fscode = fss.str();

	const char* vertexShaderSource = vscode.c_str();

	const char* fragmentShaderSource = fscode.c_str();


	//创建shader
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);


	int success = 0;
	char infoLog[1024];
	//给shader输入代码
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);


	



	//执行shader编译
	glCompileShader(vertex);
	//错误检查
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		cout << "ERROR:SHADER COMPILE ERROR --VERTEX" << "\n" << infoLog << endl;
	}


	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		cout << "ERROR:SHADER COMPILE ERROR --FRAGMENT" << "\n" << infoLog << endl;
	}

	//创建program
	program = 0;
	program = glCreateProgram();

	

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		cout << "ERROR:SHADER COMPILE ERROR --PROGRAM" << "\n" << infoLog << endl;
	}


	glUseProgram(program);
	GLuint modlLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modlLoc, 1, GL_FALSE, glm::value_ptr(model[0]));
	glUseProgram(0);


	//清理
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void prepareTexture() {
	//读取图片
	int Pic_width, Pic_height, channels;
	//反转y轴
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Textrues/pictrue1.png", &Pic_width, &Pic_height, &channels,STBI_rgb_alpha);
	if (data == nullptr) cout << "open Texture FILE error" << endl;
	else {
		//激活纹理对象
		glGenTextures(1, &Texture);
		//激活纹理单元
		glActiveTexture(GL_TEXTURE0);
		//绑定纹理对象单元
		glBindTexture(GL_TEXTURE_2D, Texture);

		//传输数据,开辟显存
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Pic_width, Pic_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		//纹理过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//纹理包裹
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u方向
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//v方向

	}
	
}

//绕任意轴的旋转
glm::mat4 RotateArbitraryLine(glm::vec3 v1, glm::vec3 v2, float theta)
{
	glm::mat4 rmatrix;
	float a = v1.x;
	float b = v1.y;
	float c = v1.z;

	glm::vec3 p1 = v2 - v1;
	glm::vec3 p = glm::normalize(p1);

	float u = p.x;
	float v = p.y;
	float w = p.z;

	float uu = u * u;
	float uv = u * v;
	float uw = u * w;
	float vv = v * v;
	float vw = v * w;
	float ww = w * w;
	float au = a * u;
	float av = a * v;
	float aw = a * w;
	float bu = b * u;
	float bv = b * v;
	float bw = b * w;
	float cu = c * u;
	float cv = c * v;
	float cw = c * w;

	float costheta = glm::cos(theta);
	float sintheta = glm::sin(theta);

	rmatrix[0][0] = uu + (vv + ww) * costheta;
	rmatrix[0][1] = uv * (1 - costheta) + w * sintheta;
	rmatrix[0][2] = uw * (1 - costheta) - v * sintheta;
	rmatrix[0][3] = 0;

	rmatrix[1][0] = uv * (1 - costheta) - w * sintheta;
	rmatrix[1][1] = vv + (uu + ww) * costheta;
	rmatrix[1][2] = vw * (1 - costheta) + u * sintheta;
	rmatrix[1][3] = 0;

	rmatrix[2][0] = uw * (1 - costheta) + v * sintheta;
	rmatrix[2][1] = vw * (1 - costheta) - u * sintheta;
	rmatrix[2][2] = ww + (uu + vv) * costheta;
	rmatrix[2][3] = 0;

	rmatrix[3][0] = (a * (vv + ww) - u * (bv + cw)) * (1 - costheta) + (bw - cv) * sintheta;
	rmatrix[3][1] = (b * (uu + ww) - v * (au + cw)) * (1 - costheta) + (cu - aw) * sintheta;
	rmatrix[3][2] = (c * (uu + vv) - w * (au + bv)) * (1 - costheta) + (av - bu) * sintheta;
	rmatrix[3][3] = 1;

	return rmatrix;
}

////////渲染////////
void render() {
	//画面清理
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//绑定program
	glUseProgram(program);
	view = camera.CameraMove(0.1f, window);

	if (sign_2) model[sign_2] = glm::rotate(model[0], R+=0.1f, glm::vec3(0.0f, 0.1f, 0.0f));//旋转
	else model[sign_2] = glm::mat4(1.0f);

	GLuint sign = glGetUniformLocation(program, "sign");
	glUniform1i(sign, 0);

	//A
	glBindVertexArray(vao[1]);
	for(int i= 0; i< 29 ; i++){
		if (sign_2) model[sign_2] = glm::rotate(model[0], R, glm::vec3(0.0f, 0.1f, 0.0f));//旋转
		else model[sign_2] = glm::mat4(1.0f);
		//model[sign_2] = RotateArbitraryLine(glm::vec3(graph.diamsPositions[i].x, 12.0f, graph.diamsPositions[i].z), glm::vec3(graph.diamsPositions[i].x, 0.0f, graph.diamsPositions[i].z), graph.diamsPositions[i].w);
		model[sign_2] = glm::translate(model[sign_2], glm::vec3(graph.diamsPositions[i].x, graph.diamsPositions[i].y, graph.diamsPositions[i].z));

		GLuint transformLoc = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model[sign_2]));



		GLuint projLoc = glGetUniformLocation(program, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		GLuint viewLoc = glGetUniformLocation(program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//绑定vao

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
	}
	model[0] = glm::mat4(1.0f);
	GLuint transformLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model[0]));

	//坐标轴
	glBindVertexArray(vao[0]);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);


	if ((glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) && sign_1) {
		sign_1 = 0;
	}
	else if ((glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) || sign_1) {
		sign_1 = 1;
	}
	else sign_1 = 0;
	GLuint colorVBO[2] = { 0 };
	glGenBuffers(2, colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, graph.stages1.colors_Size, graph.stages1.colors[sign_1], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, graph.stages2.colors_Size, graph.stages2.colors[sign_1], GL_STATIC_DRAW);
	glBindVertexArray(vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[0]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(vao[3]);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO[1]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	if (sign_2) model[sign_2] = glm::rotate(model[0], R, glm::vec3(0.0f, 0.1f, 0.0f));//旋转
	else model[sign_2] = glm::mat4(1.0f);
	//B1
	glBindVertexArray(vao[2]);
	for (int i = 0; i < 90; i++) {
		if (sign_2) model[sign_2] = glm::rotate(model[0], R, glm::vec3(0.0f, 0.1f, 0.0f));//旋转
		else model[sign_2] = glm::mat4(1.0f);
		model[sign_2] = glm::translate(model[sign_2], glm::vec3(graph.stage1Positions[i].x, graph.stage1Positions[i].y, graph.stage1Positions[i].z));
		GLuint transformLoc = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model[sign_2]));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
	}


	//B2
	glBindVertexArray(vao[3]);
	for (int i = 0; i < 60; i++) {
		if (sign_2) model[sign_2] = glm::rotate(model[0], R, glm::vec3(0.0f, 0.1f, 0.0f));//旋转
		else model[sign_2] = glm::mat4(1.0f);
		model[sign_2] = glm::translate(model[sign_2], glm::vec3(graph.stage2Positions[i].x, graph.stage2Positions[i].y, graph.stage2Positions[i].z));
		GLuint transformLoc = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model[sign_2]));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
	}
	//一块屏幕
	sign = glGetUniformLocation(program, "sign");
	glUniform1i(sign, 1);
	GLuint unLoc = glGetUniformLocation(program, "sampler");
	glUniform1i(unLoc, 0);

	glUniform1i(sign, 1);
	glBindVertexArray(vao[4]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

}
int main(int argc,char* argv[]) {
	vao = new GLuint[5];
	model = new glm::mat4[2];
	model[0] = glm::mat4(1.0f);//固定状态
	model[1] = glm::mat4(1.0f);//旋转状态
	sign_1=sign_2 = 0;
	int width = 1800, height = 1000;
	window=GLInit(width,height);//初始化


	proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	//连接窗口
	glfwMakeContextCurrent(window);



	//窗口大小变化
	glfwSetFramebufferSizeCallback(window, farmbuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	//键盘变化
	glfwSetKeyCallback(window, key_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		return -1;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//设置视口
	glViewport(0, 0, 1800, 1000);
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	glLineWidth(6);
	prepareShader();//shader编译
	preparesinglebuffer();//渲染
	prepareTexture();
	//窗口循环
	while (!glfwWindowShouldClose(window)) {
		if ((glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) && sign_2) sign_2 = 0;
		else if ((glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) || sign_2) sign_2 = 1;

		//切换双缓存
		glfwSwapBuffers(window);
		//消息监听
		glfwPollEvents();
		//绘制
		render();
	}
	
	//退出清理
	glfwTerminate();
	return 0;
}