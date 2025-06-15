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

#ifndef SPINE_SPINE_H_
#define SPINE_SPINE_H_

#include <spine_godot/spine-cpp/include/spine/Animation.h>
#include <spine_godot/spine-cpp/include/spine/AnimationState.h>
#include <spine_godot/spine-cpp/include/spine/AnimationStateData.h>
#include <spine_godot/spine-cpp/include/spine/Atlas.h>
#include <spine_godot/spine-cpp/include/spine/AtlasAttachmentLoader.h>
#include <spine_godot/spine-cpp/include/spine/Attachment.h>
#include <spine_godot/spine-cpp/include/spine/AttachmentLoader.h>
#include <spine_godot/spine-cpp/include/spine/AttachmentTimeline.h>
#include <spine_godot/spine-cpp/include/spine/AttachmentType.h>
#include <spine_godot/spine-cpp/include/spine/BlendMode.h>
#include <spine_godot/spine-cpp/include/spine/Bone.h>
#include <spine_godot/spine-cpp/include/spine/BoneData.h>
#include <spine_godot/spine-cpp/include/spine/BoundingBoxAttachment.h>
#include <spine_godot/spine-cpp/include/spine/ClippingAttachment.h>
#include <spine_godot/spine-cpp/include/spine/Color.h>
#include <spine_godot/spine-cpp/include/spine/ColorTimeline.h>
#include <spine_godot/spine-cpp/include/spine/ConstraintData.h>
#include <spine_godot/spine-cpp/include/spine/ContainerUtil.h>
#include <spine_godot/spine-cpp/include/spine/CurveTimeline.h>
#include <spine_godot/spine-cpp/include/spine/DeformTimeline.h>
#include <spine_godot/spine-cpp/include/spine/DrawOrderTimeline.h>
#include <spine_godot/spine-cpp/include/spine/Event.h>
#include <spine_godot/spine-cpp/include/spine/EventData.h>
#include <spine_godot/spine-cpp/include/spine/EventTimeline.h>
#include <spine_godot/spine-cpp/include/spine/Extension.h>
#include <spine_godot/spine-cpp/include/spine/HasRendererObject.h>
#include <spine_godot/spine-cpp/include/spine/HashMap.h>
#include <spine_godot/spine-cpp/include/spine/IkConstraint.h>
#include <spine_godot/spine-cpp/include/spine/IkConstraintData.h>
#include <spine_godot/spine-cpp/include/spine/IkConstraintTimeline.h>
#include <spine_godot/spine-cpp/include/spine/Inherit.h>
#include <spine_godot/spine-cpp/include/spine/InheritTimeline.h>
#include <spine_godot/spine-cpp/include/spine/Json.h>
#include <spine_godot/spine-cpp/include/spine/LinkedMesh.h>
#include <spine_godot/spine-cpp/include/spine/MathUtil.h>
#include <spine_godot/spine-cpp/include/spine/MeshAttachment.h>
#include <spine_godot/spine-cpp/include/spine/MixBlend.h>
#include <spine_godot/spine-cpp/include/spine/MixDirection.h>
#include <spine_godot/spine-cpp/include/spine/PathAttachment.h>
#include <spine_godot/spine-cpp/include/spine/PathConstraint.h>
#include <spine_godot/spine-cpp/include/spine/PathConstraintData.h>
#include <spine_godot/spine-cpp/include/spine/PathConstraintMixTimeline.h>
#include <spine_godot/spine-cpp/include/spine/PathConstraintPositionTimeline.h>
#include <spine_godot/spine-cpp/include/spine/PathConstraintSpacingTimeline.h>
#include <spine_godot/spine-cpp/include/spine/Physics.h>
#include <spine_godot/spine-cpp/include/spine/PhysicsConstraint.h>
#include <spine_godot/spine-cpp/include/spine/PhysicsConstraintData.h>
#include <spine_godot/spine-cpp/include/spine/PointAttachment.h>
#include <spine_godot/spine-cpp/include/spine/Pool.h>
#include <spine_godot/spine-cpp/include/spine/PositionMode.h>
#include <spine_godot/spine-cpp/include/spine/Property.h>
#include <spine_godot/spine-cpp/include/spine/RTTI.h>
#include <spine_godot/spine-cpp/include/spine/RegionAttachment.h>
#include <spine_godot/spine-cpp/include/spine/RotateMode.h>
#include <spine_godot/spine-cpp/include/spine/RotateTimeline.h>
#include <spine_godot/spine-cpp/include/spine/ScaleTimeline.h>
#include <spine_godot/spine-cpp/include/spine/ShearTimeline.h>
#include <spine_godot/spine-cpp/include/spine/Skeleton.h>
#include <spine_godot/spine-cpp/include/spine/SkeletonBinary.h>
#include <spine_godot/spine-cpp/include/spine/SkeletonBounds.h>
#include <spine_godot/spine-cpp/include/spine/SkeletonClipping.h>
#include <spine_godot/spine-cpp/include/spine/SkeletonData.h>
#include <spine_godot/spine-cpp/include/spine/SkeletonJson.h>
#include <spine_godot/spine-cpp/include/spine/SkeletonRenderer.h>
#include <spine_godot/spine-cpp/include/spine/Skin.h>
#include <spine_godot/spine-cpp/include/spine/Slot.h>
#include <spine_godot/spine-cpp/include/spine/SlotData.h>
#include <spine_godot/spine-cpp/include/spine/SpacingMode.h>
#include <spine_godot/spine-cpp/include/spine/SpineObject.h>
#include <spine_godot/spine-cpp/include/spine/SpineString.h>
#include <spine_godot/spine-cpp/include/spine/TextureLoader.h>
#include <spine_godot/spine-cpp/include/spine/Timeline.h>
#include <spine_godot/spine-cpp/include/spine/TransformConstraint.h>
#include <spine_godot/spine-cpp/include/spine/TransformConstraintData.h>
#include <spine_godot/spine-cpp/include/spine/TransformConstraintTimeline.h>
#include <spine_godot/spine-cpp/include/spine/TranslateTimeline.h>
#include <spine_godot/spine-cpp/include/spine/Triangulator.h>
#include <spine_godot/spine-cpp/include/spine/Updatable.h>
#include <spine_godot/spine-cpp/include/spine/Vector.h>
#include <spine_godot/spine-cpp/include/spine/VertexAttachment.h>
#include <spine_godot/spine-cpp/include/spine/Vertices.h>

#endif
