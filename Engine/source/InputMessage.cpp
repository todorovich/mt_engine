#include "InputMessage.hpp"

#include "engine.hpp"

using namespace mt;

 void InputMessage::_MouseMove(__int32 x, __int32 y)
{
	engine::get_input_handler()._MouseMove(x, y);
}

void InputMessage::_MouseDown(WPARAM btnState)
{
	engine::get_input_handler()._MouseDown(btnState);
}

void InputMessage::_MouseUp(WPARAM btnState)
{
	engine::get_input_handler()._MouseUp(btnState);
}

void InputMessage::_KeyDown(WPARAM vk_key)
{
	engine::get_input_handler()._KeyDown(vk_key);
}

void InputMessage::_KeyUp(WPARAM vk_key)
{
	engine::get_input_handler()._KeyUp(vk_key);
}