//Single File Mess
//Game Engine

#pragma once

#ifndef __SFM_GUI_3862103495683_H__
#define __SFM_GUI_3862103495683_H__

#pragma region Includes

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <linux/input.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <SDL2/SDL.h>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <GL/gl.h>
#include <chrono>
#include <cstring>
#include <algorithm>
#include "./lodepng.h"

// Linux
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#pragma endregion

namespace sf2d {
///////////////////////////////////////////////////////////////
// TYPEDEF

#pragma region Typedefs

typedef std::vector<char> ByteBuffer;

#pragma endregion

#pragma region Strings

#define Stz std::string("") +

typedef std::string string_t;
typedef std::wstring wstring_t;

std::string operator+(const std::string& str, const char& rhs) {
  return str + std::to_string(rhs);
}
std::string operator+(const std::string& str, const int8_t& rhs) {
  return str + std::to_string(rhs);
}
std::string operator+(const std::string& str, const int16_t& rhs) {
  return str + std::to_string(rhs);
}
std::string operator+(const std::string& str, const int32_t& rhs) {
  return str + std::to_string(rhs);
}
std::string operator+(const std::string& str, const int64_t& rhs) {
  return str + std::to_string(rhs);
}

std::string operator+(const std::string& str, const uint8_t& rhs) {
  return str + std::to_string(rhs);
}
std::string operator+(const std::string& str, const uint16_t& rhs) {
  return str + std::to_string(rhs);
}
std::string operator+(const std::string& str, const uint32_t& rhs) {
  return str + std::to_string(rhs);
}
std::string operator+(const std::string& str, const uint64_t& rhs) {
  return str + std::to_string(rhs);
}

std::string operator+(const std::string& str, const double& rhs) {
  return str + std::to_string(rhs);
}
std::string operator+(const std::string& str, const float& rhs) {
  return str + std::to_string(rhs);
}

#pragma endregion

#pragma region Enums

enum class ButtonState { Up,
                         Press,
                         Hold,
                         Release,
                         None };
enum class MouseButton { Left,
                         Right,
                         Middle };

#pragma endregion

#pragma region FWD

class TypeConv;
class Game;
class App;
class PhysicsComponent;
class MeshComponent;
class StringUtil;
class GraphicsWindowCreateParameters;
class Input;
class Gu;
class Log;
class RenderViewport;

#pragma endregion

class Log {
public:
  static void error(const std::string& str) {
    std::cout << str << std::endl;
  }
  static void info(const std::string& str) {
    std::cout << str << std::endl;
  }
};

#pragma region Preprocessor
#define __out_
#define __in_
#define BRLogError(x) Log::error(Stz x)
#define BRLogInfo(x) Log::info(Stz x)
#define BRLogWarn(x) BRLogInfo(x)
#define BRLogDebug(x) BRLogInfo(x)
#define BRThrowException(x)     \
  do {                          \
    BRLogError(x);              \
    throw new std::exception(); \
  } while (0);
#define BRThrowNotImplementedException() BRThrowException("The method is not implemented.")
void staticDebugBreak(const string_t& str);
void runtimeAssertion(const string_t& str);
#ifdef _DEBUG
#define AssertOrThrow2(x)                                           \
  do {                                                              \
    if (!(x)) {                                                     \
      staticDebugBreak(Stz "Debug Time Assertion: '" + #x + "'. "); \
    }                                                               \
  } while (0)
#else
#define AssertOrThrow2(x)                                        \
  do {                                                           \
    if (!(x)) {                                                  \
      runtimeAssertion(Stz "Runtime Assertion: '" + #x + "'. "); \
    }                                                            \
  } while (0)
#endif

#pragma endregion

class TypeConv {
public:
  static int_fast32_t strToInt(const string_t& s) {
    int_fast32_t ret;
    try {
      ret = std::stoi(s);
    }
    catch (const std::invalid_argument& ia) {
      BRLogError("strToInt: Invalid argument '" + s + "'. ex: " + ia.what());

      throw ia;
    }
    return ret;
  }
};

class MathUtils {
public:
  static int32_t getNumberOfDigits(int32_t i) {
    return i > 0 ? (int)log10f((float)i) + 1 : 1;
  }
  static uint32_t getNumberOfDigits(uint32_t i) {
    return i > 0 ? (int)log10((double)i) + 1 : 1;
  }
};

#pragma region Structs

struct Box2f {
  glm::vec2 _p0;
  glm::vec2 _p1;
};
struct Pixel4f {
public:
  float r = 0, g = 0, b = 0, a = 0;
  Pixel4f(float r = 0, float g = 0, float b = 0, float a = 0) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
};
struct v2x2 {
  float x, y, u, v;
  v2x2(float dx, float dy, float du, float dv) {
    x = dx;
    y = dy;
    u = du;
    v = dv;
  }
};
struct v3n3x2 {
  glm::vec3 v;
  glm::vec3 n;
  glm::vec2 x;
  v3n3x2(glm::vec3& dv, glm::vec3& dn, glm::vec2& dx) {
    v = dv;
    n = dn;
    x = dx;
  }
};
struct v_GuiVert {
  glm::vec4 _rect;
  glm::vec4 _clip;
  glm::vec4 _tex;
  glm::vec2 _texsiz;
  glm::uvec2 _pick_color;
};

#pragma endregion

class StringUtil {
public:
  static string_t getZeroPaddedNumber(int32_t number, int32_t numberOfZeros) {
    return getLeftPaddedNumber(number, numberOfZeros, '0');
  }
  static string_t getLeftPaddedNumber(int32_t number, int32_t numberOfChars, char padChar) {
    return getPaddedNumber(number, numberOfChars, padChar);
  }
  static string_t getPaddedNumber(int32_t number, int32_t maxNumberOfChars, char padChar, bool rightAlignNumber = true, bool expand = true) {
    string_t ret;
    char* cbuf;
    int32_t nDigits;

    nDigits = MathUtils::getNumberOfDigits(number);

    if (nDigits > maxNumberOfChars) {
      if (expand) {
        maxNumberOfChars = nDigits;
      }
    }

    // fancy printf
    cbuf = new char[maxNumberOfChars + 1];
    memset(cbuf, 0, maxNumberOfChars + 1);

    if (rightAlignNumber == (bool)true) {
      snprintf(cbuf, maxNumberOfChars + 1, "%0*d", maxNumberOfChars, number);
    }
    else {
      //right pad
      //TODO: make sure this is alright. In Windows this worked.
      //snprintf(cbuf, maxNumberOfChars + 1, "%-0*d", maxNumberOfChars, number);
      //Linux
      snprintf(cbuf, maxNumberOfChars + 1, "%-*d", maxNumberOfChars, number);
    }

    ret = string_t(cbuf);
    delete[] cbuf;

    // replace
    if (nDigits < maxNumberOfChars) {
      if (rightAlignNumber == (bool)true) {
        std::replace(ret.begin(), ret.begin() + (ret.length() - nDigits), '0', padChar);
      }
      else {
        std::replace(ret.begin() + nDigits, ret.end(), '0', padChar);
      }
    }
    return ret;
  }
  static string_t removeNewline(const string_t& str) {
    string_t out = str;

    if (out.length() == 0) {
      return out;
    }
    if (out[out.length() - 1] == '\0') {
      out = out.substr(0, out.length() - 1);
    }
    if (out.length() == 0) {
      return out;
    }
    if (out[out.length() - 1] == '\n') {
      out = out.substr(0, out.length() - 1);
    }
    if (out.length() == 0) {
      return out;
    }
    if (out[out.length() - 1] == '\r') {
      out = out.substr(0, out.length() - 1);
    }

    return out;
  }
  static std::vector<string_t> split(const string_t& in, char del) {
    std::vector<string_t> ret;
    split(in, del, ret);
    return ret;
  }
  static void split(const string_t& in, char del, std::vector<string_t>& __out_ ret) {
    string_t tbuf = "";
    for (size_t n = 0; n < in.length(); ++n) {
      if (in[n] == del) {
        ret.push_back(tbuf);
        tbuf = "";
      }
      else
        tbuf += in[n];
    }
    if (tbuf.length())
      ret.push_back(tbuf);
  }
  static std::vector<string_t> split(const string_t& in, const std::vector<char>& dels) {
    std::vector<string_t> v;
    split(in, dels, v);
    return v;
  }
  static void split(const string_t& __in_ in, const std::vector<char>& __in_ dels, std::vector<string_t>& __out_ ret) {
    string_t tbuf = "";
    //std::vector<t_string> ret;
    bool bDel;
    for (size_t n = 0; n < in.length(); ++n) {
      bDel = (bool)false;
      for (size_t idel = 0; idel < dels.size(); ++idel) {
        if ((in[n] == dels[idel]) && (tbuf.length() > 0)) {
          ret.push_back(tbuf);
          tbuf = "";
          bDel = true;
        }
      }
      if (bDel == (bool)false)
        tbuf += in[n];
    }
    if (tbuf.length()) {
      ret.push_back(tbuf);
    }
  }
};

class GraphicsWindowCreateParameters {
public:
  static constexpr int Wintype_Desktop = 0;  //X11 doesn't encourage disabling buttons like win32, so we're going with 'window types' instead of disabling properties.
  static constexpr int Wintype_Utility = 1;
  static constexpr int Wintype_Noborder = 2;

public:
  GraphicsWindowCreateParameters(const string_t& title, int32_t x, int32_t y, int32_t width, int32_t height, int32_t type,
                                 bool fullscreen, bool show, bool forceAspectRatio) {
    _title = title;
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _fullscreen = fullscreen;
    _show = show;
    _forceAspectRatio = forceAspectRatio;
    _type = type;
  }

public:
  string_t _title = "My_Window";
  int32_t _x = 100;
  int32_t _y = 100;
  int32_t _width = 800;
  int32_t _height = 600;
  int32_t _type = Wintype_Desktop;
  bool _fullscreen = false;
  bool _show = true;               //Show after creating
  bool _forceAspectRatio = false;  //Forces the window buffer to be the same aspect as the screen.
};

class FileSystem {
public:
  static bool fileExists(const string_t& filename) {
    //**NOTE: a portable option would be to use this code from SDL.
    // However the code below is supposed to be "faster"
    /*
  SDL_RWops *rw = SDL_RWFromFile(filename.c_str(), "rb");
  if (rw == nullptr)
  return false;

  SDL_RWclose(rw);
  return true;
  */

    //**Alternate version
    bool exists;
    struct stat buffer;
    exists = (stat(filename.c_str(), &buffer) == 0);

#if defined(BR2_OS_WINDOWS)
    // We get errors when calling stat in Windows for some reason.
    SetLastError(0);
#endif

    return exists;
  }
  static void SDLFileFree(char*& pOutData) {
    delete[] pOutData;
    pOutData = nullptr;
  }
  static int SDLFileRead(const string_t& fname, char*& pOutData,
                         int64_t& _iOutSizeBytes, bool addNull) {
    //Return 1 = failure
    //Return 0 = success
    //Use SDLUtils::checkSDLError() to check the error.
    string_t full_path = fname;  // not mac -- > getFilePath(fname);

    SDL_RWops* rw = SDL_RWFromFile(full_path.c_str(), "rb");
    if (rw == NULL) {
      return 1;
    }

    _iOutSizeBytes = SDL_RWsize(rw);
    if (addNull) {
      pOutData = new char[_iOutSizeBytes + 1];
    }
    else {
      pOutData = new char[_iOutSizeBytes];
    }

    Sint64 nb_read_total = 0, nb_read = 1;
    char* buf = pOutData;
    while (nb_read_total < _iOutSizeBytes && nb_read != 0) {
      nb_read = SDL_RWread(rw, buf, 1, _iOutSizeBytes - nb_read_total);
      nb_read_total += nb_read;
      buf += nb_read;
    }
    SDL_RWclose(rw);
    if (nb_read_total != _iOutSizeBytes) {
      delete[] pOutData;
      return 1;
    }

    // So yeah sometimes you just gotta..
    if (addNull) {
      pOutData[nb_read_total] = '\0';
    }
    return 0;
  }
  static int SDLFileWrite(const string_t& fname, char* pData,
                          size_t _iDataSizeBytes) {
    string_t full_path = fname;  //getFilePath(fname);

    SDL_RWops* rw = SDL_RWFromFile(full_path.c_str(), "wb");
    if (rw == NULL) {
      return 1;
    }

    SDL_RWwrite(rw, pData, 1, _iDataSizeBytes);
    SDL_RWclose(rw);

    return 0;
  }
};

class Input {
public:
  void setKeyDown(SDL_Scancode code) {
    setKey(code, ButtonState::Hold);
  }
  void setKeyUp(SDL_Scancode code) {
    setKey(code, ButtonState::Up);
  }
  void setLmbState(ButtonState b) {
    _eLMBState = b;
  }
  void setRmbState(ButtonState b) {
    _eRMBState = b;
  }
  void setMouseWheel(int32_t m) {
    _iMouseWheel = m;
  }
  void setKey(SDL_Scancode code, ButtonState val) {
    auto found = keys.find(code);
    if (found == keys.end()) {
      keys.insert(std::make_pair(code, ButtonState::Up));
      found = keys.find(code);
    }
    found->second = val;
  }

  ButtonState getKey(SDL_Scancode code) {
    auto it = keys.find(code);
    if (it == keys.end()) {
      keys.insert(std::make_pair(code, ButtonState::Up));
      it = keys.find(code);
      //TODO: get initial button state
    }
    return it->second;
  }

  bool keyPressOrHold(SDL_Scancode code) {
    ButtonState s = getKey(code);

    return (s == ButtonState::Press || s == ButtonState::Hold);
  }

private:
  ButtonState _eLMBState = ButtonState::Up;
  ButtonState _eRMBState = ButtonState::Up;
  std::map<SDL_Scancode, ButtonState> keys;
  int32_t _iMouseWheel = 0;
};

class RenderViewport {
public:
  uint32_t width() { return _width; }
  uint32_t height() { return _height; }

  RenderViewport(uint32_t w, uint32_t h) {
    updateWH(w, h);
  }
  bool updateWH(uint32_t w, uint32_t h) {
    //Returns true if w/h has changed.
    if (_last_width != w || _last_height != h) {
      _last_width = _width;
      _last_height = _height;
      _width = w;
      _height = h;
      return true;
    }
    return false;
  }

private:
  uint32_t _width = 1;
  uint32_t _height = 1;
  uint32_t _last_width = 1;
  uint32_t _last_height = 1;
};

class Gu {
public:
  static Input* getGlobalInput() {
    if (Gu::_pInput.get() == nullptr) {
      Gu::_pInput = std::make_unique<Input>();
    }
    return Gu::_pInput.get();
  }
  static void debugBreak() {
    raise(SIGTRAP);
  }

  static uint64_t getMicroSeconds() {
    int64_t ret;
    std::chrono::nanoseconds ns = std::chrono::high_resolution_clock::now().time_since_epoch();
    ret = std::chrono::duration_cast<std::chrono::microseconds>(ns).count();
    return ret;
  }
  static uint64_t getMilliSeconds() {
    return getMicroSeconds() / 1000;
  }
  static void guiQuad2d(Box2f& pq, std::shared_ptr<RenderViewport> vp) {
    //Transforms a quad for the matrix-less Gui projection.

    //The resulting coordinates for the GPU are -0.5 +0.5 in both axes with the center being in the center of the screen
    //Translate a 2D screen quad to be rendered in a shader.
    //So* our quad is from TOP Left - OpenGL is Bottom Left - this fixes this.
    float w = (float)vp->width();
    float w2 = w * 0.5f;
    float h = (float)vp->height();
    float h2 = h * 0.5f;

    //Subtract from viewport center
    pq._p0.x -= w2;
    pq._p1.x -= w2;

    //Invert text to show rightsize up and divide by perspective
    pq._p0.x = pq._p0.x / w2;
    pq._p0.y = (h2 - pq._p0.y - 1) / h2;
    pq._p1.x = pq._p1.x / w2;
    pq._p1.y = (h2 - pq._p1.y - 1) / h2;
  }

private:
  static std::unique_ptr<Input> _pInput;
};
std::unique_ptr<Input> Gu::_pInput;

class Game {
public:
  Game(std::shared_ptr<App> a) {
    _pApp = a;
  }
  virtual void init() = 0;
  virtual void update(double delta) = 0;
  virtual void render() = 0;

  std::shared_ptr<App> app() { return _pApp; }

private:
  std::shared_ptr<App> _pApp = nullptr;
};

//Interface for OpenGL
class GL {
public:
  static PFNGLUSEPROGRAMPROC glUseProgram;
  static PFNGLBINDBUFFERARBPROC glBindBuffer;
  static PFNGLGENBUFFERSPROC glGenBuffers;
  static PFNGLBUFFERDATAPROC glBufferData;
  static PFNGLBUFFERSUBDATAPROC glBufferSubData;
  static PFNGLSHADERSOURCEPROC glShaderSource;
  static PFNGLCOMPILESHADERPROC glCompileShader;
  static PFNGLGETSHADERIVPROC glGetShaderiv;
  static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
  static PFNGLCREATEPROGRAMPROC glCreateProgram;
  static PFNGLATTACHSHADERPROC glAttachShader;
  static PFNGLLINKPROGRAMPROC glLinkProgram;
  static PFNGLDETACHSHADERPROC glDetachShader;
  static PFNGLDELETESHADERPROC glDeleteShader;
  static PFNGLCREATESHADERPROC glCreateShader;
  static PFNGLDELETEPROGRAMPROC glDeleteProgram;
  static PFNGLGETPROGRAMIVPROC glGetProgramiv;
  static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
  static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
  static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
  static PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
  static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
  static PFNGLACTIVETEXTUREPROC glActiveTexture;
  static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
  static PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog;
  static PFNGLGETOBJECTLABELPROC glGetObjectLabel;
  static PFNGLOBJECTLABELPROC glObjectLabel;
  static PFNGLOBJECTPTRLABELPROC glObjectPtrLabel;
  static PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel;
  static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
  static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
  static PFNGLDELETEBUFFERSPROC glDeleteBuffers;
  static PFNGLISBUFFERPROC glIsBuffer;
  static PFNGLMAPBUFFERPROC glMapBuffer;
  static PFNGLUNMAPBUFFERPROC glUnmapBuffer;
  static PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
  static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
  static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
  static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
  static PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri;
  static PFNGLDRAWBUFFERSPROC glDrawBuffers;
  static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
  static PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
  static PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
  static PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
  static PFNGLTEXSTORAGE2DPROC glTexStorage2D;
  static PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
  static PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
  static PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
  static PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
  static PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
  static PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
  static PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;
  static PFNGLBINDBUFFERBASEPROC glBindBufferBase;
  static PFNGLUNIFORM1IPROC glUniform1i;
  static PFNGLUNIFORM1IVPROC glUniform1iv;
  static PFNGLUNIFORM2IVPROC glUniform2iv;
  static PFNGLUNIFORM3IVPROC glUniform3iv;
  static PFNGLUNIFORM4IVPROC glUniform4iv;
  static PFNGLUNIFORM1FVPROC glUniform1fv;
  static PFNGLUNIFORM2FVPROC glUniform2fv;
  static PFNGLUNIFORM3FVPROC glUniform3fv;
  static PFNGLUNIFORM4FVPROC glUniform4fv;
  static PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
  static PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
  static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
  static PFNGLUNIFORM1UIVPROC glUniform1uiv;
  static PFNGLUNIFORM2UIVPROC glUniform2uiv;
  static PFNGLUNIFORM3UIVPROC glUniform3uiv;
  static PFNGLUNIFORM4UIVPROC glUniform4uiv;
  static PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv;
  static PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
  static PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
  static PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv;
  static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;
  static PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv;
  static PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;
  static PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
  static PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;
  static PFNGLISPROGRAMPROC glIsProgram;
  static PFNGLPROGRAMBINARYPROC glProgramBinary;
  static PFNGLVALIDATEPROGRAMPROC glValidateProgram;
  static PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
  static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
  static PFNGLMEMORYBARRIERPROC glMemoryBarrier;
  static PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
  static PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName;
  static PFNGLFENCESYNCPROC glFenceSync;
  static PFNGLISSYNCPROC glIsSync;
  static PFNGLGETSYNCIVPROC glGetSynciv;
  static PFNGLDELETESYNCPROC glDeleteSync;
  static PFNGLDISPATCHCOMPUTEPROC glDispatchCompute;
  static PFNGLGETINTEGERI_VPROC glGetIntegeri_v;
  static PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding;
  static PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex;
  static PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData;
  //PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv ;
  //PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv ;
  //PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv ;
  //PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameteruiv ;
  //PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv ;
  //PFNGLDELETETEXTURESEXTPROC glDeleteTextures ;
  //PFNGLGETTEXPARAMETERIIVPROC glGetTexParameteriv ;
  //PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameteruiv ;
  //PFNGLGETTEXTUREPARAMETERIVEXTPROC glGetTextureParameteriv ;
  static bool loadOpenGLFunctions() {
    bool bValid = true;

#define SDLGLP2(x, y)                                                                                       \
  do {                                                                                                      \
    if (!(y = (x)SDL_GL_GetProcAddress(#y))) {                                                              \
      BRLogError("GL Method " + #y + " not supported by your GPU, or there was another error somewhere.."); \
      bValid = false;                                                                                       \
      Gu::debugBreak();                                                                                     \
    }                                                                                                       \
  } while (0)
    //Quick
    //(PFN[A-Z0-9_]*)\s+([a-zA-Z0-9_]*)\s*=\s*nullptr;
    //SDLGLP2($1, $2)
    SDLGLP2(PFNGLUSEPROGRAMPROC, glUseProgram);
    SDLGLP2(PFNGLBINDBUFFERARBPROC, glBindBuffer);
    SDLGLP2(PFNGLGENBUFFERSPROC, glGenBuffers);
    SDLGLP2(PFNGLBUFFERDATAPROC, glBufferData);
    SDLGLP2(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
    SDLGLP2(PFNGLSHADERSOURCEPROC, glShaderSource);
    SDLGLP2(PFNGLCOMPILESHADERPROC, glCompileShader);
    SDLGLP2(PFNGLGETSHADERIVPROC, glGetShaderiv);
    SDLGLP2(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
    SDLGLP2(PFNGLCREATEPROGRAMPROC, glCreateProgram);
    SDLGLP2(PFNGLATTACHSHADERPROC, glAttachShader);
    SDLGLP2(PFNGLLINKPROGRAMPROC, glLinkProgram);
    SDLGLP2(PFNGLDETACHSHADERPROC, glDetachShader);
    SDLGLP2(PFNGLDELETESHADERPROC, glDeleteShader);
    SDLGLP2(PFNGLCREATESHADERPROC, glCreateShader);
    SDLGLP2(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
    SDLGLP2(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
    SDLGLP2(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
    SDLGLP2(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    SDLGLP2(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
    SDLGLP2(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer);
    SDLGLP2(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
    SDLGLP2(PFNGLACTIVETEXTUREPROC, glActiveTexture);
    SDLGLP2(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
    SDLGLP2(PFNGLGETDEBUGMESSAGELOGPROC, glGetDebugMessageLog);
    SDLGLP2(PFNGLGETOBJECTLABELPROC, glGetObjectLabel);
    SDLGLP2(PFNGLOBJECTLABELPROC, glObjectLabel);
    SDLGLP2(PFNGLOBJECTPTRLABELPROC, glObjectPtrLabel);
    SDLGLP2(PFNGLGETOBJECTPTRLABELPROC, glGetObjectPtrLabel);
    SDLGLP2(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
    SDLGLP2(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
    SDLGLP2(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
    SDLGLP2(PFNGLISBUFFERPROC, glIsBuffer);
    SDLGLP2(PFNGLMAPBUFFERPROC, glMapBuffer);
    SDLGLP2(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
    SDLGLP2(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
    SDLGLP2(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
    SDLGLP2(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
    SDLGLP2(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers);
    SDLGLP2(PFNGLFRAMEBUFFERPARAMETERIPROC, glFramebufferParameteri);
    SDLGLP2(PFNGLDRAWBUFFERSPROC, glDrawBuffers);
    SDLGLP2(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D);
    SDLGLP2(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus);
    SDLGLP2(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers);
    SDLGLP2(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);
    SDLGLP2(PFNGLTEXSTORAGE2DPROC, glTexStorage2D);
    SDLGLP2(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
    SDLGLP2(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer);
    SDLGLP2(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers);
    SDLGLP2(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage);
    SDLGLP2(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer);
    SDLGLP2(PFNGLGETUNIFORMBLOCKINDEXPROC, glGetUniformBlockIndex);
    SDLGLP2(PFNGLUNIFORMBLOCKBINDINGPROC, glUniformBlockBinding);
    SDLGLP2(PFNGLBINDBUFFERBASEPROC, glBindBufferBase);
    SDLGLP2(PFNGLUNIFORM1IPROC, glUniform1i);
    SDLGLP2(PFNGLUNIFORM1IVPROC, glUniform1iv);
    SDLGLP2(PFNGLUNIFORM2IVPROC, glUniform2iv);
    SDLGLP2(PFNGLUNIFORM3IVPROC, glUniform3iv);
    SDLGLP2(PFNGLUNIFORM4IVPROC, glUniform4iv);
    SDLGLP2(PFNGLUNIFORM1FVPROC, glUniform1fv);
    SDLGLP2(PFNGLUNIFORM2FVPROC, glUniform2fv);
    SDLGLP2(PFNGLUNIFORM3FVPROC, glUniform3fv);
    SDLGLP2(PFNGLUNIFORM4FVPROC, glUniform4fv);
    SDLGLP2(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
    SDLGLP2(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
    SDLGLP2(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
    SDLGLP2(PFNGLUNIFORM1UIVPROC, glUniform1uiv);
    SDLGLP2(PFNGLUNIFORM2UIVPROC, glUniform2uiv);
    SDLGLP2(PFNGLUNIFORM3UIVPROC, glUniform3uiv);
    SDLGLP2(PFNGLUNIFORM4UIVPROC, glUniform4uiv);
    SDLGLP2(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv);
    SDLGLP2(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv);
    SDLGLP2(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);
    SDLGLP2(PFNGLGETVERTEXATTRIBIIVPROC, glGetVertexAttribIiv);
    SDLGLP2(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetFramebufferAttachmentParameteriv);
    SDLGLP2(PFNGLGETACTIVEUNIFORMBLOCKIVPROC, glGetActiveUniformBlockiv);
    SDLGLP2(PFNGLTEXIMAGE2DMULTISAMPLEPROC, glTexImage2DMultisample);
    SDLGLP2(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer);
    SDLGLP2(PFNGLGETPROGRAMBINARYPROC, glGetProgramBinary);
    SDLGLP2(PFNGLISPROGRAMPROC, glIsProgram);
    SDLGLP2(PFNGLPROGRAMBINARYPROC, glProgramBinary);
    SDLGLP2(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);
    SDLGLP2(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib);
    SDLGLP2(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
    SDLGLP2(PFNGLMEMORYBARRIERPROC, glMemoryBarrier);
    SDLGLP2(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange);
    SDLGLP2(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC, glGetActiveUniformBlockName);
    SDLGLP2(PFNGLFENCESYNCPROC, glFenceSync);
    SDLGLP2(PFNGLISSYNCPROC, glIsSync);
    SDLGLP2(PFNGLGETSYNCIVPROC, glGetSynciv);
    SDLGLP2(PFNGLDELETESYNCPROC, glDeleteSync);
    SDLGLP2(PFNGLDISPATCHCOMPUTEPROC, glDispatchCompute);
    SDLGLP2(PFNGLGETINTEGERI_VPROC, glGetIntegeri_v);
    SDLGLP2(PFNGLSHADERSTORAGEBLOCKBINDINGPROC, glShaderStorageBlockBinding);
    SDLGLP2(PFNGLGETPROGRAMRESOURCEINDEXPROC, glGetProgramResourceIndex);
    //SDLGLP2(PFNGLGETSAMPLERPARAMETERFVPROC, glGetSamplerParameterfv);
    //SDLGLP2(PFNGLGETSAMPLERPARAMETERIIVPROC, glGetSamplerParameterIiv);
    //SDLGLP2(PFNGLGETSAMPLERPARAMETERIUIVPROC, glGetSamplerParameterIuiv);
    //SDLGLP2(PFNGLGETSAMPLERPARAMETERIUIVPROC, glGetSamplerParameteruiv);
    //SDLGLP2(PFNGLGETSAMPLERPARAMETERIVPROC, glGetSamplerParameteriv);
    //SDLGLP2(PFNGLGETSAMPLERPARAMETERIVPROC, glGetSamplerParameteriv);
    SDLGLP2(PFNGLCOPYIMAGESUBDATAPROC, glCopyImageSubData);
    //SDLGLP2(PFNGLDELETETEXTURESEXTPROC, glDeleteTextures);
    //SDLGLP2(PFNGLGETTEXPARAMETERIIVPROC, glGetTexParameteriv);
    //SDLGLP2(PFNGLGETTEXPARAMETERIUIVPROC, glGetTexParameteruiv);
    //SDLGLP2(PFNGLGETTEXTUREPARAMETERIVEXTPROC, glGetTextureParameteriv);

    return bValid;
  }
};

#pragma region GL_METHODS
PFNGLUSEPROGRAMPROC GL::glUseProgram = nullptr;
PFNGLBINDBUFFERARBPROC GL::glBindBuffer = nullptr;
PFNGLGENBUFFERSPROC GL::glGenBuffers = nullptr;
PFNGLBUFFERDATAPROC GL::glBufferData = nullptr;
PFNGLBUFFERSUBDATAPROC GL::glBufferSubData = nullptr;
PFNGLSHADERSOURCEPROC GL::glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC GL::glCompileShader = nullptr;
PFNGLGETSHADERIVPROC GL::glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC GL::glGetShaderInfoLog = nullptr;
PFNGLCREATEPROGRAMPROC GL::glCreateProgram = nullptr;
PFNGLATTACHSHADERPROC GL::glAttachShader = nullptr;
PFNGLLINKPROGRAMPROC GL::glLinkProgram = nullptr;
PFNGLDETACHSHADERPROC GL::glDetachShader = nullptr;
PFNGLDELETESHADERPROC GL::glDeleteShader = nullptr;
PFNGLCREATESHADERPROC GL::glCreateShader = nullptr;
PFNGLDELETEPROGRAMPROC GL::glDeleteProgram = nullptr;
PFNGLGETPROGRAMIVPROC GL::glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC GL::glGetProgramInfoLog = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC GL::glEnableVertexAttribArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC GL::glVertexAttribPointer = nullptr;
PFNGLVERTEXATTRIBIPOINTERPROC GL::glVertexAttribIPointer = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC GL::glDisableVertexAttribArray = nullptr;
PFNGLACTIVETEXTUREPROC GL::glActiveTexture = nullptr;
PFNGLGETUNIFORMLOCATIONPROC GL::glGetUniformLocation = nullptr;
PFNGLGETDEBUGMESSAGELOGPROC GL::glGetDebugMessageLog = nullptr;
PFNGLGETOBJECTLABELPROC GL::glGetObjectLabel = nullptr;
PFNGLOBJECTLABELPROC GL::glObjectLabel = nullptr;
PFNGLOBJECTPTRLABELPROC GL::glObjectPtrLabel = nullptr;
PFNGLGETOBJECTPTRLABELPROC GL::glGetObjectPtrLabel = nullptr;
PFNGLGENVERTEXARRAYSPROC GL::glGenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC GL::glBindVertexArray = nullptr;
PFNGLDELETEBUFFERSPROC GL::glDeleteBuffers = nullptr;
PFNGLISBUFFERPROC GL::glIsBuffer = nullptr;
PFNGLMAPBUFFERPROC GL::glMapBuffer = nullptr;
PFNGLUNMAPBUFFERPROC GL::glUnmapBuffer = nullptr;
PFNGLGETBUFFERPARAMETERIVPROC GL::glGetBufferParameteriv = nullptr;
PFNGLDELETEVERTEXARRAYSPROC GL::glDeleteVertexArrays = nullptr;
PFNGLBINDFRAMEBUFFERPROC GL::glBindFramebuffer = nullptr;
PFNGLGENFRAMEBUFFERSPROC GL::glGenFramebuffers = nullptr;
PFNGLFRAMEBUFFERPARAMETERIPROC GL::glFramebufferParameteri = nullptr;
PFNGLDRAWBUFFERSPROC GL::glDrawBuffers = nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC GL::glFramebufferTexture2D = nullptr;
PFNGLCHECKFRAMEBUFFERSTATUSPROC GL::glCheckFramebufferStatus = nullptr;
PFNGLDELETEFRAMEBUFFERSPROC GL::glDeleteFramebuffers = nullptr;
PFNGLGETACTIVEUNIFORMPROC GL::glGetActiveUniform = nullptr;
PFNGLTEXSTORAGE2DPROC GL::glTexStorage2D = nullptr;
PFNGLGENERATEMIPMAPPROC GL::glGenerateMipmap = nullptr;
PFNGLBINDRENDERBUFFERPROC GL::glBindRenderbuffer = nullptr;
PFNGLGENRENDERBUFFERSPROC GL::glGenRenderbuffers = nullptr;
PFNGLRENDERBUFFERSTORAGEPROC GL::glRenderbufferStorage = nullptr;
PFNGLFRAMEBUFFERRENDERBUFFERPROC GL::glFramebufferRenderbuffer = nullptr;
PFNGLGETUNIFORMBLOCKINDEXPROC GL::glGetUniformBlockIndex = nullptr;
PFNGLUNIFORMBLOCKBINDINGPROC GL::glUniformBlockBinding = nullptr;
PFNGLBINDBUFFERBASEPROC GL::glBindBufferBase = nullptr;
PFNGLUNIFORM1IPROC GL::glUniform1i = nullptr;
PFNGLUNIFORM1IVPROC GL::glUniform1iv = nullptr;
PFNGLUNIFORM2IVPROC GL::glUniform2iv = nullptr;
PFNGLUNIFORM3IVPROC GL::glUniform3iv = nullptr;
PFNGLUNIFORM4IVPROC GL::glUniform4iv = nullptr;
PFNGLUNIFORM1FVPROC GL::glUniform1fv = nullptr;
PFNGLUNIFORM2FVPROC GL::glUniform2fv = nullptr;
PFNGLUNIFORM3FVPROC GL::glUniform3fv = nullptr;
PFNGLUNIFORM4FVPROC GL::glUniform4fv = nullptr;
PFNGLUNIFORMMATRIX2FVPROC GL::glUniformMatrix2fv = nullptr;
PFNGLUNIFORMMATRIX3FVPROC GL::glUniformMatrix3fv = nullptr;
PFNGLUNIFORMMATRIX4FVPROC GL::glUniformMatrix4fv = nullptr;
PFNGLUNIFORM1UIVPROC GL::glUniform1uiv = nullptr;
PFNGLUNIFORM2UIVPROC GL::glUniform2uiv = nullptr;
PFNGLUNIFORM3UIVPROC GL::glUniform3uiv = nullptr;
PFNGLUNIFORM4UIVPROC GL::glUniform4uiv = nullptr;
PFNGLGETVERTEXATTRIBIUIVPROC GL::glGetVertexAttribIuiv = nullptr;
PFNGLGETVERTEXATTRIBFVPROC GL::glGetVertexAttribfv = nullptr;
PFNGLGETVERTEXATTRIBIVPROC GL::glGetVertexAttribiv = nullptr;
PFNGLGETVERTEXATTRIBIIVPROC GL::glGetVertexAttribIiv = nullptr;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC GL::glGetFramebufferAttachmentParameteriv = nullptr;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC GL::glGetActiveUniformBlockiv = nullptr;
PFNGLTEXIMAGE2DMULTISAMPLEPROC GL::glTexImage2DMultisample = nullptr;
PFNGLBLITFRAMEBUFFERPROC GL::glBlitFramebuffer = nullptr;
PFNGLGETPROGRAMBINARYPROC GL::glGetProgramBinary = nullptr;
PFNGLISPROGRAMPROC GL::glIsProgram = nullptr;
PFNGLPROGRAMBINARYPROC GL::glProgramBinary = nullptr;
PFNGLVALIDATEPROGRAMPROC GL::glValidateProgram = nullptr;
PFNGLGETACTIVEATTRIBPROC GL::glGetActiveAttrib = nullptr;
PFNGLGETATTRIBLOCATIONPROC GL::glGetAttribLocation = nullptr;
PFNGLMEMORYBARRIERPROC GL::glMemoryBarrier = nullptr;
PFNGLMAPBUFFERRANGEPROC GL::glMapBufferRange = nullptr;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC GL::glGetActiveUniformBlockName = nullptr;
PFNGLFENCESYNCPROC GL::glFenceSync = nullptr;
PFNGLISSYNCPROC GL::glIsSync = nullptr;
PFNGLGETSYNCIVPROC GL::glGetSynciv = nullptr;
PFNGLDELETESYNCPROC GL::glDeleteSync = nullptr;
PFNGLDISPATCHCOMPUTEPROC GL::glDispatchCompute = nullptr;
PFNGLGETINTEGERI_VPROC GL::glGetIntegeri_v = nullptr;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC GL::glShaderStorageBlockBinding = nullptr;
PFNGLGETPROGRAMRESOURCEINDEXPROC GL::glGetProgramResourceIndex = nullptr;
PFNGLCOPYIMAGESUBDATAPROC GL::glCopyImageSubData = nullptr;
#pragma endregion

class OglErr {
public:
  enum class GpuLogLevel { Err_,
                           Wrn_,
                           Inf_,
                           Dbg_ };
  static string_t glErrToStr(GLenum err) {
    switch (err) {
      case 0:
        return "GL_NO_ERROR         ";
      case 0x0500:
        return "GL_INVALID_ENUM     ";
      case 0x0501:
        return "GL_INVALID_VALUE    ";
      case 0x0502:
        return "GL_INVALID_OPERATION";
      case 0x0503:
        return "GL_STACK_OVERFLOW   ";
      case 0x0504:
        return "GL_STACK_UNDERFLOW  ";
      case 0x0505:
        return "GL_OUT_OF_MEMORY    ";
    }
    return " *GL Error code not recognized.";
  }
  static bool _bPrintingGPULog;
  static GLint _maxMsgLen;
  static bool chkErrRt(bool bDoNotBreak = false, bool doNotLog = false, const string_t& shaderName = "", bool clearOnly = false) {
    //Same as dbg for now
    return handleErrors(true, bDoNotBreak, doNotLog, shaderName, clearOnly);
  }
  static bool chkErrDbg(bool bDoNotBreak = false, bool doNotLog = false, const string_t& shaderName = "", bool clearOnly = false) {
    return handleErrors(true, bDoNotBreak, doNotLog, shaderName, clearOnly);
  }

private:
  static bool handleErrors(bool bShowNote, bool bDoNotBreak, bool doNotLog, const string_t& shaderName, bool clearOnly);
  static bool checkOglErr(bool bShowNote, bool bDoNotBreak, bool doNotLog, const string_t& shaderName) {
    bool bError = false;

    //GPU Log -
    // This isn't the Application log it's the hardware log on the card.
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
      if (doNotLog == false) {
        string_t errmsg = "GL Error: " + glErrToStr(err) + " (" + (int)err + ")";
        // if (StringUtil::isNotEmpty(shaderName)) {
        //   errmsg += OperatingSystem::newline() + " -> shader: " + shaderName;
        // }
        //errmsg += debugGetRenderState();
        BRLogError(errmsg);
      }

      // if (Gu::getEngineConfig()->getBreakOnGraphicsError() == true) {
      if (bDoNotBreak == false) {
        Gu::debugBreak();
      }
      // }
      bError = true;
    }

    return bError;
  }
  static void clearGPULog() {
    printAndFlushGpuLog(true, true, true, "", true);
  }
  static void printAndFlushGpuLog(bool bShowNote, bool bDoNotBreak, bool doNotLog,
                                  const string_t& shaderName, bool clearOnly) {
    if (_bPrintingGPULog) {
      //Prevent recursion.
      return;
    }
    _bPrintingGPULog = true;
    {
      printAndFlushGpuLog_Notrap(bShowNote, bDoNotBreak, doNotLog, shaderName, clearOnly);
    }
    _bPrintingGPULog = false;
  }
  static void printAndFlushGpuLog_Notrap(bool bShowNote, bool bDoNotBreak, bool doNotLog,
                                         const string_t& shaderName, bool clearOnly) {
    //Enable this in engine.cpp glEnable(GL_DEBUG_OUTPUT);
    // if (ctx == nullptr) {
    //   BRLogWarn("Context not initialized (context isseu");
    //   return;
    // }
    if (!GL::glGetDebugMessageLog) {
      BRLogWarn("Opengl log not initialized (context isseu");
      return;
    }

    GLuint numMsgs = 64;
    GLuint numFound;

    if (_maxMsgLen == -1) {
      glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &_maxMsgLen);
    }
    if (_maxMsgLen <= 0) {
      BRLogError("GL_MAX_DEBUG_MESSAGE_LENGTH returned 0.");
      _maxMsgLen = -2;
      return;
    }

    bool graphicsLogHigh = true;  // Gu::getEngineConfig()->getGraphicsErrorLogging_High();
    bool graphicsLogMed = true;   //Gu::getEngineConfig()->getGraphicsErrorLogging_Medium();
    bool graphicsLogLow = true;   //Gu::getEngineConfig()->getGraphicsErrorLogging_Low();
    bool graphicsLogInfo = true;  // Gu::getEngineConfig()->getGraphicsErrorLogging_Info();

    do {
      std::vector<GLchar> msgData(numMsgs * _maxMsgLen);
      std::vector<GLenum> sources(numMsgs);
      std::vector<GLenum> types(numMsgs);
      std::vector<GLenum> severities(numMsgs);
      std::vector<GLuint> ids(numMsgs);
      std::vector<GLsizei> lengths(numMsgs);

      numFound = GL::glGetDebugMessageLog(numMsgs, (GLsizei)msgData.size(), &sources[0], &types[0],
                                          &ids[0], &severities[0], &lengths[0], &msgData[0]);
      if (numFound == 0) {
        return;
      }
      if (clearOnly) {
        continue;  //clear messages.
      }

      sources.resize(numFound);
      types.resize(numFound);
      severities.resize(numFound);
      ids.resize(numFound);
      lengths.resize(numFound);

      std::vector<string_t> messages;
      messages.reserve(numFound);

      std::vector<GLchar>::iterator currPos = msgData.begin();
      for (size_t iMsg = 0; iMsg < lengths.size(); ++iMsg) {
        int id = ids[iMsg];
        if (!skipNVIDIA(id) && !skipATI(id)) {
          string_t strMsg = std::string(currPos, currPos + lengths[iMsg] - 1);
          GLenum severity = severities[iMsg];
          GLenum type = types[iMsg];
          GLenum source = sources[iMsg];
          logGPUMessageText(strMsg, id, shaderName, doNotLog, severity, type, source, graphicsLogHigh, graphicsLogMed, graphicsLogLow, graphicsLogInfo);
        }
        currPos = currPos + lengths[iMsg];
      }
    } while (numFound > 0);
  }
  static void logGPUMessageText(const string_t& cstrMsg, int msgId, const string_t& shaderName, bool doNotLog, GLenum severity,
                                GLenum type, GLenum source, bool graphicsLogHigh, bool graphicsLogMed, bool graphicsLogLow,
                                bool graphicsLogInfo) {
    string_t msg = "";
    string_t shaderMsg = "";

    // if (StringUtil::isNotEmpty(shaderName)) {
    //   shaderMsg = " -> shader: " + shaderName;
    // }
    if (doNotLog == false) {
      string_t strId = Stz "";  //"[id=" + StringUtil::toHex(msgId, true) + "]";

      //Skip if the config.xml has turned off this kind of logging.
      if (severity == GL_DEBUG_SEVERITY_HIGH && graphicsLogHigh == false) {
        return;
      }
      else if (severity == GL_DEBUG_SEVERITY_MEDIUM && graphicsLogMed == false) {
        return;
      }
      else if (severity == GL_DEBUG_SEVERITY_LOW && graphicsLogLow == false) {
        return;
      }
      else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION && graphicsLogInfo == false) {
        return;
      }

      string_t strSev = "";
      string_t strType = "";
      string_t strSource = "";
      GpuLogLevel level = GpuLogLevel::Dbg_;
      getTypeSevSourceLevel(type, severity, source, strType, strSev, strSource, level);

      //Prevent infinite recursion to dump the rendering state.
      string_t strStackInfo = "";
      string_t strRenderState = "";
      static bool _bPrintingGPULog = false;
      if (_bPrintingGPULog == false) {
        _bPrintingGPULog = true;
        //This isn't necessary. We can just add it above. what's happening is calling renderstate() resets the glError.
        // Also the GL Error automatically resets.
        strRenderState = (type == GL_DEBUG_SEVERITY_NOTIFICATION) ? "" : "";  //ctx->debugGetRenderState(true, false, false);
        strStackInfo = "";                                                    //(type == GL_DEBUG_TYPE_ERROR || type == GL_DEBUG_SEVERITY_NOTIFICATION) ? "" : DebugHelper::getStackTrace();  //error prints stack.
        _bPrintingGPULog = false;
      }
      else {
        strRenderState = " RenderState: Gpu Log is currently in recursive call, no information can be displayed.";
        strStackInfo = " Stack: Gpu Log is currently in recursive call, no information can be displayed.";
      }

      msg = Stz "GPU_LOG_MSG" + strId + strType + strSev + strSource + "\n" +
            shaderMsg + "\n" +
            " MSG ID: " + strId + "\n" +
            " Msg: " + cstrMsg + "\n" +
            " Render: " + "\n" + strStackInfo + "\n" +
            strRenderState;

      if (type == GL_DEBUG_TYPE_ERROR) {
        BRLogError(msg);
      }
      else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
        BRLogInfo(msg);
      }
      else {
        BRLogWarn(msg);
      }
    }
  }
  static bool skipNVIDIA(int id) {
    //NVidia - redundant messages / infos
    return id == 0x00020071     // GL_DYANMIC_DRAW or GL_STATIC_DRAW memory usgae
           || id == 0x00020084  // Texture state usage warning: Texture 0 is base level inconsistent. Check texture size.
                                // else if (id == 0x00020061) {
                                //   return true;
                                // }  // Framebuffer detailed info: The driver allocated storage for renderbuffer 1.
                                // else if (id == 0x00020004) {
                                //   return true;
                                // }  // Usage warning: Generic vertex attribute array ... uses a pointer with a small value (...). Is this intended to be used as an offset into a buffer object?
                                // else if (id == 0x00020072) {
                                //   return true;
                                // }  // Buffer performance warning: Buffer object ... (bound to ..., usage hint is GL_STATIC_DRAW) is being copied/moved from VIDEO memory to HOST memory.
                                // else if (id == 0x00020074) {
                                //   return true;
                                // }  // Buffer usage warning: Analysis of buffer object ... (bound to ...) usage indicates that the GPU is the primary producer and consumer of data for this buffer object.  The usage hint s upplied with this buffer object, GL_STATIC_DRAW, is inconsistent with this usage pattern.  Try using GL_STREAM_COPY_ARB, GL_STATIC_COPY_ARB, or GL_DYNAMIC_COPY_ARB instead.
                                // else if (id == 0x00020070) {
                                //   return true;
                                // }  // Total VBO Usage in the system... (Useful information)
                                // else if (id == 0x00020043) {
                                //   return true;
                                // }  // A non-Fullscreen clear caused a fallback from CSAA to MSAA; - probolem in clearing cube shadow buffers
                                //Other (mom's house) driver
                                // else if (id == 0x07) {
                                //   return true;
                                // }  // glLineWidth Deprecated (other driver)

      ;

    return false;
  }
  static bool skipATI(int id) {
    return false;
  }
  static void getTypeSevSourceLevel(GLenum type, GLenum severity, GLenum source, string_t& strType, string_t& strSev, string_t& strSource, GpuLogLevel& level) {
    if (type == GL_DEBUG_TYPE_ERROR) {
      strType = "[type=ERROR]";
    }
    else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) {
      strType = "[type=DEPRECATED_BEHAVIOR]";
    }
    else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) {
      strType = "[type=UNDEFINED_BEHAVIOR]";
    }
    else if (type == GL_DEBUG_TYPE_PORTABILITY) {
      strType = "[type=PORTABILITY]";
    }
    else if (type == GL_DEBUG_TYPE_PERFORMANCE) {
      strType = "[type=PERFORMANCE]";
    }
    else if (type == GL_DEBUG_TYPE_OTHER) {
      strType = "[type=OTHER]";
    }
    else {
      strType = "undefined";  //"[type=(undefined(" + TypeConv::intToStr(type) + "))]";
    }

    if (severity == GL_DEBUG_SEVERITY_HIGH) {
      strSev = "[severity=HIGH]";
      level = GpuLogLevel::Err_;
    }
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
      strSev = "[severity=MEDIUM]";
      level = GpuLogLevel::Wrn_;
    }
    else if (severity == GL_DEBUG_SEVERITY_LOW) {
      strSev = "[severity=LOW]";
      level = GpuLogLevel::Inf_;
    }
    else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
      strSev = "[severity=NOTIFICATION]";
      level = GpuLogLevel::Inf_;
    }
    else {
      strSev = "undefined";  //"[severity=(undefined(" + TypeConv::intToStr(severity) + ")))]";
      level = GpuLogLevel::Inf_;
    }

    if (source == GL_DEBUG_SOURCE_API) {
      strSource = "[source=API]";
    }
    else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM) {
      strSource = "[source=WINDOW_SYSTEM]";
    }
    else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER) {
      strSource = "[source=SHADER_COMPILER]";
    }
    else if (source == GL_DEBUG_SOURCE_THIRD_PARTY) {
      strSource = "[source=THIRD_PARTY]";
    }
    else if (source == GL_DEBUG_SOURCE_APPLICATION) {
      strSource = "[source=APPLICATION]";
    }
    else if (source == GL_DEBUG_SOURCE_OTHER) {
      strSource = "[source=OTHER]";
    }
  }
};
bool OglErr::_bPrintingGPULog = false;
GLint OglErr::_maxMsgLen = -1;

//32 Bit Image, default layout: R, G, B, A
class Image32 {
public:
  Image32() {}
  virtual ~Image32() {
    freeData();
  }
  int32_t width() { return _width; }
  int32_t height() { return _height; }
  unsigned char* pixels() { return _pPixels; }
  static std::shared_ptr<Image32> default1x1Image(std::shared_ptr<Pixel4f> pix) {
    std::shared_ptr<Image32> ret = std::make_shared<Image32>();
    ret->createBlank(1, 1, pix);
    return ret;
  }
  void load(const string_t& loc) {
    std::string teximg = loc;
    int64_t dataSize = 0;
    char* data = nullptr;

    if (FileSystem::fileExists(teximg)) {
      int ret = FileSystem::SDLFileRead(teximg, data, dataSize, false);
      if (ret == 0) {
        //good

        unsigned int width = 0;
        unsigned int height = 0;
        int err = lodepng_decode32(&_pPixels, &width, &height, (unsigned char*)data, (size_t)dataSize);
        if (err != 0) {
          BRThrowException(Stz "Could not load image " + loc + " err code = " + err);
        }
        else {
          _width = (int32_t)width;
          _height = (int32_t)height;
          //Image32::flipImage20161206(_pPixels, _width, _height);
        }
      }
      else {
        BRLogError("Failed to read file " + teximg);
      }
    }
    else {
      BRLogError("File does not exist " + teximg);
    }
  }

private:
  void createBlank(int32_t width, int32_t height, std::shared_ptr<Pixel4f> pix) {
    _width = width;
    _height = height;
    AssertOrThrow2(_width > 0 && _height > 0);
    _iDataSize = width * height * 4;
    _pPixels = (unsigned char*)malloc(_iDataSize);  // Malloc instead of new since lodepng uses malloc.
  }
  void freeData() {
    if (_pPixels) {
      //lodepng_free - this is lodepng's memory manager
      free(_pPixels);
    }
    _pPixels = nullptr;
    _iDataSize = 0;
    _width = _height = 0;
  }
  static void flipImage20161206(uint8_t* image, int width, int height) {
    int rowSiz = width * 4;

    uint8_t* rowTmp1 = new uint8_t[rowSiz];
    int h2 = height / 2;

    for (int j = 0; j < h2; ++j) {
      uint8_t* ptRowDst = image + rowSiz * j;
      uint8_t* ptRowSrc = image + rowSiz * (height - j - 1);

      memcpy(rowTmp1, ptRowDst, rowSiz);
      memcpy(ptRowDst, ptRowSrc, rowSiz);
      memcpy(ptRowSrc, rowTmp1, rowSiz);
    }

    delete[] rowTmp1;
  }

private:
  unsigned char* _pPixels = nullptr;
  int64_t _iDataSize = 0;
  int32_t _width = 0;
  int32_t _height = 0;
};

#pragma region Texture

enum class TextureFormat { Image4ub,     //png image from disk
                           DepthShadow,  //shadow map - Resolution & BPP, can be changed in the config.xml
                           CubeShadow    //cube shadow map. -  Resolution & BPP, can be changed in the config.xml
};
enum class TexWrap { Clamp,
                     Repeat };
enum class TexFilter { Linear,
                       Nearest };
enum class TextureChannel {
  Channel0,  // don't use anymore.  Use an integer instead
  Channel1,  //
  Channel2,  //
  Channel3,  //
  Channel4,  //
  Channel5,  //
  Channel6,  //
};
class Texture2D {
public:
  Texture2D(std::shared_ptr<Image32> img, bool genMipmaps, bool bRepeatU, bool bRepeatV) {
    _iWidth = img->width();
    _iHeight = img->height();

    calculateGLTextureFormat(TextureFormat::Image4ub);

    // Bind texture
    GL::glActiveTexture(GL_TEXTURE0);
    OglErr::chkErrRt();
    glGenTextures(1, &_glId);
    OglErr::chkErrRt();
    glBindTexture(_eGLTextureBinding, _glId);
    OglErr::chkErrRt();

    //Calc format
    OglErr::chkErrRt();

    _bHasMipmaps = genMipmaps;
    _bRepeatU = bRepeatU;
    _bRepeatV = bRepeatV;

    //Specify storage mode
    if (genMipmaps) {
      OglErr::chkErrRt();

      int numMipMaps = generateMipmapLevels(width(), height());
      GL::glTexStorage2D(_eGLTextureBinding, numMipMaps, _eGLTextureMipmapFormat, width(), height());
      OglErr::chkErrRt();
    }
    else {
      GL::glTexStorage2D(_eGLTextureBinding, 1, _eGLTextureMipmapFormat, width(), height());
      OglErr::chkErrRt();
    }

    // Copy texture data
    glTexSubImage2D(
      _eGLTextureBinding,
      0, 0, 0,  //level, x, y
      (GLsizei)img->width(),
      (GLsizei)img->height(),
      _eGLTextureFormat,          //format
      _eGLTextureInternalFormat,  //type
      (void*)img->pixels()        //pixels
    );

    OglErr::chkErrRt();

    // Specify Parameters
    if (bRepeatU) {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_WRAP_S, GL_REPEAT);
    }
    else {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    }
    if (bRepeatV) {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    if (genMipmaps) {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else {
      //Default to nearest filtering * this is needed because the
      //texture atlas shows edges with linear filtering
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    //if(Gu::GetEngineDisplayParams()->getEnableAnisotropicFiltering())
    //{
    //    glTexParameterf(_eFormat, GL_TEXTURE_MAX_ANISOTROPY_EXT, Gu::GetEngineDisplayParams()->getTextureAnisotropyLevel());
    //    Gu::checkErrors();
    //}

    // - Generate the mipmaps
    if (genMipmaps) {
      //GL 3.0 mipmaps
      GL::glGenerateMipmap(_eGLTextureBinding);
      OglErr::chkErrRt();
    }

    //getContext()->setObjectLabel(GL_TEXTURE, _glId, _strName);

    //Unbind so we don't modify it
    glBindTexture(_eGLTextureBinding, 0);
    /*****/
  }
  virtual ~Texture2D() {
    glDeleteTextures(1, &_glId);
  }
  static std::shared_ptr<Texture2D> default1x1Tex() {
    //Returns a 1x1 32 bit pixel white texture.
    if (_pDefault1x1Tex == nullptr) {
      std::shared_ptr<Image32> img = Image32::default1x1Image(std::make_shared<Pixel4f>(1, 1, 1, 1));
      _pDefault1x1Tex = std::make_shared<Texture2D>(img, false, true, true);
    }
    return _pDefault1x1Tex;
  }
  uint32_t width() { return _iWidth; }
  uint32_t height() { return _iHeight; }
  uint32_t boundChannel() {
    return _boundChannel;
  }
  bool bind(TextureChannel eChannel) {
    if (_glId == 0) {
      //https://stackoverflow.com/questions/1108589/is-0-a-valid-opengl-texture-id
      BRLogError("Texture was not created on the GPU.");
      Gu::debugBreak();
      return false;
    }
    else {
      GL::glActiveTexture(GL_TEXTURE0 + (int)eChannel);
      glBindTexture(_eGLTextureBinding, _glId);
      OglErr::chkErrDbg();
      _boundChannel = (int)eChannel;
    }
    return true;
  }
  void unbind(TextureChannel eChannel) {
    GL::glActiveTexture(GL_TEXTURE0 + (int)eChannel);
    glBindTexture(_eGLTextureBinding, 0);
  }
  void setWrapU(TexWrap wrap) {
    bind(TextureChannel::Channel0);
    if (wrap == TexWrap::Clamp) {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    }
    else if (wrap == TexWrap::Repeat) {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_WRAP_S, GL_REPEAT);
    }
    else {
      BRThrowNotImplementedException();
    }
    unbind(TextureChannel::Channel0);
  }
  void setWrapV(TexWrap wrap) {
    bind(TextureChannel::Channel0);
    if (wrap == TexWrap::Clamp) {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    else if (wrap == TexWrap::Repeat) {
      glTexParameteri(_eGLTextureBinding, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else {
      BRThrowNotImplementedException();
    }
    unbind(TextureChannel::Channel0);
  }
  void setFilter(TexFilter filter) {
    _eFilter = filter;
    bind(TextureChannel::Channel0);
    OglErr::chkErrDbg();

    if (filter == TexFilter::Linear) {
      if (_bHasMipmaps) {
        GL::glGenerateMipmap(_eGLTextureBinding);
        glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //Note: GL_GENERATE_MIPMAP is deprecated.
      }
      else {
        glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //GL_GENERATE_MIPMAP is deprecated.
      }
    }
    else if (filter == TexFilter::Nearest) {
      if (_bHasMipmaps) {
        GL::glGenerateMipmap(_eGLTextureBinding);
        glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
      }
      else {
        glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(_eGLTextureBinding, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      }
    }
    else {
      BRThrowNotImplementedException();
    }
    OglErr::chkErrRt();

    unbind(TextureChannel::Channel0);
  }

private:
  int32_t generateMipmapLevels(uint32_t width, uint32_t height) {
    // - Create log2 mipmaps
    int numMipMaps = 0;
    int x = std::max(width, height);
    for (; x; x = x >> 1) {
      numMipMaps++;
    }
    return numMipMaps;
  }
  void calculateGLTextureFormat(TextureFormat fmt) {
    //All textures are 32 bit
    //AssertOrThrow2(getBytesPerPixel() == 4);
    if (fmt == TextureFormat::Image4ub) {
      //We only support one color type.
      _eGLTextureFormat = (GL_RGBA);
      _eGLTextureMipmapFormat = GL_RGBA8;
      _eGLTextureInternalFormat = GL_UNSIGNED_BYTE;
      _eGLTextureBinding = GL_TEXTURE_2D;
    }
    else if (fmt == TextureFormat::DepthShadow) {
      // #define SHADOW_CUBE_MAP_TEX_INTERNAL_FORMAT GL_RGBA16F
      // #define SHADOW_CUBE_MAP_TEX_FORMAT GL_RGBA
      // #define SHADOW_CUBE_MAP_TEX_DATATYPE GL_FLOAT
      //
      //     _eTextureFormat = (GL_RGBA);
      //     _eTextureMipmapFormat = GL_RGBA8;
    }
    else if (fmt == TextureFormat::CubeShadow) {
      // #define SHADOW_CUBE_MAP_TEX_INTERNAL_FORMAT GL_RGBA16F
      // #define SHADOW_CUBE_MAP_TEX_FORMAT GL_RGBA
      // #define SHADOW_CUBE_MAP_TEX_DATATYPE GL_FLOAT
      //
      //     _eTextureFormat = (GL_RGBA);
      //     _eTextureMipmapFormat = GL_RGBA8;
    }
    else {
      BRLogError("Invalid engine texture format " + (int)fmt);
      Gu::debugBreak();
    }
  }

private:
  GLuint _glId = 0;
  uint32_t _iWidth = 0;
  uint32_t _iHeight = 0;

  TextureFormat _eFormat;
  GLenum _eGLTextureBinding = GL_TEXTURE_2D;
  GLenum _eGLTextureFormat = 0;
  GLenum _eGLTextureMipmapFormat = 0;
  GLenum _eGLTextureInternalFormat = 0;
  string_t _strLocation = "";
  TexFilter _eFilter;
  string_t _strName = "";  //Note:this maps to glObjectLabel
  bool _bHasMipmaps = false;
  bool _bRepeatU = false;
  bool _bRepeatV = false;
  bool _bLoadFailed = false;
  bool _bTransparent = false;
  uint32_t _boundChannel = 0;
  static std::shared_ptr<Texture2D> _pDefault1x1Tex;
};
std::shared_ptr<Texture2D> Texture2D::_pDefault1x1Tex = nullptr;

#pragma endregion

class ShaderProgram {
  class Shader {
  public:
    Shader() {
    }
    virtual ~Shader() {
      GL::glDeleteShader(_glId);
    }
    GLuint glId() { return _glId; }
    void compile(GLenum type, const std::string& src) {
      _shaderType = type;
      if (_shaderType != GL_VERTEX_SHADER && _shaderType != GL_FRAGMENT_SHADER && _shaderType != GL_GEOMETRY_SHADER) {
        BRThrowException("Invalid shader type passed to Shader()");
      }

      _sourceLines = StringUtil::split(src, { '\n' });

      //Shader compiler stops at null lines so we need the \n in there.
      GLchar** arg = new char*[_sourceLines.size()];
      for (size_t i = 0; i < _sourceLines.size(); ++i) {
        arg[i] = new char[_sourceLines[i].size() + 2];
        if (_sourceLines[i].size()) {
          std::memcpy(arg[i], _sourceLines[i].c_str(), _sourceLines[i].length());
        }
        arg[i][_sourceLines[i].size() + 0] = '\n';
        arg[i][_sourceLines[i].size() + 1] = '\0';
        //Windows..Error
        //memcpy_s(arg[i], pSubProg->getSourceLines()[i].size(), pSubProg->getSourceLines()[i].c_str(), pSubProg->getSourceLines()[i].size());
      }

      OglErr::chkErrDbg();

      _glId = GL::glCreateShader(type);
      OglErr::chkErrDbg();
      GL::glShaderSource(_glId, (GLsizei)_sourceLines.size(), (const GLchar**)arg, NULL);
      OglErr::chkErrDbg();
      GL::glCompileShader(_glId);
      OglErr::chkErrDbg();
      GL::glGetShaderiv(_glId, GL_COMPILE_STATUS, &_compileStatus);
      OglErr::chkErrDbg();

      if (!_compileStatus) {
        BRLogInfo(debugGetFullShaderSource());
        BRLogInfo("----------------------------------------------------");
        _errors = getErrors();
        BRLogError(_errors);
      }
      else {
        BRLogInfo("Shader compiled successfully.");
      }

      // delete arg[]
      for (size_t i = 0; i < _sourceLines.size(); ++i) {
        delete[] arg[i];
      }
      delete[] arg;
    }
    string_t getErrors() {
      GLsizei buf_size = 1;
      GL::glGetShaderiv(_glId, GL_INFO_LOG_LENGTH, &buf_size);
      OglErr::chkErrRt();

      if (buf_size == 0) {
        return Stz "";
      }
      char log_out[buf_size];
      GLsizei length_out = 0;
      GL::glGetShaderInfoLog(_glId, buf_size, &length_out, log_out);
      OglErr::chkErrRt();

      //get vector of errors
      std::vector<std::string> ret;
      std::string tempStr;
      char* c = log_out;
      size_t n = 0;
      while ((*c) && n < buf_size) {
        while (((*c) != '\n') && ((*c))) {
          tempStr += (*c);
          c++;
        }
        ret.push_back(tempStr);
        tempStr.clear();
        c++;
        n++;
      }

      //combine
      string_t ret2 = "";
      for (auto& str : ret) {
        ret2 += str;
      }

      return ret2;
    }
    string_t debugGetFullShaderSource() const {
      string_t str = "";
      for (size_t iLine = 0; iLine < _sourceLines.size(); ++iLine) {
        str += string_t(StringUtil::getZeroPaddedNumber((int32_t)iLine + 1, 4));
        str += " ";
        string_t nl = StringUtil::removeNewline(_sourceLines[iLine]);  //.substr(0, _sourceLines[i].length() - 2);
        if (nl.length() != 0) {
          //Zero length strings will add \0 which will terminate.
          str += nl;
        }
        str += string_t("\n");
      }
      return str;
    }

  private:
    GLuint _glId = 0;
    GLint _compileStatus = 0;
    GLenum _shaderType = 0;
    std::vector<std::string> _sourceLines;
    string_t _errors = "";
  };

public:
  ShaderProgram() {
  }
  virtual ~ShaderProgram() {
    _pVert = nullptr;
    _pFrag = nullptr;
    _pGeom = nullptr;
    GL::glDeleteProgram(_glId);
  }
  GLuint glId() { return _glId; }
  void compileVert(const std::string& src);

  void compile(const std::string& vert, const std::string& frag) {
    compile(vert, "", frag);
  }
  void compile(const std::string& vert, const std::string& geom, const std::string& frag) {
    try {
      _glId = GL::glCreateProgram();

      _pVert = nullptr;
      _pGeom = nullptr;
      _pFrag = nullptr;

      _pVert = std::make_unique<Shader>();
      _pVert->compile(GL_VERTEX_SHADER, vert);
      OglErr::chkErrRt();

      if (geom.length()) {
        _pGeom = std::make_unique<Shader>();
        _pGeom->compile(GL_GEOMETRY_SHADER, geom);
        OglErr::chkErrRt();
      }

      _pFrag = std::make_unique<Shader>();
      _pFrag->compile(GL_FRAGMENT_SHADER, frag);
      OglErr::chkErrRt();

      GL::glAttachShader(_glId, _pVert->glId());
      OglErr::chkErrRt();
      if (_pGeom) {
        GL::glAttachShader(_glId, _pGeom->glId());
        OglErr::chkErrRt();
      }
      GL::glAttachShader(_glId, _pFrag->glId());
      OglErr::chkErrRt();
      GL::glLinkProgram(_glId);
      OglErr::chkErrRt();

      BRLogDebug("Program linked.. getting info log.");
      std::vector<string_t> errorLog;
      getProgramErrorLog(errorLog);
      for (string_t strErr : errorLog) {
        BRLogDebug(strErr);
      }
      OglErr::chkErrRt();

      GL::glUseProgram(_glId);
      GLenum ex = glGetError();
      if (ex == GL_NO_ERROR) {
        BRLogInfo("Shader compiled successfully.");
      }
      else {
        BRLogError("Shader compile failed.");
        Gu::debugBreak();
      }
    }
    catch (std::exception& ex) {
      Gu::debugBreak();
    }
  }
  void bind() {
    GL::glUseProgram(_glId);
  }
  void unbind() {
    GL::glUseProgram(0);
  }
  GLuint texVal = 0;
  void setTextureUf(std::shared_ptr<Texture2D> tex, const string_t& name) {
    auto loc = GL::glGetUniformLocation(_glId, name.c_str());
    OglErr::chkErrDbg();
    if (loc != 0) {
      texVal = tex->boundChannel();
      GL::glUniform1uiv(loc, 1, &texVal);
      OglErr::chkErrDbg();
    }
  }
  void setMatrixUf(glm::mat4& m, const string_t& name) {
    auto loc = GL::glGetUniformLocation(_glId, name.c_str());
    OglErr::chkErrDbg();
    if (loc != 0) {
      GL::glUniformMatrix4fv(loc, 1, false, (GLfloat*)&m);
      OglErr::chkErrDbg();
    }
  }
  void getProgramErrorLog(std::vector<string_t>& outLog) {
    // - Do your stuff
    GLsizei buf_size;
    GL::glGetProgramiv(_glId, GL_INFO_LOG_LENGTH, &buf_size);

    char* log_out = new char[buf_size];
    GLsizei length_out;
    GL::glGetProgramInfoLog(_glId, buf_size, &length_out, log_out);

    string_t tempStr;
    char* c = log_out;

    for (int i = 0; i < length_out; ++i) {
      while ((*c) && (*c) != '\n' && (i < length_out)) {
        tempStr += (*c);
        c++;
        i++;
      }
      outLog.push_back(tempStr);
      tempStr.clear();
      c++;
    }

    delete[] log_out;
  }

private:
  GLuint _glId = 0;
  std::unique_ptr<Shader> _pVert;
  std::unique_ptr<Shader> _pFrag;
  std::unique_ptr<Shader> _pGeom;
};

class GpuBuffer {
public:
  GpuBuffer(const string_t& mesh_name, GLenum bufferType, size_t iElementSize) : _glBufferType(bufferType), _iElementSize(iElementSize) {
    GL::glGenBuffers(1, &_glId);
    _meshName = mesh_name;
  }
  ~GpuBuffer() {
    GL::glDeleteBuffers(1, &_glId);
  }
  bool isAllocated() { return _bIsAllocated; }
  uint32_t getGlId() { return _glId; }
  size_t getByteSize() { return _iElementSize * _iNumElements; }  // Returns the size in bytes!.
  size_t getEleSize() { return _iElementSize; }                   // Reutrns the number of fragments in this VBO.
  size_t getNumElements() { return _iNumElements; }
  void setGlBufferType(GLenum type) {
    _glBufferType = type;
  }

  void allocate(size_t iNumElements) {
    _iNumElements = iNumElements;
    bindBuffer();
    GL::glBufferData(_glBufferType, _iNumElements * _iElementSize, nullptr, GL_STATIC_DRAW);
    // GL::setObjectLabel(GL_BUFFER, _glId, _meshName + "-buffer");
    unbindBuffer();
    _bIsAllocated = true;
  }
  void copyDataServerClient(size_t num_elements, void* __out_ elements, int32_t elementSize) {
    //Acutlly the error was due to not having allocated the buffer DOH
    //if(_glBufferType==GL_SHADER_STORAGE_BUFFER)
    //    BroThrowException("Tried to call base read on an SSBO - use syncRead instead.");

    return readbytes(num_elements, elements, elementSize);
  }
  void copyDataClientServer(std::shared_ptr<ByteBuffer> gb) {
    AssertOrThrow2(gb != NULL);
    return copyDataClientServer(gb->size(), gb->data(), 1);
  }
  void copyDataServerClient(std::shared_ptr<ByteBuffer> gb) {
    AssertOrThrow2(gb != NULL);
    return copyDataServerClient(gb->size(), gb->data(), 1);
  }
  void readbytes(size_t num_elements, void* __out_ buf, int32_t elementSize) {
    if (buf == nullptr) {
      BRLogError("Tried to read to NULL Buffer reading Gpu contents.");
      Gu::debugBreak();
    }
    if (_bIsAllocated == false) {
      BRThrowException(" [VBO] was not allocated");
    }
    size_t readSize;

    if (elementSize == -1) {
      readSize = getEleSize() * num_elements;
    }
    else {
      readSize = ((size_t)elementSize) * num_elements;
    }

    size_t byteSize = getByteSize();
    if (readSize > byteSize) {
      BRThrowException("Tried to read " + readSize + " from Gpu Buffer with size of " + getByteSize() + ".");
    }
    OglErr::chkErrDbg();

    bindBuffer();
    {
      void* pData = nullptr;
      mapBuffer(GL_WRITE_ONLY, pData);
      //memcpy_s((void*)buf, readSize, pData, readSize);
      std::memcpy((void*)buf, pData, readSize);
      unmapBuffer();
    }
    unbindBuffer();

    OglErr::chkErrDbg();
  }
  void copyDataClientServer(size_t num_elements, const void* frags, int32_t iElementSize) {
    if (num_elements == 0) {
      return;
    }
    if (frags == nullptr) {
      BRLogError(" [VBO] Fragments to copy were null. ");
      Gu::debugBreak();
      return;
    }
    if (_bIsAllocated == false) {
      BRLogError(" [VBO] was not allocated");
      Gu::debugBreak();
      return;
    }

    bindBuffer();
    {
      size_t byteSize = getByteSize();
      size_t copySizeBytes;
      if (iElementSize == -1) {
        copySizeBytes = getEleSize() * num_elements;
      }
      else {
        copySizeBytes = iElementSize * num_elements;
      }
      if (copySizeBytes > byteSize) {
        BRLogError("Copy size " + copySizeBytes + " (" + num_elements + " elements) was larger than the buffer size " + byteSize + ". Make sure the input size is not -1 or less than 0.");
        unbindBuffer();
        return;
        Gu::debugBreak();
      }

      //**NOTE: we would HAVE to use glMapBuffer because when we initially create this buffer
      //we intend to have it to be the GIVEN size. glBufferData will reallocate it.
      void* pData = nullptr;
      mapBuffer(GL_WRITE_ONLY, pData);
      std::memcpy((void*)pData, frags, copySizeBytes);
      //memcpy_s((void*)pData, getByteSize(), frags, copySizeBytes);
      unmapBuffer();

      OglErr::chkErrDbg();
    }
    unbindBuffer();
  }
  void mapBuffer(GLenum access, void*& pData) {
    void* frags;
    OglErr::chkErrDbg();

    if (_isBound == false) {
      BRThrowException("GPU BUffer was not bound prior to mapping");
    }

    // - Can't map more than one buffer at the same time.
    // User must call unmap
    if (_isMapped == true) {
      BRThrowException("GPU Buffer was already mapped prior to mapping.");
    }

    if (false) {
      GLint dat;
      GL::glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_MAPPED, &dat);
      OglErr::chkErrDbg();
    }
    frags = GL::glMapBuffer(_glBufferType, access);
    OglErr::chkErrDbg();

    _isMapped = true;

    if (frags == nullptr) {
      static bool sbLogged = false;
      if (sbLogged == false) {
        sbLogged = true;
        OglErr::chkErrDbg();
        BRLogError("Error - glMapBuffer returned nullptr.");
        Gu::debugBreak();
      }
    }

    pData = frags;
  }
  void unmapBuffer() {
    verifyValidBuffer();
    if (GL::glUnmapBuffer(_glBufferType) == false) {
      //video memory just got trashed.
      BRLogError("Video Memory has been trashed by the OS. Graphics may be unstable.");
    }
    OglErr::chkErrDbg();

    _isMapped = false;
  }
  void bindBuffer() {
    OglErr::chkErrDbg();
    verifyValidBuffer();
    OglErr::chkErrDbg();
    GL::glBindBuffer(_glBufferType, _glId);
    OglErr::chkErrDbg();
    _isBound = true;
  }
  void bindBuffer(GLenum e) {
    verifyValidBuffer();
    GL::glBindBuffer(e, _glId);
    OglErr::chkErrDbg();
    _isBound = true;
  }
  void unbindBuffer() {
    GL::glBindBuffer(_glBufferType, 0);
    OglErr::chkErrDbg();
    _isBound = false;
  }
  void verifyValidBuffer() {
    //GDebugger doesn't like this for some reason.
    // if (Gu::getEngineConfig()->getEnableRuntimeErrorChecking()) {
    if (!GL::glIsBuffer(_glId)) {
      //Buffer object doesn't exist in the context.
      //Error somewhere..
      GL::glBindBuffer(_glBufferType, _glId);
      if (!GL::glIsBuffer(_glId)) {
        Gu::debugBreak();
      }
    }
    // }
  }

protected:
  uint32_t _glId = 0;
  GLenum _glBufferType;  // GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER

  size_t _iElementSize = 0;  // The element size
  size_t _iNumElements = 0;  // The number of elements we allocated

  string_t _meshName = "";

  bool _isMapped = false;
  bool _isBound = false;
  bool _bIsAllocated = false;
};

class PhysicsComponent {
  glm::vec3 v;
};
class MeshComponent {
};

class QuadBlitter {
public:
  typedef v_GuiVert GuiVert;
  QuadBlitter(int_fast32_t count = 8192, std::shared_ptr<Texture2D> pTex = nullptr) {
    init(count);
  }
  virtual ~QuadBlitter() {
    GL::glDeleteVertexArrays(1, &_vao);
  }
  void setTexture(std::shared_ptr<Texture2D> pTex) {
    _pTex = pTex;
  }
  std::shared_ptr<Texture2D> getTex() {
    //Set default tex if not available.
    if (_pTex == nullptr) {
      return Texture2D::default1x1Tex();
    }
    return _pTex;
  }
  void reset() {
    _used = 0;
  }
  void setQuad(const glm::vec2& point, std::shared_ptr<RenderViewport> vp, const glm::vec4& color = glm::vec4(1, 1, 1, 1), const glm::vec2& wh = glm::vec2(-1, -1), bool flip_test = false) {
    if (_used >= _verts_local.size()) {
      BRLogError("Too many quads used.");
      Gu::debugBreak();
      return;
    }

    Box2f cpyPos;
    cpyPos._p0.x = point.x;
    cpyPos._p0.y = point.y;
    cpyPos._p1.x = point.x + (wh.x <= 0 ? getTex()->width() : wh.x);
    cpyPos._p1.y = point.y + (wh.y <= 0 ? getTex()->height() : wh.y);

    if (flip_test) {
      auto tmp = cpyPos._p0.x;
      cpyPos._p0.x = cpyPos._p1.x;
      cpyPos._p1.x = tmp;
    }

    // convert to screen coordinates
    Gu::guiQuad2d(cpyPos, vp);

    GuiVert& v = _verts_local[_used];

    v._rect.x = cpyPos._p0.x;
    v._rect.y = cpyPos._p0.y;
    v._rect.z = cpyPos._p1.x;
    v._rect.w = cpyPos._p1.y;

    //Clip Rect.  For discard
    //  v._clip = makeClipRectForRender(b2ClipRect);
    //if (Gu::getRenderSettings()->getDebug()->getShowGuiBoxesAndDisableClipping()) {
    //Disable clip
    v._clip.x = -9999;
    v._clip.y = -9999;
    v._clip.z = 9999;
    v._clip.w = 9999;
    //  }

    //Texs
    //Not sure, I think this is in texture (sub-texture) space, [0,1] not pixels.

    v._tex.x = 0;  // _q2Tex._p0.x;  //GL - bottom left
    v._tex.y = 0;  //_q2Tex._p0.y;
    v._tex.z = 1;  //_q2Tex._p1.x;  //GL - top right *this essentially flips it upside down
    v._tex.w = 1;  //_q2Tex._p1.y;

    //I think this is in texture space (sub-texture in the case of the GUI)
    v._texsiz.x = 1;  // = fabsf(_pTexture->tex()->uv1().x - _pTexture->tex()->uv0().x);
    v._texsiz.y = 1;  //
    //
    // if (_pTexture != nullptr) {
    //   v._texsiz.x = fabsf(_pTexture->tex()->uv1().x - _pTexture->tex()->uv0().x);
    //   v._texsiz.y = fabsf(_pTexture->tex()->uv0().y - _pTexture->tex()->uv1().y);  //Uv0 - uv1 - because we flipped coords bove
    // }
    // else {
    //   //*this is for "Fixed" textures, e.g. fonts and text.  We compute them in UiLabel first
    //   v._texsiz.x = fabsf(v._tex.z - v._tex.x);
    //   v._texsiz.y = fabsf(v._tex.w - v._tex.y);  //y is flipfloped again
    // }

    //**Texture Adjust - modulating repeated textures causes seaming issues, especially with texture filtering
    //adjust the texture coordinates by some pixels to account for that.  0.5f seems to work well.
    static float pixAdjust = 0.51f;  // # of pixels to adjust texture by
                                     //#ifdef _DEBUG
                                     //    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                                     //        pixAdjust -= 0.005;
                                     //    }
                                     //    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                                     //        pixAdjust += 0.005;
                                     //    }
                                     //#endif
    float w1px = 0;                  // 1 pixel subtract from the u/v to prevent creases during texture modulation
    float h1px = 0;
    if (getTex() != nullptr) {
      if (getTex()->width() > 0 && v._texsiz.x > 0) {
        w1px = 1.0f / getTex()->width();
        w1px *= v._texsiz.x;
        w1px *= pixAdjust;
      }
      if (getTex()->height() > 0 && v._texsiz.y > 0) {
        h1px = 1.0f / getTex()->height();
        h1px *= v._texsiz.y;
        h1px *= pixAdjust;
      }
    }
    v._texsiz.x -= w1px * 2.0f;
    v._texsiz.y -= h1px * 2.0f;
    v._tex.x += w1px;
    v._tex.y += h1px;
    v._tex.z -= w1px;
    v._tex.w -= h1px;

    //**End texture adjust

    //Pick Color
    v._pick_color.x = 0;  //_iPickId;

    //Display Color
    //vec4 vc = getColor();
    v._pick_color.y =  ////    0xFFFFFFFF; //White
      ((int)(color.x * 255.0f) << 24) |
      ((int)(color.y * 255.0f) << 16) |
      ((int)(color.z * 255.0f) << 8) |
      ((int)(color.w * 255.0f) << 8);
    //_verts_local[_used] = v;

    _used++;
  }

  void render(std::shared_ptr<RenderViewport> vp) {
    if (_used == 0) {
      return;
    }
    glDisable(GL_CULL_FACE);

    std::shared_ptr<Texture2D> tex = getTex();

    copyVerts();

    tex->bind(TextureChannel::Channel0);
    _prog->bind();

    // auto mproj = glm::perspective(60.0f, (float)((float)vp->width() / (float)vp->height()), 1.0f, 1000.0f);
    // auto mview = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    _prog->setTextureUf(tex, "_ufTexture0");
    // _prog->setMatrixUf(mview, "_ufView");
    // _prog->setMatrixUf(mproj, "_ufProj");

    //test_inline_vao();

    GL::glBindVertexArray(_vao);
    // _inds->bindBuffer();
    glDrawArrays(GL_POINTS, 0, _used);
    // _inds->unbindBuffer();
    GL::glBindVertexArray(0);
    _prog->unbind();
    tex->unbind(TextureChannel::Channel0);
  }
  void test_inline_vao() {
    GLint _v401 = GL::glGetAttribLocation(_prog->glId(), "_v401");
    GLint _v402 = GL::glGetAttribLocation(_prog->glId(), "_v402");
    GLint _v403 = GL::glGetAttribLocation(_prog->glId(), "_v403");
    GLint _v201 = GL::glGetAttribLocation(_prog->glId(), "_v201");
    GLint _u201 = GL::glGetAttribLocation(_prog->glId(), "_u201");

    if (_v401 == -1 || _v402 == -1 || _v403 == -1 || _v201 == -1 || _u201 == -1) {
      BRLogError("Failed to find one or more attributes for shader.");
      Gu::debugBreak();
    }
    else {
      OglErr::chkErrDbg();
      _verts->bindBuffer();
      OglErr::chkErrDbg();
      GL::glEnableVertexAttribArray(_v401);
      GL::glVertexAttribPointer(
        _v401,
        4,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized?
        sizeof(GuiVert),        // stride
        (GLvoid*)((intptr_t)0)  // array buffer offset
      );
      OglErr::chkErrDbg();
      GL::glEnableVertexAttribArray(_v402);
      GL::glVertexAttribPointer(
        _v402,
        4,                                          // size
        GL_FLOAT,                                   // type
        GL_FALSE,                                   // normalized?
        sizeof(GuiVert),                            // stride
        (GLvoid*)((intptr_t)0 + sizeof(glm::vec4))  // array buffer offset
      );
      OglErr::chkErrDbg();
      GL::glEnableVertexAttribArray(_v403);
      GL::glVertexAttribPointer(
        _v403,
        4,                                                              // size
        GL_FLOAT,                                                       // type
        GL_FALSE,                                                       // normalized?
        sizeof(GuiVert),                                                // stride
        (GLvoid*)((intptr_t)0 + sizeof(glm::vec4) + sizeof(glm::vec4))  // array buffer offset
      );
      OglErr::chkErrDbg();
      GL::glEnableVertexAttribArray(_v201);
      GL::glVertexAttribPointer(
        _v201,
        2,                                                                                  // size
        GL_FLOAT,                                                                           // type
        GL_FALSE,                                                                           // normalized?
        sizeof(GuiVert),                                                                    // stride
        (GLvoid*)((intptr_t)0 + sizeof(glm::vec4) + sizeof(glm::vec4) + sizeof(glm::vec4))  // array buffer offset
      );
      OglErr::chkErrDbg();
      GL::glEnableVertexAttribArray(_u201);
      GL::glVertexAttribIPointer(
        _u201,
        2,  // size
        GL_UNSIGNED_INT,
        sizeof(GuiVert),                                                                                        // stride
        (GLvoid*)((intptr_t)0 + sizeof(glm::vec4) + sizeof(glm::vec4) + sizeof(glm::vec4) + sizeof(glm::vec2))  // array buffer offset
      );
      OglErr::chkErrDbg();
    }
  }

private:
  void init(uint_fast32_t count = 8192) {
    _count = count;
    createProgram();

    _verts = std::make_shared<GpuBuffer>("verts", GL_ARRAY_BUFFER, sizeof(GuiVert));
    _verts->allocate(_count);

    _verts_local = std::vector<GuiVert>((size_t)_count);
    _verts->copyDataClientServer(_verts_local.size(), _verts_local.data(), sizeof(_verts_local[0]));

    createVAO();
  }
  void copyVerts() {
    _verts->copyDataClientServer(_used, _verts_local.data(), sizeof(_verts_local[0]));
  }
  void createProgram() {
    std::string vert = Stz "#version 430\n" +
                       "layout(location = 0) in vec4 _v401;//rect\n" +
                       "layout(location = 1) in vec4 _v402;//clip\n" +
                       "layout(location = 2) in vec4 _v403;//tex\n" +
                       "layout(location = 3) in vec2 _v201;//texsiz\n" +
                       "layout(location = 4) in uvec2 _u201;//pick_color\n" +
                       "\n" +
                       "out vec4 _rectVS;\n" +
                       "out vec4 _clipVS;\n" +
                       "out vec4 _texVS;\n" +
                       "out vec2 _texsizVS;\n" +
                       "flat out uvec2 _pick_colorVS;\n" +
                       "\n" +
                       "void main() {\n" +
                       "    _rectVS = _v401;\n" +
                       "    _clipVS = _v402;\n" +
                       "    _texVS = _v403;\n" +
                       "    _texsizVS = _v201;\n" +
                       "    _pick_colorVS = _u201;\n" +
                       "\n" +
                       "    \n" +
                       "	gl_Position =  vec4(_v401.x, _v401.y, -1, 1);	\n" +
                       "}\n";

    std::string geom = Stz "#version 430\n" +
                       "layout(points) in;\n" +
                       "layout(triangle_strip, max_vertices=4) out;\n" +
                       "\n" +
                       "in vec4 _rectVS[];\n" +
                       "in vec4 _clipVS[];\n" +
                       "in vec4 _texVS[];\n" +
                       "in vec2 _texsizVS[];\n" +
                       "flat in uvec2 _pick_colorVS[];\n" +
                       "\n" +
                       "out vec2 _vert;\n" +
                       "out vec2 _tex;\n" +
                       "\n" +
                       "flat out vec4 _clip;\n" +
                       "flat out vec2 _texSiz;//We can do compute this in the GS and output better data before the PS\n" +
                       "flat out uvec2 _pick_color;\n" +
                       "flat out vec2 _texPos;//don't interpolate\n" +
                       "\n" +
                       "\n" +
                       "float p0x(vec4 f) { return f.x; }\n" +
                       "float p0y(vec4 f) { return f.y; }\n" +
                       "float p1x(vec4 f) { return f.z; }\n" +
                       "float p1y(vec4 f) { return f.w; }\n" +
                       "\n" +
                       "void setGS(){\n" +
                       "//Uniform primitie values\n" +
                       "    _clip        = _clipVS[0];\n" +
                       "    _texSiz      = _texsizVS[0];\n" +
                       "    _pick_color  = _pick_colorVS[0];\n" +
                       "    _texPos      = vec2(_texVS[0].x, _texVS[0].y);//not sure why xw.  x,y is already in opengl's BL oeiinf\n" +
                       "}\n" +
                       "\n" +
                       "void main() {\n" +
                       "    /*\n" +
                       "    0x0y                   1x0y\n" +
                       "        0------------ ----2\n" +
                       "        |          /      |\n" +
                       "        |  /              |\n" +
                       "        1 ----------------3\n" +
                       "    0x1y                   1x1y\n" +
                       "    */\n" +
                       "    \n" +
                       "    setGS();\n" +
                       "    _tex            = vec2(p0x(_texVS [0]), p0y(_texVS [0]));\n" +
                       "    _vert           = vec2(p0x(_rectVS[0]), p0y(_rectVS[0]));\n" +
                       "    gl_Position     = vec4(p0x(_rectVS[0]), p0y(_rectVS[0]), -1, 1);\n" +
                       "    EmitVertex();\n" +
                       "    \n" +
                       "    setGS();\n" +
                       "    _tex            = vec2(p0x(_texVS [0]), p1y(_texVS [0]));\n" +
                       "    _vert           = vec2(p0x(_rectVS[0]), p1y(_rectVS[0]));\n" +
                       "    gl_Position     = vec4(p0x(_rectVS[0]), p1y(_rectVS[0]), -1, 1);\n" +
                       "    EmitVertex();\n" +
                       "    \n" +
                       "    setGS();\n" +
                       "    _tex            = vec2(p1x(_texVS [0]), p0y(_texVS [0]));\n" +
                       "    _vert           = vec2(p1x(_rectVS[0]), p0y(_rectVS[0]));\n" +
                       "    gl_Position     = vec4(p1x(_rectVS[0]), p0y(_rectVS[0]), -1, 1);\n" +
                       "    EmitVertex();\n" +
                       "    \n" +
                       "    setGS();\n" +
                       "    _tex            = vec2(p1x(_texVS [0]), p1y(_texVS [0]));\n" +
                       "    _vert           = vec2(p1x(_rectVS[0]), p1y(_rectVS[0]));\n" +
                       "    gl_Position     = vec4(p1x(_rectVS[0]), p1y(_rectVS[0]), -1, 1);\n" +
                       "    EmitVertex();\n" +
                       "    \n" +
                       "    EndPrimitive();\n" +
                       "\n" +
                       "    \n" +
                       "    \n" +
                       "}\n";
    std::string frag = Stz "#version 430\n" +
                       "//layout(location = 0) out vec4 _gColorOut;\n" +
                       "out vec4 _gColorOut;\n" +
                       //"layout(location = 1) out uint _gPickOut;\n" +
                       "\n" +
                       "uniform sampler2D _ufTexture0;\n" +
                       "\n" +
                       "in vec2 _vert; //this is now the fragment position\n" +
                       "flat in vec4 _clip;//This is now the fragment clip\n" +
                       "in vec2 _tex;\n" +
                       "flat in vec2 _texPos;//Origin of the texture coords (top left)\n" +
                       "flat in vec2 _texSiz;\n" +
                       "flat in uvec2 _pick_color;\n" +
                       "\n" +
                       "void main(){\n" +
                       "    if(_vert.x < _clip.x \n" +
                       "       || _vert.y < _clip.y \n" +
                       "       || _vert.x > _clip.z \n" +
                       "       || _vert.y > _clip.w) { \n" +
                       "       discard; \n" +
                       "   }\n" +
                       "   \n" +
                       "   //Texture Scaling\n" +
                       "   //We need texpos here = p + mod(a-p, siz);\n" +
                       "   vec2 texmod;\n" +
                       "   texmod.x = _texPos.x + mod(_tex.x - _texPos.x, _texSiz.x);\n" +
                       "   texmod.y = _texPos.y + mod(_tex.y - _texPos.y, _texSiz.y);\n" +
                       "   \n" +
                       "	vec4 tx = texture(_ufTexture0, vec2(texmod));\n" +
                       "    if(tx.a < 0.001){\n" +
                       "  		discard;\n" +
                       "  	} \n" +
                       "    \n" +
                       "    float r = float((_pick_color.y>>24) & 0xFF) / 255.0;\n" +
                       "    float g = float((_pick_color.y>>16) & 0xFF) / 255.0;\n" +
                       "    float b = float((_pick_color.y>>8) & 0xFF) / 255.0;\n" +
                       "   \n" +
                       "    _gColorOut = tx * vec4(r, g, b, 1.0);\n" +
                       "\n" +
                       "  //  _gPickOut = _pick_color.x;\n" +
                       "}\n";

    _prog = std::make_shared<ShaderProgram>();
    _prog->compile(vert, geom, frag);
  }
  void createVAO() {
    GL::glGenVertexArrays(1, &_vao);
    GL::glBindVertexArray(_vao);
    {
      //Very basic vert + tex. The screen coordinates are -1,1 x and -1,1 y
      GLint _v401 = GL::glGetAttribLocation(_prog->glId(), "_v401");
      GLint _v402 = GL::glGetAttribLocation(_prog->glId(), "_v402");
      GLint _v403 = GL::glGetAttribLocation(_prog->glId(), "_v403");
      GLint _v201 = GL::glGetAttribLocation(_prog->glId(), "_v201");
      GLint _u201 = GL::glGetAttribLocation(_prog->glId(), "_u201");

      if (_v401 == -1 || _v402 == -1 || _v403 == -1 || _v201 == -1 || _u201 == -1) {
        BRLogError("Failed to find one or more attributes for shader.");
        Gu::debugBreak();
      }
      else {
        OglErr::chkErrDbg();
        _verts->bindBuffer();
        OglErr::chkErrDbg();
        GL::glEnableVertexAttribArray(_v401);
        GL::glVertexAttribPointer(
          _v401,
          4,                      // size
          GL_FLOAT,               // type
          GL_FALSE,               // normalized?
          sizeof(GuiVert),        // stride
          (GLvoid*)((intptr_t)0)  // array buffer offset
        );
        OglErr::chkErrDbg();
        GL::glEnableVertexAttribArray(_v402);
        GL::glVertexAttribPointer(
          _v402,
          4,                                          // size
          GL_FLOAT,                                   // type
          GL_FALSE,                                   // normalized?
          sizeof(GuiVert),                            // stride
          (GLvoid*)((intptr_t)0 + sizeof(glm::vec4))  // array buffer offset
        );
        OglErr::chkErrDbg();
        GL::glEnableVertexAttribArray(_v403);
        GL::glVertexAttribPointer(
          _v403,
          4,                                                              // size
          GL_FLOAT,                                                       // type
          GL_FALSE,                                                       // normalized?
          sizeof(GuiVert),                                                // stride
          (GLvoid*)((intptr_t)0 + sizeof(glm::vec4) + sizeof(glm::vec4))  // array buffer offset
        );
        OglErr::chkErrDbg();
        GL::glEnableVertexAttribArray(_v201);
        GL::glVertexAttribPointer(
          _v201,
          2,                                                                                  // size
          GL_FLOAT,                                                                           // type
          GL_FALSE,                                                                           // normalized?
          sizeof(GuiVert),                                                                    // stride
          (GLvoid*)((intptr_t)0 + sizeof(glm::vec4) + sizeof(glm::vec4) + sizeof(glm::vec4))  // array buffer offset
        );
        OglErr::chkErrDbg();
        GL::glEnableVertexAttribArray(_u201);
        GL::glVertexAttribIPointer(
          _u201,
          2,  // size
          GL_UNSIGNED_INT,
          sizeof(GuiVert),                                                                                        // stride
          (GLvoid*)((intptr_t)0 + sizeof(glm::vec4) + sizeof(glm::vec4) + sizeof(glm::vec4) + sizeof(glm::vec2))  // array buffer offset
        );
        OglErr::chkErrDbg();
      }
      GL::glBindVertexArray(0);
    }
  }

  std::shared_ptr<ShaderProgram> _prog = nullptr;
  std::shared_ptr<GpuBuffer> _verts = nullptr;
  std::shared_ptr<Texture2D> _pTex = nullptr;
  GLuint _vao = 0;
  uint32_t _count = 1;
  uint32_t _used = 0;
  std::vector<GuiVert> _verts_local;
};

class App {
  //**
  int _iProfile = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;
  int _iDepthBits = 24;
  //**
  SDL_Window* _pWindow;
  SDL_GLContext _context;
  uint32_t _iSupportedDepthSize = 0;
  bool _bVsync = false;
  std::shared_ptr<RenderViewport> _viewport = nullptr;
  glm::vec4 _clearColor = glm::vec4(1, 0, 1, 1);
  bool _bClearColorChanged = true;

public:
  std::shared_ptr<GL> _pGL = std::make_shared<GL>();
  std::shared_ptr<RenderViewport> viewport() { return _viewport; }
  void setClearColor(const glm::vec4& v) {
    _clearColor = v;
    _bClearColorChanged = true;
  }

public:
  void run(std::shared_ptr<Game> g) {
    init();
    double last_time = Gu::getMicroSeconds();
    double last_delta = Gu::getMicroSeconds();

    g->init();

    while (true) {
      if (handleSDLEvents() == true) {
        break;  //SDL_QUIT
      }

      SDL_GL_MakeCurrent(_pWindow, _context);
      {
        double curtime = Gu::getMicroSeconds();
        last_delta = curtime - last_time;
        last_time = curtime;

        //Technically, we could just use the SDL resize event to prevent unnecessary resize code.
        int last_w = 1, last_h = 1;
        SDL_GetWindowSize(_pWindow, &last_w, &last_h);
        if (_viewport->updateWH((uint32_t)last_w, (uint32_t)last_h)) {
          //Hypothetically We would resize FBO's here as well
        }

        g->update((double)last_delta / (double)1'000'000);

        if (_bClearColorChanged) {
          glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
          _bClearColorChanged = false;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        g->render();
      }
      SDL_GL_SwapWindow(_pWindow);
    }
  }
  static void checkSDLErr(bool bLog = true, bool bBreak = true) {
    //Do SDL errors here as well
    const char* c;
    while ((c = SDL_GetError()) != nullptr && *c != 0) {
      //linux : GLXInfo
      if (bLog == true) {
        Log::error(std::string("SDL: ") + std::string(c));
      }

      Gu::debugBreak();
      SDL_ClearError();
    }
  }

public:
private:
  void init() {
    SDL_ShowCursor(SDL_ENABLE);

    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
      Log::error(Stz "SDL could not be initialized: " + SDL_GetError());
    }

    string_t title = "test";

    GraphicsWindowCreateParameters params(
      title, 100, 100, 500, 500,
      GraphicsWindowCreateParameters::Wintype_Desktop, false, true, false);

    setSDLGLFlags(4, 3);
    _pWindow = makeSDLWindow(params, SDL_WINDOW_OPENGL, true);
    initGLContext(_pWindow);
    _viewport = std::make_shared<RenderViewport>(params._width, params._height);
  }
  bool initGLContext(SDL_Window* sdlw) {
    bool bRet = false;
    static bool bInitialized = false;
    if (bInitialized == true) {
      BRLogError("Tried to initialize context twice.");
      return true;
    }
    bInitialized = true;

    _context = SDL_GL_CreateContext(sdlw);
    if (!_context) {
      //Eat the "context failed" error.  It's not informative.
      checkSDLErr(false, false);
      bRet = false;
    }
    else {
      checkSDLErr();
      int ver, subver, shad_ver, shad_subver;
      getOpenGLVersion(ver, subver, shad_ver, shad_subver);

      //Make sure we have a good depth value.
      int iDepth = 0;
      SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &iDepth);
      _iSupportedDepthSize = iDepth;
      // if (iDepth < _profile->_iDepthBits) {
      //   BRLogWarn("Depth buffer size " + _profile->_iDepthBits = " not supported in profile.");
      //   bRet = false;
      // }
      // else
      //if (checkOpenGlMinimumVersionInfo(_profile->_iMinVersion, _profile->_iMinSubVersion)) {
      printHelpfulDebug();

      // if (_profile->_iMSAABuffers == 0) {
      //   Gu::getEngineConfig()->setEnableMSAA(false);
      //   BRLogWarn("This configuration did not support MSAA.");
      // }

      if (!GL::loadOpenGLFunctions()) {
        BRLogError("Failed to load context.");
        SDL_GL_DeleteContext(_context);
        bRet = false;
      }
      else {
        //Quick GL test.
        GL::glUseProgram(0);

        //Check that OpenGL initialized successfully
        loadCheckProc();

        //Swap Interval.
        SDL_GL_SetSwapInterval(_bVsync ? 1 : 0);  //Vsync is automatic on IOS

        //Create opengl error handler
        // _pOglErr = std::make_unique<OglErr>();
        // _pRenderUtils = std::make_unique<RenderUtils>(getThis<GLContext>());

        bRet = true;
      }
    }
    //}

    return bRet;
  }
  void loadCheckProc() {
    //Check that OpenGL initialized successfully by checking a library pointer.
    PFNGLUSEPROGRAMPROC proc = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
    if (proc == nullptr) {
      string_t exep;
      exep += "glUseProgram was not found.\n";
      exep += ("  OpenGL not installed, or bad graphics driver.\n");
      BRThrowException(exep);
    }
  }
  void printHelpfulDebug() {
    int tmp = 0;
    checkSDLErr();
    SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &tmp);
    BRLogInfo("SDL_GL_DOUBLEBUFFER: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &tmp);
    BRLogInfo("SDL_GL_BUFFER_SIZE: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &tmp);

    BRLogInfo("SDL_GL_DEPTH_SIZE: " + tmp);
    BRLogInfo("Skipping stencil size, should be zero.");
    //Stencil size check causes GL errors in some implementations when stencil is zero. Not sure why.
    //SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &tmp);
    BRLogInfo("SDL_GL_STENCIL_SIZE: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &tmp);
    BRLogInfo("SDL_GL_ACCELERATED_VISUAL: " + tmp);

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &tmp);
    BRLogInfo("SDL_GL_CONTEXT_PROFILE_MASK: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, &tmp);
    BRLogInfo("SDL_GL_SHARE_WITH_CURRENT_CONTEXT: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_FLAGS, &tmp);
    BRLogInfo("SDL_GL_CONTEXT_FLAGS: " + tmp);

    SDL_GL_GetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, &tmp);
    BRLogInfo("SDL_GL_FRAMEBUFFER_SRGB_CAPABLE: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &tmp);
    BRLogInfo("SDL_GL_MULTISAMPLESAMPLES: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &tmp);
    BRLogInfo("SDL_GL_MULTISAMPLEBUFFERS: " + tmp);

    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &tmp);
    BRLogInfo("SDL_GL_RED_SIZE: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &tmp);
    BRLogInfo("SDL_GL_GREEN_SIZE: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &tmp);
    BRLogInfo("SDL_GL_BLUE_SIZE: " + tmp);
    SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &tmp);
    BRLogInfo("SDL_GL_ALPHA_SIZE: " + tmp);
    checkSDLErr();
  }

  void getOpenGLVersion(int& ver, int& subver, int& shad_ver, int& shad_subver) {
    char* tmp;
    string_t glver;
    string_t glslver;
    ver = subver = shad_ver = shad_subver = 0;

    tmp = (char*)glGetString(GL_VERSION);
    if (tmp != nullptr) {
      glver = tmp;
    }
    else {
      glver = "";
    }

    std::vector<string_t> sv;

    if (glver.length() > 0) {
      sv = StringUtil::split(glver, '.');
      if (sv.size() < 2) {
        BRThrowException("Failed to get OpenGL version. Got '" + glver + "'.  Check that you have OpenGL installed on your machine. You may have to update your 'graphics driver'.");
      }
      ver = TypeConv::strToInt(sv[0]);
      subver = TypeConv::strToInt(sv[1]);
    }
    else {
      BRLogError("Failed to get OpenGL version.");
    }
    if (ver > 3) {
      //This will fail if we try to get an OpenGL version greater than what is supported, returning GL 1.1.  Shade is only supported on GL > 2.1.
      tmp = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
      if (tmp != nullptr) {
        glslver = tmp;
      }
      else {
        glslver = "";
      }
      if (glslver.length() > 0) {
        sv = StringUtil::split(glslver, '.');
        if (sv.size() < 2) {
          BRThrowException("Failed to get OpenGL Shade version. Got '" + glslver + "'.  Check that you have OpenGL installed on your machine. You may have to update your 'graphics driver'.");
        }
        shad_ver = TypeConv::strToInt(sv[0]);
        shad_subver = TypeConv::strToInt(sv[1]);
      }
      else {
        BRLogWarn("Failed to get OpenGL Shade version.");
      }
    }
  }
  void setSDLGLFlags(int minVersion, int minSubVersion) {
    checkSDLErr();
    //Attribs
    SDL_GL_ResetAttributes();
    checkSDLErr();

    //We want SRGB in the final render, so this should be requested.
    SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, false);
    checkSDLErr();

    //Context sharing will be necessary with multiple-window rendering (we are required to create 1 context per window)
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
    checkSDLErr();

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    checkSDLErr();
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    checkSDLErr();
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    //Not sure, imagine we'd use our own buffer blending to create a VR scene.
    //SDL_GL_SetAttribute(SDL_GL_STEREO, _pGlState->gl_stereo);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, minVersion);
    checkSDLErr();
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minSubVersion);
    checkSDLErr();

    //Desktop Debug = Compatibility, Runtime = Core, Phone = ES
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, _iProfile);
    checkSDLErr();

    int debug_flag = 0;
#ifdef _DEBUG
    debug_flag = SDL_GL_CONTEXT_DEBUG_FLAG;
#endif

    //Only in GL 3.0 (apparently)
    //Forward compatible deprecates old funcionality for a gain in speed (apparently)
    //https://wiki.libsdl.org/SDL_GLcontextFlag#SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
    int forward_compat = (_iProfile == SDL_GL_CONTEXT_PROFILE_CORE) ? (0) : (SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, debug_flag | forward_compat);
    checkSDLErr();

    //Depth size is finicky. Sometimes it will only give us 16 bits. Trying to set stencil to zero MIGHT help
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    checkSDLErr();
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, _iDepthBits);
    checkSDLErr();
    //Attempt to zero out the stencil buffer to request a 32b depth.

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    checkSDLErr();
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    checkSDLErr();
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    checkSDLErr();
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    checkSDLErr();

    //Multisampling
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, prof->_iMSAASamples);
    //checkSDLErr();
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, prof->_iMSAABuffers);
    //checkSDLErr();
  }
  bool handleSDLEvents() {
    SDL_Event event;
    bool done = false;
    while (SDL_PollEvent(&event)) {
      if (handleEvents(&event) == false) {
        done = true;
      }
    }
    return done;
  }
  SDL_Window* makeSDLWindow(const GraphicsWindowCreateParameters& params, int render_system, bool show) {
    string_t title;
    bool bFullscreen = false;
    SDL_Window* ret;

    int style_flags = 0;
    style_flags |= (show ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN);
    if (params._type == GraphicsWindowCreateParameters::Wintype_Desktop) {
      style_flags |= SDL_WINDOW_RESIZABLE;
    }
    else if (params._type == GraphicsWindowCreateParameters::Wintype_Utility) {
    }
    else if (params._type == GraphicsWindowCreateParameters::Wintype_Noborder) {
      style_flags |= SDL_WINDOW_BORDERLESS;
    }

    int x = params._x;
    int y = params._y;
    int w = params._width;
    int h = params._height;

    // #ifdef BR2_OS_IPHONE
    //     int flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL;
    //     title = "";
    // #elif defined(BR2_OS_WINDOWS) || defined(BR2_OS_LINUX)
    int flags = style_flags | render_system;
    title = params._title;
    // #else
    //     OS_NOT_SUPPORTED_ERROR
    // #endif

    //Note: This calls SDL_GL_LOADLIBRARY if SDL_WINDOW_OPENGL is set.
    ret = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (ret != nullptr) {
      //On Linux SDL will set an error if unable to represent a GL/Vulkan profile, as we try different ones. Ignore them for now.
      //Windows SDL sets an error when the context is created.
      checkSDLErr();

      //Fullscreen nonsense
      if (bFullscreen) {
        SDL_SetWindowFullscreen(ret, SDL_WINDOW_FULLSCREEN);
      }
      checkSDLErr();
      if (show) {
        SDL_ShowWindow(ret);
      }
      checkSDLErr();
    }
    else {
      //Linux: Couldn't find matching GLX visual.
      checkSDLErr(true, false);
    }

    //Customize window (per display system)
    //setWindowProps(ret, params);

    return ret;
  }
  bool handleEvents(SDL_Event* event) {
    int n = 0;
    glm::vec2 delta;
    SDL_Scancode keyCode;

    switch (event->type) {
      case SDL_MOUSEMOTION:
        //Don't use this.  Because of "SDL_warpMouse" which will mess stuff up.
        break;
      case SDL_KEYDOWN:
        keyCode = event->key.keysym.scancode;
        Gu::getGlobalInput()->setKeyDown(keyCode);
        break;
      case SDL_KEYUP:
        keyCode = event->key.keysym.scancode;
        Gu::getGlobalInput()->setKeyUp(keyCode);
        break;
      case SDL_MOUSEBUTTONDOWN:
        switch (event->button.button) {
          case SDL_BUTTON_LEFT:
            Gu::getGlobalInput()->setLmbState(ButtonState::Press);
            break;
          case SDL_BUTTON_MIDDLE:
            break;
          case SDL_BUTTON_RIGHT:
            Gu::getGlobalInput()->setRmbState(ButtonState::Press);
            break;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        switch (event->button.button) {
          case SDL_BUTTON_LEFT:
            Gu::getGlobalInput()->setLmbState(ButtonState::Release);
            break;
          case SDL_BUTTON_MIDDLE:
            break;
          case SDL_BUTTON_RIGHT:
            Gu::getGlobalInput()->setRmbState(ButtonState::Release);
            break;
        }
        break;
      case SDL_WINDOWEVENT:
        switch (event->window.event) {
          case SDL_WINDOWEVENT_CLOSE:
            return false;
            break;
        }
        break;
      case SDL_MOUSEWHEEL:
        if (event->wheel.y != 0) {
          int n = std::min(10, std::max(-10, event->wheel.y));
          Gu::getGlobalInput()->setMouseWheel(n);
        }
        if (event->wheel.x != 0) {
          n++;
        }
        break;
      case SDL_QUIT:
        return false;
        break;
    }

    return true;
  }
};

#pragma region PostDec And Defs

bool OglErr::handleErrors(bool bShowNote, bool bDoNotBreak, bool doNotLog, const string_t& shaderName, bool clearOnly) {
  App::checkSDLErr(doNotLog || !clearOnly, clearOnly);

  printAndFlushGpuLog(true, bDoNotBreak, doNotLog, shaderName, clearOnly);

  return checkOglErr(bShowNote, bDoNotBreak || clearOnly, doNotLog || !clearOnly, shaderName);
}
void staticDebugBreak(const string_t& str) {
  BRLogError(str);
  Gu::debugBreak();
}
void runtimeAssertion(const string_t& str) {
  BRThrowException(str);
}

#pragma endregion

}  // namespace sf2d

#endif