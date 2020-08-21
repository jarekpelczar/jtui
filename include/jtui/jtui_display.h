#ifndef _JTUI_DISPLAY_H_
#define _JTUI_DISPLAY_H_

#include <sys/types.h>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <unistd.h>
#include <string_view>

namespace jtui {

enum class Color {
	Black = 30,
	Red = 31,
	Green = 32,
	Yellow = 33,
	Blue = 34,
	Magenta = 35,
	Cyan = 36,
	White = 37,
	BrightBlack = 90,
	BrightRed = 91,
	BrightGreen = 92,
	BrightYellow = 93,
	BrightBlue = 94,
	BrightMagenta = 95,
	BrightCyan = 96,
	BrightWhite = 97
};

enum class ClearMode {
	FromCursorToEnd = 0,
	FromCursorToBeginning = 1,
	EntireScreen = 2,
	ResetAll = 3
};

enum class LineClearMode {
	FronCursorToEnd = 0, FrontCursorToStart = 1, EntireLine = 2
};

enum class DisplayAttribute {
	Reset = 0,
	Bold = 1,
	Faint = 2,
	Italic = 3,
	Underline = 4,
	SlowBlink = 5,
	RapidBlink = 6,
	ReverseVideo = 7,
	CrossedOut = 9,
	NotItalic = 22,
	UnderlineOff = 24,
	BlinkOff = 25
};

class Display {
public:
	constexpr Display(int fd = 1) noexcept :
			_fd(fd) {
	}

	void setBackgroundColor(Color color) const noexcept;
	void setForegroundColor(Color color) const noexcept;
	void setColor(Color fgColor, Color bgColor) const noexcept;
	void setForegroundColor(uint8_t r, uint8_t g, uint8_t b) const noexcept;
	void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b) const noexcept;
	void cursorUp(unsigned int dy = 1) const noexcept;
	void cursorDown(unsigned int dy = 1) const noexcept;
	void cursoLeft(unsigned int dx = 1) const noexcept;
	void cursoRight(unsigned int dx = 1) const noexcept;
	void gotoXY(unsigned int x, unsigned int y) const noexcept;
	void nextLinesDown(unsigned int dy = 1) const noexcept;
	void previousLinesUp(unsigned int dy = 1) const noexcept;
	void clear(ClearMode mode) const noexcept;
	void clearLine(LineClearMode mode) const noexcept;
	void setAttribute(DisplayAttribute attr) const noexcept;
	void setApplicationKeypad() const noexcept;
	void setNormalKeypad() const noexcept;
	void drawText(const std::string_view &text) const noexcept;
	void drawRepeated(uint8_t value, size_t count) const noexcept;
	void drawRect(uint8_t value, size_t width, size_t height) const noexcept;

private:
	int _fd;
};

inline void Display::setBackgroundColor(Color color) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%um", (unsigned int) color + 10);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::setForegroundColor(Color color) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%um", (unsigned int) color);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::setColor(Color fgColor, Color bgColor) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%u;%um", (unsigned int) fgColor,
			(unsigned int) bgColor + 10);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::setForegroundColor(uint8_t r, uint8_t g,
		uint8_t b) const noexcept {
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "\x1B[38;2;%u;%u;%um", r, g, b);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::setBackgroundColor(uint8_t r, uint8_t g,
		uint8_t b) const noexcept {
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "\x1B[48;2;%u;%u;%um", r, g, b);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::cursorUp(unsigned int dy) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%uA", dy);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::cursorDown(unsigned int dy) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%uB", dy);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::cursoLeft(unsigned int dx) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%uD", dx);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::cursoRight(unsigned int dx) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%uC", dx);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::gotoXY(unsigned int x, unsigned int y) const noexcept {
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "\x1B[%u;%uH", y + 1, x + 1);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::nextLinesDown(unsigned int dy) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%uE", dy);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::previousLinesUp(unsigned int dy) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%uF", dy);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::clear(ClearMode mode) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%uJ", (unsigned int) mode);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::clearLine(LineClearMode mode) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%uK", (unsigned int) mode);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::setAttribute(DisplayAttribute attr) const noexcept {
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "\x1B[%um", (unsigned int) attr);
	if (::write(_fd, buffer, strlen(buffer))) {
	}
}

inline void Display::setApplicationKeypad() const noexcept {
	if (::write(_fd, "\x1B=", 2)) {
	}
}

inline void Display::setNormalKeypad() const noexcept {
	if (::write(_fd, "\x1B>", 2)) {
	}
}

inline void Display::drawText(const std::string_view &text) const noexcept {
	if (::write(_fd, text.data(), text.size())) {
	}
}

inline void Display::drawRepeated(uint8_t value, size_t count) const noexcept {
	uint8_t buffer[512];
	memset(buffer, value, std::min(count, sizeof(buffer)));
	while (count > 0) {
		if (::write(_fd, buffer, std::min(count, sizeof(buffer)))) {
		}
		count -= std::min(count, sizeof(buffer));
	}
}

inline void Display::drawRect(uint8_t value, size_t width,
		size_t height) const noexcept {
	while (height-- > 0) {
		drawRepeated(value, width);
		cursoLeft(width);
	}
}

}  // namespace jtui

#endif /* _JTUI_DISPLAY_H_ */
