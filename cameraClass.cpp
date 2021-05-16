enum Camera_Movement{FORWARD, BACKWARD, LEFT, RIGHT};
const float YAW		= -90.0f;
const float PITCH	= 0.0f;
const float SPEED	= 2.5f;
const float SENSITIVITY	= 0.1f;
const float ZOOM	= 45.0f;

class Camera{
	private:
		//glm::vec3 target;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		//float x_offset;
		//float y_offset;
		float yaw;
		float pitch;
		float movementSpeed;
		float mouseSensitivity;
		float zoom;
		void updateCameraVectors(){
			glm::vec3 Front;
			Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			Front.y = sin(glm::radians(pitch));
			Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			front = glm::normalize(Front);
			right = glm::normalize(glm::cross(front, up));
			up = glm::normalize(glm::cross(right, front)); 
			}
	public:
		glm::vec3 position;
		Camera (glm::vec3 camPos) : position(camPos), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {
			yaw			= YAW;
			pitch			= PITCH;
			movementSpeed		= SPEED;
			mouseSensitivity	= SENSITIVITY;
			zoom			= ZOOM;
			updateCameraVectors();
		}

		glm::mat4 getViewMatrix(){
			return glm::lookAt(position, position + front, up);
		}

		void processKeyboard(Camera_Movement direction, float deltaTime){
			float velocity = movementSpeed * deltaTime;
			if (direction == FORWARD)
				position += front * velocity;
			if (direction == BACKWARD)
				position -= front * velocity;
			if (direction == LEFT)
				position -= right * velocity;
			if (direction == RIGHT)
				position += right * velocity;
		}
		void processMouse(float x_offset, float y_offset, GLboolean constrainPitch = true){

			x_offset	*= mouseSensitivity;
			y_offset	*= mouseSensitivity;
			yaw		+= x_offset;
			pitch		+= y_offset;
			std::cout << "YAW " << yaw << std::endl;
			std::cout << "PITCH " << pitch << std::endl;

			if(constrainPitch){
				if(pitch > 89.0f)
					pitch = 89.0f;
				if(pitch < -89.0f)
					pitch = -89.0f;
			}
			updateCameraVectors();
		}
		void processScroll(float y_offset){
		        if (zoom >= 1.0f && zoom <= 45.0f)
				zoom -= y_offset;
			if (zoom <= 1.0f)
				zoom = 1.0f;
			if (zoom >= 45.0f)
				zoom = 45.0f;
		}
};			
