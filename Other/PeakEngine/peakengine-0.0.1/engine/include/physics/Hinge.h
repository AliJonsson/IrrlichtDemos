/*
Copyright (C) 2008  Mathias Gottschlag

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in the
Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _HINGE_H_
#define _HINGE_H_

#include "physics/Joint.h"
#include "core/Vector3D.h"

//tolua_begin
namespace peak
{
	/**
	 * \brief Hinge joint with one axis
	 */
	class Hinge: public Joint
	{
		public:
			Hinge();
			virtual ~Hinge();
			
			virtual bool init(World *world);
			
			/**
			 * \brief Sets the anchor of the hinge.
			 *
			 * The anchor is the point which will be always the same on both
			 * attached bodies.
			 * \param anchor New anchor
			 */
			void setAnchor(Vector3D anchor);
			/**
			 * \brief Sets the axis around which the hinge rotates.
			 * \param axis New axis
			 */
			void setAxis(Vector3D axis);
		private:
			//tolua_end
			//tolua_begin
	};
}
//tolua_end

#endif

