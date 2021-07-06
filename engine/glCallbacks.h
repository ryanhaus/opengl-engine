enum class Callback { WinResize, MouseMove };

void callback_winResize(GLFWwindow* window, int width, int height);
void callback_mouseMove(GLFWwindow* window, double x, double y);