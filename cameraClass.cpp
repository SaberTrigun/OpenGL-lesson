enum Camera_Movement {FORWARD, BACKWARD, LEFT, RIGHT};

const float YAW		= -90.0f;
const float PITCH	= 0.0f;
const float SPEED	= 2.5f;
const float SENSITIVITY	= 0.1f;
const float ZOOM	= 45.0f;

class Camera{
	private:
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;
		
		float yaw;
		float pitch;

		float movementSpeed;
		float mouseSensitivity;
		float zoom;
		
		void UpdateCameraVectors(){
			glm::vec3 Front;
			Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			Front.y = sin(glm::radians(pitch));
			Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			front = glm::normalize(Front);
			
			right	= glm::normalize(glm::cross(front, worldUp));
			up	= glm::normalize(glm::cross(right, front));
		}
	public:
		glm::vec3 position;
		Camera (glm::vec3 cameraPosition ) : position(cameraPosition), front(glm::vec3(0.0f, 0.0f, -1.0f)), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)){
			yaw			= YAW;
			pitch			= PITCH;
			movementSpeed		= SPEED;
			mouseSensitivity	= SENSITIVITY;
			zoom			= ZOOM;
			UpdateCameraVectors();	
		}

		glm::mat4 GetViewMatrix(){
			return glm::lookAt(position, position + front, up);
		}
		// Функция для клавиатуры
		void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
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
		// Функция для мыши
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
			xoffset *= mouseSensitivity;
			yoffset *= mouseSensitivity;

			yaw	+= xoffset;
			pitch	+= yoffset;

			if (constrainPitch){
				if (pitch > 89.0f)
					pitch = 89.0f;
				if (pitch < -89.0f)
					pitch = -89.0f;
			}
			UpdateCameraVectors();
		}
		
		// Функция для скролинга
		void ProcessMouseScroll(float yoffset) {
			if (zoom >= 1.0f && zoom <= 45.0f)
				zoom -= yoffset;
			if (zoom <= 1.0f)
				zoom = 1.0f;
			if (zoom >= 45.0f)
				zoom = 45.0f;
		}
};

