#include "events/Event.h"
#include "Example.h"

HandlerListMap EventBus::s_handlers = HandlerListMap();

int main() {
	ExampleApp* example = new ExampleApp();
	example->run();
}

// TODO move glad.c
// TODO fix key