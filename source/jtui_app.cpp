#include <jtui/jtui.h>
#include <sys/poll.h>
#include <termios.h>

namespace jtui {

Application::Application(unsigned int width, unsigned int height, int outputFd) :
	Display(outputFd),
	_width(width),
	_height(height)
{

}

void Application::resize(unsigned int newWidth, unsigned int newHeight)
{
	_width = newWidth;
	_height = newHeight;
}

}  // namespace jtui
