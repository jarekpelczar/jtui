#include <jtui/jtui.h>

namespace jtui {

RenderBuffer::RenderBuffer(unsigned int width, unsigned int height) :
	_cells(width * height),
	_width(width),
	_height(height)
{
	clear();
}

void RenderBuffer::resize(unsigned int width, unsigned int height)
{
	_cells.resize(width * height);
	_width = width;
	_height = height;
	clear();
}

void RenderBuffer::clear() noexcept
{
	_backgroundStyle = _drawStyle;

	for(auto& cell : _cells) {
		cell = _drawStyle;
	}
}

void RenderBuffer::setBackgroundColor(Color color) noexcept {
	_drawStyle._bgColor = (uint32_t) color | 0x80000000;
}

void RenderBuffer::setForegroundColor(Color color) noexcept {
	_drawStyle._fgColor = (uint32_t) color | 0x80000000;
}

void RenderBuffer::setColor(Color fgColor, Color bgColor) noexcept {
	_drawStyle._bgColor = (uint32_t) bgColor | 0x80000000;
	_drawStyle._fgColor = (uint32_t) fgColor | 0x80000000;
}

void RenderBuffer::setForegroundColor(uint8_t r, uint8_t g, uint8_t b) noexcept {
	_drawStyle._fgColor = r | (((uint32_t) g) << 8) | (((uint32_t) b) << 16);
}

void RenderBuffer::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b) noexcept {
	_drawStyle._bgColor = r | (((uint32_t) g) << 8) | (((uint32_t) b) << 16);
}

void RenderBuffer::setAttribute(DisplayAttribute attr) noexcept {
	_drawStyle._displayAttribute |= 1U << (unsigned int) attr;
}

void RenderBuffer::removeAttributes() noexcept {
	_drawStyle._displayAttribute = 0;
}

void RenderBuffer::drawText(int x, int y,
		const std::string_view &text) noexcept {
	if (x >= (int)_width)
		return;
	if (y >= (int)_height || y < 0)
		return;

	const char *src;
	size_t length;

	if (x < 0) {
		if (x + (int) text.size() <= 0) {
			return;
		} else {
			src = text.data() - x;
			length = text.data() + text.size() - src;
			x = 0;
		}
	} else {
		src = text.data();

		if (x + text.size() > _width) {
			length = _width - x;
		} else {
			length = text.size();
		}
	}

	Cell cell = _drawStyle;

	for (size_t i = 0; i < length; ++i) {
		cell._character = *src++;
		_cells[y * _height + x + i] = cell;
	}
}

void RenderBuffer::renderTo(Display& display)
{
	display.setAttribute(DisplayAttribute::Reset);
	if (_backgroundStyle._bgColor & 0x80000000) {
		display.setBackgroundColor((Color) (_backgroundStyle._bgColor & 0xff));
	} else {
		display.setBackgroundColor(_backgroundStyle._bgColor & 0xff,
				(_backgroundStyle._bgColor >> 8) & 0xff,
				(_backgroundStyle._bgColor >> 16) & 0xff);
	}

	if (_backgroundStyle._fgColor & 0x80000000) {
		display.setForegroundColor((Color) (_backgroundStyle._fgColor & 0xff));
	} else {
		display.setForegroundColor(_backgroundStyle._fgColor & 0xff,
				(_backgroundStyle._fgColor >> 8) & 0xff,
				(_backgroundStyle._fgColor >> 16) & 0xff);
	}
	display.clear(ClearMode::EntireScreen);

	Cell *cell = _cells.data();
	bool attributeChanged = true;
	bool needGoto = true;
	Cell lastAttribute = *cell;

	for (unsigned int y = 0; y < _height; ++y) {
		for (unsigned int x = 0; x < _width; ++x, ++cell) {
			if (!cell->_character) {
				needGoto = true;
				continue;
			}

			if (!attributeChanged) {
				if (lastAttribute._bgColor != cell->_bgColor
						|| lastAttribute._fgColor != cell->_fgColor
						|| lastAttribute._displayAttribute
								!= cell->_displayAttribute) {
					attributeChanged = true;
				}
			}

			if (attributeChanged) {
				display.setAttribute(DisplayAttribute::Reset);
				if (cell->_bgColor & 0x80000000) {
					display.setBackgroundColor((Color) (cell->_bgColor & 0xff));
				} else {
					display.setBackgroundColor(cell->_bgColor & 0xff,
							(cell->_bgColor >> 8) & 0xff,
							(cell->_bgColor >> 16) & 0xff);
				}

				if (cell->_fgColor & 0x80000000) {
					display.setForegroundColor((Color) (cell->_fgColor & 0xff));
				} else {
					display.setForegroundColor(cell->_fgColor & 0xff,
							(cell->_fgColor >> 8) & 0xff,
							(cell->_fgColor >> 16) & 0xff);
				}
				lastAttribute = *cell;
			}

			if (needGoto) {
				display.gotoXY(x, y);
				needGoto = false;
			}

			display.drawText(
					std::string_view((const char*) &cell->_character, 1));
		}
	}
}

}  // namespace jtui
