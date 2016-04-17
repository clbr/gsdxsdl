#include "stdafx.h"
#include "GSWndSDL.h"

static Display *disp;
static char oldtitle[PATH_MAX];

GSWndSDL::GSWndSDL() {
	disp = XOpenDisplay(NULL);
	m_managed = true;
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
	return disp;
}

void *GSWndSDL::GetHandle() {
	return NULL;
}

GSVector4i GSWndSDL::GetClientRect() {
	SDL_Surface *s = SDL_GetVideoSurface();

	return GSVector4i(0, 0, s->w, s->h);
}

bool GSWndSDL::SetWindowText(const char *title) {
	if (strcmp(oldtitle, title)) {
		strcpy(oldtitle, title);
		SDL_WM_SetCaption(title, NULL);
	}
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
