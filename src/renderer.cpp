#include "..\include\renderer.h"

void Renderer::drawMap(MapLoader* map){
	
	GLint lightPositionID = glGetUniformLocation(map->getMap()->ShaderID->id(), "light_position");
	GLint modelLoc = glGetUniformLocation(map->getMap()->ShaderID->id(), "model");
	GLint viewLoc = glGetUniformLocation(map->getMap()->ShaderID->id(), "view");
	GLint projLoc = glGetUniformLocation(map->getMap()->ShaderID->id(), "projection");
	GLint colourID = glGetUniformLocation(map->getMap()->ShaderID->id(), "testCol");


	glm::mat4 view = map->getPlayer()->getView();
	glm::mat4 projection = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, -100, 0)) * glm::scale(glm::mat4(1), glm::vec3(100.0f, 100.0f, 100.0f));


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(lightPositionID, map->getPlayer()->getPos().x, map->getPlayer()->getPos().y, map->getPlayer()->getPos().z);
	glUniform3f(colourID, 1.0F, 1.0F, 1.0F);


	///////////////////////////////////////////////////////////////////////////////


	glEnable(GL_TEXTURE_2D);
	glUseProgram(map->getMap()->ShaderID->id());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, map->getMap()->heightMap->id());
	glBindTexture(GL_TEXTURE_2D, map->getMap()->textureProgramID->id());

	glBindVertexArray(map->getMap()->VertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, map->getMap()->VertexBuffer);
	GLint positionID = glGetAttribLocation(map->getMap()->ShaderID->id(), "position");
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(positionID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, map->getMap()->ElementBuffer);



	glDrawElements(GL_TRIANGLES, map->getMap()->indexes.size(), GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(0);
}
