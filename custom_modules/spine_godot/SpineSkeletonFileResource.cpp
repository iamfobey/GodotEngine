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

#include "SpineSkeletonFileResource.h"
#ifdef SPINE_GODOT_EXTENSION
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/classes/file_access.hpp>
#else
#if VERSION_MAJOR > 3
#include "core/error/error_list.h"
#include "core/error/error_macros.h"
#include "core/io/file_access.h"
#else
#include "core/error_list.h"
#include "core/error_macros.h"
#include "core/os/file_access.h"
#endif
#endif
#include <spine_godot/spine-cpp/include/spine/Json.h>
#include <spine_godot/spine-cpp/include/spine/Version.h>
#include <spine_godot/spine-cpp/include/spine/Extension.h>


struct BinaryInput {
	const unsigned char *cursor;
	const unsigned char *end;
};

static unsigned char readByte(BinaryInput *input) {
	return *input->cursor++;
}

static int readVarint(BinaryInput *input, bool optimizePositive) {
	unsigned char b = readByte(input);
	int value = b & 0x7F;
	if (b & 0x80) {
		b = readByte(input);
		value |= (b & 0x7F) << 7;
		if (b & 0x80) {
			b = readByte(input);
			value |= (b & 0x7F) << 14;
			if (b & 0x80) {
				b = readByte(input);
				value |= (b & 0x7F) << 21;
				if (b & 0x80) value |= (readByte(input) & 0x7F) << 28;
			}
		}
	}

	if (!optimizePositive) {
		value = (((unsigned int) value >> 1) ^ -(value & 1));
	}

	return value;
}

static char *readString(BinaryInput *input) {
	int length = readVarint(input, true);
	char *string;
	if (length == 0) {
		return NULL;
	}
	string = spine::SpineExtension::alloc<char>(length, __FILE__, __LINE__);
	memcpy(string, input->cursor, length - 1);
	input->cursor += length - 1;
	string[length - 1] = '\0';
	return string;
}

void SpineSkeletonFileResource::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_from_file", "path"), &SpineSkeletonFileResource::load_from_file);
}

static bool checkVersion(const char *version) {
	if (!version) return false;
	char *result = (char *) (strstr(version, SPINE_VERSION_STRING) - version);
	return result == 0;
}

static bool checkJson(const char *jsonData) {
	spine::Json json(jsonData);
	spine::Json *skeleton = spine::Json::getItem(&json, "skeleton");
	if (!skeleton) return false;
	const char *version = spine::Json::getString(skeleton, "spine", 0);
	if (!version) return false;

	return checkVersion(version);
}

static bool checkBinary(const char *binaryData, int length) {
	BinaryInput input;
	input.cursor = (const unsigned char *) binaryData;
	input.end = (const unsigned char *) binaryData + length;
	// Skip hash
	input.cursor += 8;
	char *version = readString(&input);
	bool result = checkVersion(version);
	spine::SpineExtension::free(version, __FILE__, __LINE__);
	return result;
}

Error SpineSkeletonFileResource::load_from_file(const String &path) {
	Error error = OK;
	if (path.ends_with(".spjson") || path.ends_with(".spine-json")) {
#ifdef SPINE_GODOT_EXTENSION
		json = FileAccess::get_file_as_string(path);
		if (SSIZE(json) == 0) return ERR_INVALID_DATA;
#else
		json = FileAccess::get_file_as_string(path, &error);
		if (error != OK) return error;
#endif
		if (!checkJson(json.utf8().get_data())) return ERR_INVALID_DATA;
	} else {
#ifdef SPINE_GODOT_EXTENSION
		binary = FileAccess::get_file_as_bytes(path);
		if (binary.size() == 0) return ERR_INVALID_DATA;
#else
#if VERSION_MAJOR > 3
		binary = FileAccess::get_file_as_bytes(path, &error);
#else
		binary = FileAccess::get_file_as_array(path, &error);
#endif
		if (error != OK) return error;
#endif
		if (!checkBinary((const char *) binary.ptr(), binary.size())) return ERR_INVALID_DATA;
	}
	return error;
}

Error SpineSkeletonFileResource::save_to_file(const String &path) {
	Error error;
#ifdef SPINE_GODOT_EXTENSION
	Ref<FileAccess> file = FileAccess::open(path, FileAccess::WRITE);
	if (!file.is_valid()) return ERR_FILE_CANT_OPEN;
#else
#if VERSION_MAJOR > 3
	Ref<FileAccess> file = FileAccess::open(path, FileAccess::WRITE, &error);
	if (error != OK) return error;
#else
	FileAccess *file = FileAccess::open(path, FileAccess::WRITE, &error);
	if (error != OK) {
		if (file) file->close();
		return error;
	}
#endif
#endif
	if (!is_binary())
		file->store_string(json);
	else
		file->store_buffer(binary.ptr(), binary.size());
#if VERSION_MAJOR > 3
	file->flush();
#else
	file->close();
#endif
	return OK;
}

#ifndef SPINE_GODOT_EXTENSION
#if VERSION_MAJOR > 3
Error SpineSkeletonFileResource::copy_from(const Ref<Resource> &p_resource) {
	auto error = Resource::copy_from(p_resource);
	if (error != OK) return error;
	const Ref<SpineSkeletonFileResource> &spineFile = static_cast<const Ref<SpineSkeletonFileResource> &>(p_resource);
	this->json = spineFile->json;
	this->binary = spineFile->binary;
	emit_signal(SNAME("skeleton_file_changed"));
	return OK;
}
#endif
#endif

#ifdef SPINE_GODOT_EXTENSION
Variant SpineSkeletonFileResourceFormatLoader::_load(const String &path, const String &original_path, bool use_sub_threads, int32_t cache_mode) {
#else
#if VERSION_MAJOR > 3
RES SpineSkeletonFileResourceFormatLoader::load(const String &path, const String &original_path, Error *error, bool use_sub_threads, float *progress, CacheMode cache_mode) {
#else
#if VERSION_MINOR > 5
RES SpineSkeletonFileResourceFormatLoader::load(const String &path, const String &original_path, Error *error, bool no_subresource_cache) {
#else
RES SpineSkeletonFileResourceFormatLoader::load(const String &path, const String &original_path, Error *error) {
#endif
#endif
#endif
	Ref<SpineSkeletonFileResource> skeleton_file = memnew(SpineSkeletonFileResource);
	skeleton_file->load_from_file(path);
#ifndef SPINE_GODOT_EXTENSION
	if (error) *error = OK;
#endif
	return skeleton_file;
}

#ifdef SPINE_GODOT_EXTENSION
PackedStringArray SpineSkeletonFileResourceFormatLoader::_get_recognized_extensions() {
	PackedStringArray extensions;
	extensions.push_back("spjson");
	extensions.push_back("spskel");
	return extensions;
}
#else
void SpineSkeletonFileResourceFormatLoader::get_recognized_extensions(List<String> *extensions) const {
	extensions->push_back("spjson");
	extensions->push_back("spskel");
}
#endif

#ifdef SPINE_GODOT_EXTENSION
String SpineSkeletonFileResourceFormatLoader::_get_resource_type(const String &path) {
#else
String SpineSkeletonFileResourceFormatLoader::get_resource_type(const String &path) const {
#endif
	return path.ends_with(".spjson") || path.ends_with(".spskel") || path.ends_with(".spine-json") || path.ends_with(".skel") ? "SpineSkeletonFileResource" : "";
}

#ifdef SPINE_GODOT_EXTENSION
bool SpineSkeletonFileResourceFormatLoader::_handles_type(const StringName &type) {
#else
bool SpineSkeletonFileResourceFormatLoader::handles_type(const String &type) const {
#endif
	return type == StringName("SpineSkeletonFileResource") || ClassDB::is_parent_class(type, "SpineSkeletonFileResource");
}

#ifdef SPINE_GODOT_EXTENSION
Error SpineSkeletonFileResourceFormatSaver::_save(const Ref<Resource> &resource, const String &path, uint32_t flags) {
#else
#if VERSION_MAJOR > 3
Error SpineSkeletonFileResourceFormatSaver::save(const RES &resource, const String &path, uint32_t flags) {
#else
Error SpineSkeletonFileResourceFormatSaver::save(const String &path, const RES &resource, uint32_t flags) {
#endif
#endif
	Ref<SpineSkeletonFileResource> res = resource;
	Error error = res->save_to_file(path);
	return error;
}

#ifdef SPINE_GODOT_EXTENSION
PackedStringArray SpineSkeletonFileResourceFormatSaver::_get_recognized_extensions(const Ref<Resource> &resource) {
	PackedStringArray extensions;
	if (Object::cast_to<SpineSkeletonFileResource>(*resource)) {
		extensions.push_back("spjson");
		extensions.push_back("spskel");
	}
	return extensions;
}
#else
void SpineSkeletonFileResourceFormatSaver::get_recognized_extensions(const RES &resource, List<String> *p_extensions) const {
	if (Object::cast_to<SpineSkeletonFileResource>(*resource)) {
		p_extensions->push_back("spjson");
		p_extensions->push_back("spskel");
	}
}
#endif

#ifdef SPINE_GODOT_EXTENSION
bool SpineSkeletonFileResourceFormatSaver::_recognize(const Ref<Resource> &resource) {
#else
bool SpineSkeletonFileResourceFormatSaver::recognize(const RES &resource) const {
#endif
	return Object::cast_to<SpineSkeletonFileResource>(*resource) != nullptr;
}
