/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated April 5, 2025. Replaces all prior versions.
 *
 * Copyright (c) 2013-2025, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THE SPINE RUNTIMES ARE PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES,
 * BUSINESS INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THE SPINE RUNTIMES, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef Spine_EventData_h
#define Spine_EventData_h

#include <spine_godot/spine-cpp/include/spine/SpineObject.h>
#include <spine_godot/spine-cpp/include/spine/SpineString.h>

namespace spine {
/// Stores the setup pose values for an Event.
	class SP_API EventData : public SpineObject {
		friend class SkeletonBinary;

		friend class SkeletonJson;

		friend class Event;

	public:
		explicit EventData(const String &name);

		/// The name of the event, which is unique within the skeleton.
		const String &getName() const;

		int getIntValue() const;

		void setIntValue(int inValue);

		float getFloatValue() const;

		void setFloatValue(float inValue);

		const String &getStringValue() const;

		void setStringValue(const String &inValue);

		const String &getAudioPath() const;

		void setAudioPath(const String &inValue);

		float getVolume() const;

		void setVolume(float inValue);

		float getBalance() const;

		void setBalance(float inValue);

	private:
		const String _name;
		int _intValue;
		float _floatValue;
		String _stringValue;
		String _audioPath;
		float _volume;
		float _balance;
	};
}

#endif /* Spine_EventData_h */
