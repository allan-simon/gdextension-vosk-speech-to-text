#ifndef VOSK_H
#define VOSK_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "vosk_api.h"

namespace godot {

class Vosk : public Node {
    GDCLASS(Vosk, Node)

private:
    double time_passed;
    void *vosk_handle;
    VoskRecognizer* recognizer;
    VoskModel* model;

protected:
    static void _bind_methods();

public:
    Vosk();
    ~Vosk();

    void init(String modelPath);
    void init_wordlist(String modelPath, String wordsList);
    bool accept_wave_form(PackedByteArray data);
    bool accept_wave_form_stereo_float(PackedVector2Array data);
    String partial_result();
	String result();

};

}

#endif
