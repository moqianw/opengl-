using namespace std;
#include<stdlib.h>
#include<iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Graph {
public:

	float* postions;
	int postions_Size;
	float** colors;
	int colors_Size;
	unsigned int* indices;
	int indices_Size;
	float* uvs;
	int uvs_Size;

};
class CreateGraph {
public:
	Graph axis;
	Graph diams;
	Graph stages1;
	Graph stages2;
	Graph scream;
	glm::vec4* diamsPositions;
	glm::vec4* stage1Positions;
	glm::vec4* stage2Positions;
	void create() {
		float postions0[] = {
			0.0f,0.0f,0.0f,
			13.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,
			0.0f,13.0f,0.0f,
			0.0f,0.0f,0.0f,
			0.0f,0.0f,13.0f
		};
		unsigned int indices0[] = {
			0,1,
			2,3,
			4,5

		};
		float colors0[] = {
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f
		};
		float postions[] = {
			-0.5f,0.0f,-0.05f,
			-0.5f,0.0f,0.05f,
			0.5f,0.0f,0.05f,
			0.5f,0.0f,-0.05f,
			-0.5f,12.0f,-0.05f,
			-0.5f,12.0f,0.05f,
			0.5f,12.0f,0.05f,
			0.5f,12.0f,-0.05f
		};

		float colors[] = {
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f
		};

		unsigned int indices[] = {
			0,1,5,
			0,5,4,
			0,4,7,
			0,7,3,
			0,3,1,
			1,3,2,
			4,5,7,
			5,6,7,
			1,6,5,
			1,2,6,
			3,7,6,
			3,6,2
		};


		diamsPositions = new glm::vec4[29];
		float r_A = 12.0f;//a区半径
		float p_A = 120.0 / 29.0;//偏转角度
		for (int i = 0; i < 29; i++) {
			diamsPositions[i].x = r_A * cos(glm::radians(p_A * (i+1) + 30.0f));
			diamsPositions[i].y = 0.0f;
			diamsPositions[i].z = -r_A * sin(glm::radians(p_A * (i+1) + 30.0f));
			diamsPositions[i].w = 60.0f-p_A * (i+1);
		}


		stage1Positions = new glm::vec4[90];
		int x = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 10; j++) {
				stage1Positions[x++] = glm::vec4(-4.0f + i, 0.0f, -9.0f + j, 0.0f);
			}
		}

		x = 0;
		stage2Positions = new glm::vec4[60];
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 4; j++) {
				stage2Positions[x++] = glm::vec4(-7.0f + i, 0.0f, 1.0f + j, 0.0f);
			}
		}

		float postions2[] =
		{
			-0.5f,0.0f,-0.5f,//0
			-0.5f,0.0f,0.5f,//1
			-0.5f,-5.0f,0.5f,//5

			-0.5f,0.0f,-0.5f,//0
			-0.5f,-5.0f,0.5f,//5
			-0.5f,-5.0f,-0.5f,//4

			-0.5f,0.0f,-0.5f,//0
			-0.5f,-5.0f,-0.5f,//4
			0.5f,-5.0f,-0.5f,//7

			-0.5f,0.0f,-0.5f,//0
			0.5f,-5.0f,-0.5f,//7
			0.5f,0.0f,-0.5f,//3

			-0.5f,0.0f,-0.5f,//0
			0.5f,0.0f,-0.5f,//3
			-0.5f,0.0f,0.5f,//1

			-0.5f,0.0f,0.5f,//1
			0.5f,0.0f,-0.5f,//3
			0.5f,0.0f,0.5f,//2

			-0.5f,-5.0f,-0.5f,//4
			-0.5f,-5.0f,0.5f,//5
			0.5f,-5.0f,-0.5f,//7

			-0.5f,-5.0f,0.5f,//5
			0.5f,-5.0f,0.5f,//6
			0.5f,-5.0f,-0.5f,//7

			-0.5f,0.0f,0.5f,//1
			0.5f,-5.0f,0.5f,//6
			-0.5f,-5.0f,0.5f,//5

			-0.5f,0.0f,0.5f,//1
			0.5f,0.0f,0.5f,//2
			0.5f,-5.0f,0.5f,//6

			0.5f,0.0f,-0.5f,//3
			0.5f,-5.0f,-0.5f,//7
			0.5f,-5.0f,0.5f,//6

			0.5f,0.0f,-0.5f,//3
			0.5f,-5.0f,0.5f,//6
			0.5f,0.0f,0.5f,//2
		};
		unsigned int indices1[] = {
			0,1,2,
			3,4,5,
			6,7,8,
			9,10,11,
			12,13,14,
			15,16,17,
			18,19,20,
			21,22,23,
			24,25,26,
			27,28,29,
			30,31,32,
			33,34,35
			
		};
		float colors2_1[] = {
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f
		};
		float colors2_2[] = {
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,

			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,

			0.5f,0.0f,0.5f,
			0.5f,0.0f,0.5f,
			0.5f,0.0f,0.5f,

			0.5f,0.0f,0.5f,
			0.5f,0.0f,0.5f,
			0.5f,0.0f,0.5f,

			1.0f,0.5f,0.0f,
			1.0f,0.5f,0.0f,
			1.0f,0.5f,0.0f,

			1.0f,0.5f,0.0f,
			1.0f,0.5f,0.0f,
			1.0f,0.5f,0.0f,

			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,

			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,

			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,

			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,

			1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f,

			1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f
		};

		float postions3[] =
		{
			-0.5f,0.0f,-0.5f,//0
			-0.5f,0.0f,0.5f,//1
			-0.5f,-3.0f,0.5f,//5

			-0.5f,0.0f,-0.5f,//0
			-0.5f,-3.0f,0.5f,//5
			-0.5f,-3.0f,-0.5f,//4

			-0.5f,0.0f,-0.5f,//0
			-0.5f,-3.0f,-0.5f,//4
			0.5f,-3.0f,-0.5f,//7

			-0.5f,0.0f,-0.5f,//0
			0.5f,-3.0f,-0.5f,//7
			0.5f,0.0f,-0.5f,//3

			-0.5f,0.0f,-0.5f,//0
			0.5f,0.0f,-0.5f,//3
			-0.5f,0.0f,0.5f,//1

			-0.5f,0.0f,0.5f,//1
			0.5f,0.0f,-0.5f,//3
			0.5f,0.0f,0.5f,//2

			-0.5f,-3.0f,-0.5f,//4
			-0.5f,-3.0f,0.5f,//5
			0.5f,-3.0f,-0.5f,//7

			-0.5f,-3.0f,0.5f,//5
			0.5f,-3.0f,0.5f,//6
			0.5f,-3.0f,-0.5f,//7

			-0.5f,0.0f,0.5f,//1
			0.5f,-3.0f,0.5f,//6
			-0.5f,-3.0f,0.5f,//5

			-0.5f,0.0f,0.5f,//1
			0.5f,0.0f,0.5f,//2
			0.5f,-3.0f,0.5f,//6

			0.5f,0.0f,-0.5f,//3
			0.5f,-3.0f,-0.5f,//7
			0.5f,-3.0f,0.5f,//6

			0.5f,0.0f,-0.5f,//3
			0.5f,-3.0f,0.5f,//6
			0.5f,0.0f,0.5f//2
		};
		float colors3_1[] = {
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f
		};
		float colors3_2[] = {
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,

			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,

			0.5f,0.0f,0.5f,
			0.5f,0.0f,0.5f,
			0.5f,0.0f,0.5f,

			0.5f,0.0f,0.5f,
			0.5f,0.0f,0.5f,
			0.5f,0.0f,0.5f,

			1.0f,0.5f,0.0f,
			1.0f,0.5f,0.0f,
			1.0f,0.5f,0.0f,

			1.0f,0.5f,0.0f,
			1.0f,0.5f,0.0f,
			1.0f,0.5f,0.0f,

			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,

			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,

			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,

			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,

			1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f,

			1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f
		};
		//A区
		diams.postions_Size = sizeof(postions);
		diams.colors_Size = sizeof(colors);
		diams.indices_Size = sizeof(indices);
		diams.postions = new float[sizeof(postions)/sizeof(postions[0])];
		copy(begin(postions), end(postions), diams.postions);
		diams.colors = new float* [1];
		diams.colors[0] = new float[sizeof(colors) / sizeof(colors[0])];
		copy(begin(colors), end(colors), diams.colors[0]);
		diams.indices = new unsigned int[sizeof(indices) / sizeof(indices[0])];
		copy(begin(indices), end(indices), diams.indices);


		//坐标轴
		axis.postions_Size = sizeof(postions0);
		axis.colors_Size = sizeof(colors0);
		axis.indices_Size = sizeof(indices0);
		axis.postions = new float[sizeof(postions0) / sizeof(postions0[0])];
		copy(begin(postions0), end(postions0), axis.postions);
		axis.colors=new float* [1];
		axis.colors[0] = new float[sizeof(colors0) / sizeof(colors0[0])];
		copy(begin(colors0), end(colors0), axis.colors[0]);
		axis.indices = new unsigned int[sizeof(indices0) / sizeof(indices0[0])];
		copy(begin(indices0), end(indices0), axis.indices);



		//B1
		stages1.postions_Size = sizeof(postions2);
		stages1.colors_Size = sizeof(colors2_1);
		stages1.indices_Size = sizeof(indices1);
		stages1.postions = new float[sizeof(postions2) / sizeof(postions2[0])];
		copy(begin(postions2), end(postions2), stages1.postions);
		stages1.colors= new float* [2];
		stages1.colors[0] = new float[sizeof(colors2_1) / sizeof(colors2_1[0])];
		copy(begin(colors2_1), end(colors2_1), stages1.colors[0]);
		stages1.colors[1] = new float[sizeof(colors2_2) / sizeof(colors2_2[0])];
		copy(begin(colors2_2), end(colors2_2), stages1.colors[1]);
		stages1.indices = new unsigned int[sizeof(indices1) / sizeof(indices1[0])];
		copy(begin(indices1), end(indices1), stages1.indices);

		//B2
		stages2.postions_Size = sizeof(postions3);
		stages2.colors_Size = sizeof(colors3_1);
		stages2.indices_Size = sizeof(indices1);
		stages2.postions = new float[sizeof(postions3) / sizeof(postions3[0])];
		copy(begin(postions2), end(postions2), stages2.postions);
		stages2.colors = new float* [2];
		stages2.colors[0] = new float[sizeof(colors3_1) / sizeof(colors3_1[0])];
		copy(begin(colors3_1), end(colors3_1), stages2.colors[0]);
		stages2.colors[1] = new float[sizeof(colors3_2) / sizeof(colors3_2[0])];
		copy(begin(colors3_2), end(colors3_2), stages2.colors[1]);
		stages2.indices = new unsigned int[sizeof(indices1) / sizeof(indices1[0])];
		copy(begin(indices1), end(indices1), stages2.indices);


		//一块屏幕

		float Sc_postions[] = {
			-10.0f,0.0f,0.0f,
			10.0f,0.0f,0.0f,
			-10.0f,20.0f,0.0f,
			10.0f,20.0f,0.0f
		};
		float Sc_uvs[] = {
			0.0f,0.0f,
			1.0f,0.0f,
			0.0f,1.0f,
			1.0f,1.0f
		};
		float Sc_indices[] = {
			0,1,2,
			2,1,3
		};
		scream.indices_Size = sizeof(Sc_indices);
		scream.uvs_Size = sizeof(Sc_uvs);
		scream.postions_Size = sizeof(Sc_postions);
		scream.indices = new unsigned int[sizeof(Sc_indices) / sizeof(Sc_indices[0])];
		copy(begin(Sc_indices), end(Sc_indices), scream.indices);
		scream.uvs = new float[sizeof(Sc_uvs) / sizeof(Sc_uvs[0])];
		copy(begin(Sc_uvs), end(Sc_uvs), scream.uvs);
		scream.postions = new float[sizeof(Sc_postions) / sizeof(Sc_postions[0])];
		copy(begin(Sc_postions), end(Sc_postions), scream.postions);
	}
};