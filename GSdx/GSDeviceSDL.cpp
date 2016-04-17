/*
 *	Copyright (C) 2007-2009 Gabest
 *	http://www.gabest.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "stdafx.h"
#include "GSDeviceSDL.h"
#include <SDL_syswm.h>

static GLuint texid, listid;

GSDeviceSDL::GSDeviceSDL()
	: m_free_window(false)
	, m_window(NULL)
{
	SDL_Init(SDL_INIT_VIDEO);
}

GSDeviceSDL::~GSDeviceSDL()
{
}

bool GSDeviceSDL::Create(GSWnd* wnd)
{
	if (m_window == NULL) {
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);

		m_free_window = true;

		m_window = SDL_SetVideoMode(640 * 2, 480 * 2, 32,
						SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);
	}

	return GSDeviceSW::Create(wnd);
}

bool GSDeviceSDL::Reset(int w, int h)
{
	if(!GSDeviceSW::Reset(w, h))
	{
		return false;
	}

	delete m_backbuffer;

	m_backbuffer = new GSDummyTexture(w, h);

	{
		if (m_window) {
			SDL_SysWMinfo info;
			SDL_VERSION(&info.version);
//			if (SDL_GetWMInfo(&info) == 1) {
//				printf("Window %lu\n", info.info.x11.window);
//			}
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);

		m_window = SDL_SetVideoMode(w * 2, h * 2, 32,
						SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glGenTextures(1, &texid);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, NULL);

		// Gen the display list
		listid = glGenLists(1);
		glNewList(listid, GL_COMPILE);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3ub(255, 255, 255);

		glBegin(GL_QUADS);

		glTexCoord2f(0, 0);
		glVertex2f(-1, 1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, -1);

		glTexCoord2f(1, 1);
		glVertex2f(1, -1);

		glTexCoord2f(1, 0);
		glVertex2f(1, 1);

		glEnd();

		glEndList();
	}

	return true;
}

void GSDeviceSDL::Present(GSTexture* st, GSTexture* dt, const GSVector4& dr, int shader)
{
	ASSERT(dt == m_backbuffer); // ignore m_backbuffer

	const GSVector2i size = st->GetSize();

	if(m_backbuffer != NULL)
	{
		if(m_backbuffer->GetSize().x != size.x ||
			m_backbuffer->GetSize().y != size.y)
		{
			delete m_backbuffer;
			m_backbuffer = NULL;
		}
	}

	if (!m_backbuffer) {
		m_backbuffer = new GSDummyTexture(size.x, size.y);
	}

	GSTexture::GSMap sm;

	if(st->Map(sm, NULL))
	{
		const uint16_t w = size.x;
		const uint16_t h = size.y;
		// Direct tex upload, it's already in the correct format
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA,
					GL_UNSIGNED_BYTE,
					sm.bits);

		st->Unmap();
	}

	glCallList(listid);
}

void GSDeviceSDL::Flip()
{
	SDL_GL_SwapBuffers();
}
