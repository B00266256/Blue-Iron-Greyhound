#include "Collisions.h"

//I was hoping to draw the bounding boxes
void Collisions::draw()
{
	GLuint VAO;
	// generate and set up a VAO for the mesh
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5,  0.5, -0.5, 1.0,
		-0.5,  0.5, -0.5, 1.0,
		-0.5, -0.5,  0.5, 1.0,
		0.5, -0.5,  0.5, 1.0,
		0.5,  0.5,  0.5, 1.0,
		-0.5,  0.5,  0.5, 1.0,
	};


	GLfloat colours[] = {
		0.0,  1.0,  0.0, 1.0,
		0.0,  1.0,  0.0, 1.0,
		0.0,  1.0,  0.0, 1.0,
		0.0,  1.0,  0.0, 1.0,
		0.0,  1.0,  0.0, 1.0,
		0.0,  1.0,  0.0, 1.0,
		0.0,  1.0,  0.0, 1.0,
		0.0,  1.0,  0.0, 1.0,
	};
	GLuint VBO;
	glGenBuffers(1, &VBO);



	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//pMeshBuffers[0] = VBO;

	// VBO for colour data
	if (colours != nullptr) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(GLfloat), colours, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		//pMeshBuffers[1] = VBO;
	}

	//glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	glm::mat4 modelview(1);
	modelview = glm::translate(modelview, glm::vec3(-5.0f, 0.0f, 60.0f));
	OpenglUtils::setUniformMatrix4fv(3, "modelview", glm::value_ptr(modelview));

	//vertexArrayMap.insert(pair<GLuint, GLuint *>(VAO, pMeshBuffers));

	glBindVertexArray(VAO);	// Bind mesh VAO
	glDrawElements(GL_LINES, 32, GL_INT, 0);	// draw VAO 
	glBindVertexArray(0);

	// VAO;
}



void Collisions::AABBtoAABB()
{
	
	glm::vec3 min1;
	glm::vec3 max1;
	glm::vec3 min2;
	glm::vec3 max2;


/*
	//attempt at rotating the bounding boxes and it doesnt work in the slightest

	//glm::mat4 identity(1);
	//glm::mat4 modelview(1);

	//float rotation = objects[0]->getCameraRotation();
	//glm::vec3 eye = objects[0]->getTranslation();
	//glm::vec3 at = glm::vec3(eye.x + 1.0f*std::sin(rotation*DEG_TO_RADIAN), eye.y, eye.z - 1.0f*std::cos(rotation*DEG_TO_RADIAN));
	//glm::vec3 up(glm::vec3(0.0f, 1.0f, 0.0f));

	//modelview = glm::lookAt(eye, at, up);
	//
	//modelview = glm::translate(modelview, objects[0]->getPosition());
*/



	//for every dynamic object check against all static objects for intersection. If true update the dynamic object.
	for (int i = 0; i < dynamicObjects.size(); i++)
	{

		//Pull out the stored min and max out for testing and apply position (dynamic objects positions change)
		min1 = dynMins[i] + dynamicObjects[i]->getPosition();
		max1 = dynMaxs[i] + dynamicObjects[i]->getPosition();
	
		for (int j = 0; j < staticObjects.size(); j++)
		{
			//Pull out the stored min and max out for testing
			min2 = staticMins[j];
			max2 = staticMaxs[j];

			bool collision = true;

			// Collision tests. if any tests are false then theres no intersection.
			if (max1.x < min2.x || min1.x > max2.x)
				collision = false;
			if (max1.y < min2.y || min1.y > max2.y)
				collision = false;
			if (max1.z < min2.z || min1.z > max2.z)
				collision = false;
		
			//Make a collision reaction if there is an intersection
			if (collision)
			{
				dynamicObjects[i]->setTranslation(dynamicObjects[i]->getTranslation() + glm::vec3(0.2, 0, 0));
				std::cout << "collision";
			}
			
			
		}
	}

	

}

void Collisions::addStaticObject(GameObject* object)
{
	staticObjects.push_back(object);

	staticMins.push_back((object->getMin() * object->getScaling()) + object->getPosition());
	staticMaxs.push_back((object->getMax() * object->getScaling()) + object->getPosition());
}

void Collisions::addDynamicObject(GameObject* object)
{
	dynamicObjects.push_back(object);

	glm::vec3 scaling = object->getScaling();

	dynMins.push_back((object->getMin() * scaling));
	dynMaxs.push_back((object->getMax() *scaling));
	

}