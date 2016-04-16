#include "stdafx.h"
#include "GSWndSDL.h"

GSWndSDL::GSWndSDL() {

}

GSWndSDL::~GSWndSDL() {

}

bool GSWndSDL::Create(const string& title, int w, int h) {

}

bool GSWndSDL::Attach(void* handle, bool managed) {

}

void GSWndSDL::Detach() {

}

void *GSWndSDL::GetDisplay() {
	return NULL;
}

void *GSWndSDL::GetHandle() {
	return NULL;
}

GSVector4i GSWndSDL::GetClientRect() {
	return GSVector4i(0, 0, 640, 480);
}

bool GSWndSDL::SetWindowText(const char *title) {
	SDL_WM_SetCaption(title, NULL);
}

void GSWndSDL::AttachContext() {

}

void GSWndSDL::DetachContext() {

}

void GSWndSDL::Show() {

}

void GSWndSDL::Hide() {

}

void GSWndSDL::HideFrame() {

}

void GSWndSDL::Flip() {

}

void GSWndSDL::SetVSync(bool enable) {

}
