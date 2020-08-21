#ifndef _JTUI_RENDER_BUFFER_H_
#define _JTUI_RENDER_BUFFER_H_

#include <cstdint>
#include <vector>
#include <string_view>

namespace jtui {

class Display;

class RenderBuffer
{
public:
	RenderBuffer(unsigned int width, unsigned int height);

	void resize(unsigned int width, unsigned int height);
	void clear() noexcept;

	void setBackgroundColor(Color color) noexcept;
	void setForegroundColor(Color color) noexcept;
	void setColor(Color fgColor, Color bgColor) noexcept;
	void setForegroundColor(uint8_t r, uint8_t g, uint8_t b) noexcept;
	void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b) noexcept;
	void setAttribute(DisplayAttribute attr) noexcept;
	void removeAttributes() noexcept;

	void drawText(int x, int y, const std::string_view& text) noexcept;

	void renderTo(Display& display);

private:
	struct Cell {
		uint8_t _character = 0;
		uint32_t _displayAttribute = 0;
		uint32_t _fgColor = 0;
		uint32_t _bgColor = 0;
	};

	std::vector<Cell>		_cells;
	Cell					_backgroundStyle;
	Cell					_drawStyle;
	unsigned int			_width, _height;
};

}  // namespace jtui

#endif /* _JTUI_RENDER_BUFFER_H_ */
