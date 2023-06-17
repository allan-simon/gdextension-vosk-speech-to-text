#ifndef VOSK_REGISTER_TYPES_H
#define VOSK_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_vosk_module(ModuleInitializationLevel p_level);
void uninitialize_vosk_module(ModuleInitializationLevel p_level);

#endif
