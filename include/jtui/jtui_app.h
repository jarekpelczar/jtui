#ifndef _JTUI_APP_H_
#define _JTUI_APP_H_

#include <cstdio>
#include <array>
#include <memory>

namespace jtui {

class Application: public Display {
public:
	Application(unsigned int width, unsigned int height, int outputFd = 1);

	void resize(unsigned int newWidth, unsigned int newHeight);

private:
	unsigned int		_width;
	unsigned int		_height;
};

}  // namespace jtui

#endif /* _JTUI_APP_H_ */
