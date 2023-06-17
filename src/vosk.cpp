#include "vosk.h"
#include "vosk_api.h"
#include <godot_cpp/core/class_db.hpp>
#include <fstream>

using namespace godot;

void Vosk::_bind_methods() {
	ClassDB::bind_method(D_METHOD("init", "modelPath", "wordsList"), &Vosk::init);
	ClassDB::bind_method(D_METHOD("accept_wave_form", "data"), &Vosk::accept_wave_form);
	ClassDB::bind_method(D_METHOD("partial_result"), &Vosk::partial_result);
	ClassDB::bind_method(D_METHOD("result"), &Vosk::result);
}

Vosk::Vosk() {
    // Initialize any variables here.
    time_passed = 0.0;
}

Vosk::~Vosk() {
    //if (recognizer != nullptr) {
    //    vosk_recognizer_free(recognizer);
    //}
    //if (model != nullptr ) {
    //    vosk_model_free(model);
    //}
    // Add your cleanup here.
}

void Vosk::init(String modelPath, String wordsList)
{
    vosk_set_log_level(2);
    model = vosk_model_new(modelPath.utf8().get_data());
    recognizer = vosk_recognizer_new_grm(model, 44100, wordsList.utf8().get_data());
}

bool Vosk::accept_wave_form(PackedByteArray data)
{
    // big hack waiting https://github.com/godotengine/godot-proposals/issues/7105
    char mono[20000] = {0};

    for (int i = 0; i < data.size(); i += 4) {
        mono[i/2+0] = data[i];
        mono[i/2+1] = data[i+1];
    }

    return vosk_recognizer_accept_waveform(
        recognizer,
        mono,
        data.size()/2
        //reinterpret_cast<const char*> (data.ptr()),
        //data.size()
    );
}


String Vosk::partial_result()
{
    return vosk_recognizer_partial_result(recognizer);
}

String Vosk::result()
{

    return vosk_recognizer_result(recognizer);
}
