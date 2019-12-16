/*      _______   __   __   __   ______   __   __   _______   __   __
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/
 *
 * Copyright (c) 2004 - 2008 Olof Naess�n and Per Larsson
 *
 *
 * Per Larsson a.k.a finalman
 * Olof Naess�n a.k.a jansem/yakslem
 *
 * Visit: http://guichan.sourceforge.net
 *
 * License: (BSD)
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Guichan nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Original file: genericinput.hpp (guichan 0.8.1)
 * Modified 7.8.2008 Mathias Gottschlag
 */

#ifndef _GUIINPUT_H_
#define _GUIINPUT_H_

#include <queue>

#include "guichan/input.hpp"
#include "guichan/keyinput.hpp"
#include "guichan/mouseinput.hpp"
#include "guichan/platform.hpp"

namespace peak
{
    class Key;
    
    /**
     * \brief Implementation of a generic input for the menu system
     */
    class GUIInput: public gcn::Input
    {
    public:

        /**
         * Constructor.
         */
        GUIInput();

        /**
         * \brief Pushes a key pressed event.
         *
         * NOTE: If a special key is pressed, like the F1 key,
         *       the corresponding Guichan key value found
         *       in the enum in Key should be pushed as the
         *       unicode value.
         *
         * \param unicode The unicode value of the key. 
         */
        void pushKeyPressed(int unicode);

        /**
         * \brief Pushes a key released event.
         *
         * NOTE: If a special key is pressed, like the F1 key,
         *       the corresponding Guichan key value found
         *       in the enum in Key should be pushed as the
         *       unicode value.
         *
         * \param unicode The unicode value of the key. 
         */
        void pushKeyReleased(int unicode);
        
        /**
         * \brief Pushes a mouse button pressed event.
         *
         * \param x The x coordinate of the mouse event.
         * \param y The y coordinate of the mouse event.
         * \param button The button of the mouse event.
         */
        void pushMouseButtonPressed(int x, int y, int button);

        /**
         * \brief Pushes a mouse button released event.
         *
         * \param x The x coordinate of the mouse event.
         * \param y The y coordinate of the mouse event.
         * \param button The button of the mouse event.
         */
        void pushMouseButtonReleased(int x, int y, int button);
        
        /**
         * \brief Pushes a mouse wheel moved up event.
         *
         * \param x The x coordinate of the mouse event.
         * \param y The y coordinate of the mouse event.
         */
        void pushMouseWheelMovedUp(int x, int y);
        
        /**
         * \brief Pushes a mouse wheel moved down event.
         *
         * \param x The x coordinate of the mouse event.
         * \param y The y coordinate of the mouse event.
         */
        void pushMouseWheelMovedDown(int x, int y);

        /**
         * \brief Pushes a mouse moved event.
         *
         * \param x The x coordinate of the mouse event.
         * \param y The y coordinate of the mouse event.
         */
        void pushMouseMoved(int x, int y);

        
        // Inherited from Input

        virtual bool isKeyQueueEmpty();

        virtual gcn::KeyInput dequeueKeyInput();

        virtual bool isMouseQueueEmpty();

        virtual gcn::MouseInput dequeueMouseInput();

        virtual void _pollInput();

    protected:
        bool mLShiftPressed;
        bool mRShiftPressed;
        
        /**
         * Holds the key input queue.
         */
        std::queue<gcn::KeyInput> mKeyInputQueue;

        /**
         * Holds the mouse input queue.
         */
        std::queue<gcn::MouseInput> mMouseInputQueue;
    };
}

#endif

