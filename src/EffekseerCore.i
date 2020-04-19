%module EffekseerCore

%{

#include "../Core/EffekseerBackendCore.h"
#include "../Core/EffekseerEffectCore.h"
#include "../Core/EffekseerManagerCore.h"

%}

%include "stdint.i"

#if SWIGJAVA
%include "swig/Lib/java/char16.i"
%include various.i
%apply char *BYTE { char* data };

#endif

%include "cpp/Core/EffekseerBackendCore.h"
%include "cpp/Core/EffekseerEffectCore.h"
%include "cpp/Core/EffekseerManagerCore.h"
