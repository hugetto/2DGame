/*
    sdlgui/common.cpp -- Basic initialization and utility routines

    Based on NanoGUI by Wenzel Jakob <wenzel@inf.ethz.ch>.
    Adaptation for SDL by Dalerank <dalerankn8@gmail.com>

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include "pch.h"
#include <sdlgui/screen.h>
#if defined(_WIN32)
#include <windows.h>
#include <Commdlg.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <sdlgui/nanovg.h>

#include <map>
#include <array>
#include <thread>
#include <chrono>
#include <iostream>

#if !defined(_WIN32)
    #include <locale.h>
    #include <signal.h>
    #include <sys/dir.h>
#endif

NAMESPACE_BEGIN(sdlgui)

NVGcolor Color::toNvgColor() const {
  return reinterpret_cast<const NVGcolor &>(this->_d);
}

extern std::map<SDL_Window *, Screen *> __sdlgui_screens;

PntRect srect2pntrect(const SDL_Rect& srect)
{
  return{ srect.x, srect.y, srect.x + srect.w, srect.y + srect.h };
}

SDL_Rect pntrect2srect(const PntRect& frect)
{
  return{ frect.x1, frect.y1, frect.x2 - frect.x1, frect.y2 - frect.y1 };
}

SDL_Rect clip_rects(SDL_Rect af, const SDL_Rect& bf)
{
  PntRect a{ af.x, af.y, af.x + af.w, af.y + af.h };
  PntRect b{ bf.x, bf.y, bf.x + bf.w, bf.y + bf.h };
  if (a.x1 < b.x1)
    a.x1 = b.x1;
  if (a.y1 < b.y1)
    a.y1 = b.y1;
  if (b.x2 < a.x2)
    a.x2 = b.x2;
  if (b.y2 < a.y2)
    a.y2 = b.y2;

  return { a.x1, a.y1, a.x2 - a.x1, a.y2 - a.y1 };
}

PntRect clip_rects(PntRect a, const PntRect& b)
{
  if (a.x1 < b.x1)
    a.x1 = b.x1;
  if (a.y1 < b.y1)
    a.y1 = b.y1;
  if (b.x2 < a.x2)
    a.x2 = b.x2;
  if (b.y2 < a.y2)
    a.y2 = b.y2;

  return a;
}

SDL_Color Color::toSdlColor() const
{
  SDL_Color color{ r() * 255, g() * 255, b() * 255, a() * 255 };
  return color;
}

std::array<char, 8> utf8(int c) {
    std::array<char, 8> seq;
    int n = 0;
    if (c < 0x80) n = 1;
    else if (c < 0x800) n = 2;
    else if (c < 0x10000) n = 3;
    else if (c < 0x200000) n = 4;
    else if (c < 0x4000000) n = 5;
    else if (c <= 0x7fffffff) n = 6;
    seq[n] = '\0';
    switch (n) {
        case 6: seq[5] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x4000000;
        case 5: seq[4] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x200000;
        case 4: seq[3] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x10000;
        case 3: seq[2] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x800;
        case 2: seq[1] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0xc0;
        case 1: seq[0] = c;
    }
    return seq;
}

void Object::decRef(bool dealloc) const noexcept {
    --m_refCount;
    if (m_refCount == 0 && dealloc) {
        delete this;
    } else if (m_refCount < 0) {
        fprintf(stderr, "Internal error: Object reference count < 0!\n");
        abort();
    }
}

Object::~Object() { }

NAMESPACE_END(sdlgui)

