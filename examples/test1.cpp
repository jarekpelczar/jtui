#include <jtui/jtui.h>

int main()
{
	jtui::Application app(80, 50);
	jtui::RenderBuffer renderBuffer(80, 50);

	renderBuffer.setBackgroundColor(jtui::Color::Blue);
	renderBuffer.setForegroundColor(jtui::Color::White);
	renderBuffer.drawText(0, 1, "test string view");

	renderBuffer.renderTo(app);
}
