#include "./sfm.h"

//Short cut
typedef SFM::GL GL;

struct v2x2 {
  float x, y, u, v;
  v2x2(float dx, float dy, float du, float dv) {
    x = dx;
    y = dy;
    u = du;
    v = dv;
  }
};

class MyGame : public SFM::Game {
public:
  std::shared_ptr<SFM::ShaderProgram> _prog;
  std::shared_ptr<SFM::Texture2D> _tex;

  MyGame(std::shared_ptr<SFM::App> a) : SFM::Game(a) {
  }
  virtual void init() override {
    //OpenGL is loaded. Window Loaded - ready to rock.
    std::string vert = Stz "#version 420 core\n" +
                       "//Vert Shader\n" +
                       "\n" +
                       "layout(location = 0) in vec2 _v201;\n" +
                       "layout(location = 1) in vec2 _x201;\n" +
                       "\n" +
                       "out vec2 _x2Out;\n" +
                       "out vec3 _v3Out;\n" +
                       "\n" +
                       "void main()\n" +
                       "{\n" +
                       "    //this is the stuff from the GUI shader.  It should work.  Note we don't even need a matrix\n" +
                       "    _x2Out = _x201;\n" +
                       "    _v3Out = vec3(_v201.x, _v201.y, -1);\n" +
                       "    gl_Position =  vec4(_v201.x, _v201.y, -1, 1);\n" +
                       "}\n";

    std::string frag = Stz "#version 420 core\n" +
                       "//Frag Shader\n" +
                       "\n" +
                       "uniform sampler2D _ufTexture0;\n" +
                       "\n" +
                       "in vec3 _v3Out;\n" +
                       "in vec2 _x2Out;\n" +
                       "out vec4 _gColorOut;\n" +
                       "\n" +
                       "void main() {\n" +
                       "  _gColorOut = texture(_ufTexture0, vec2(_x2Out));\n" +
                       "  if(_gColorOut.a <= 0.001) {\n" +
                       "    discard;\n" +
                       "    }\n" +
                       "\n" +
                       " // _gPositionOut = vec4(_v3Out, 0);\n" +
                       " // _gNormalOut = vec4(0,0,0,0);//Flat Shade\n" +
                       " // _gPlaneOut = vec4(0,0,0,0);\n" +
                       "  //  _gPickOut = _ufPickId;\n" +
                       "}\n";

    _prog = std::make_shared<SFM::ShaderProgram>();
    _prog->compile(vert, frag);

    std::shared_ptr<SFM::Image> img = std::make_shared<SFM::Image>();
    img->load("./mario.png");
    _tex = std::make_shared<SFM::Texture2D>(img, true, false, false);

    _inds = std::make_shared<SFM::GpuBuffer>("indexes", GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int));
    _inds->allocate(6);
    std::vector<unsigned int> inds = { 0, 2, 3, 0, 3, 1 };
    _inds->copyDataClientServer(inds.size(), inds.data(), sizeof(unsigned int));

    _verts = std::make_shared<SFM::GpuBuffer>("vetrts", GL_ARRAY_BUFFER, sizeof(v2x2));
    _verts->allocate(4);
    std::vector<v2x2> verts = { v2x2(.10, .50, 0, 0), v2x2(.30, .50, 1, 0), v2x2(.10, .10, 0, 1), v2x2(.30, .10, 1, 1) };
    _verts->copyDataClientServer(verts.size(), verts.data(), sizeof(v2x2));
  }
  virtual void update(double delta) override {
  }
  virtual void render() override {
    glDisable(GL_CULL_FACE);

    _tex->bind(SFM::TextureChannel::e::Channel0);
    _prog->bind();
    _prog->setTextureUf(_tex, "_ufTexture0");

    GLint vLoc = GL::glGetAttribLocation(_prog->glId(), "_v201");
    GLint xLoc = GL::glGetAttribLocation(_prog->glId(), "_x201");
    if (vLoc == -1 || xLoc == -1) {
    }
    else {
      SFM::OglErr::chkErrDbg();
      _verts->bindBuffer();
      SFM::OglErr::chkErrDbg();
      GL::glEnableVertexAttribArray(vLoc);
      GL::glVertexAttribPointer(
        vLoc,
        2,      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized?
        sizeof(v2x2),           // stride
        (GLvoid*)((intptr_t)0)  // array buffer offset
      );
      SFM::OglErr::chkErrDbg();

      GL::glEnableVertexAttribArray(xLoc);
      GL::glVertexAttribPointer(
        xLoc,
        2,                          // size
        GL_FLOAT,                                   // type
        GL_FALSE,                                   // normalized?
        sizeof(v2x2),                               // stride
        (GLvoid*)((intptr_t)0 + sizeof(float) * 2)  // array buffer offset
      );
      SFM::OglErr::chkErrDbg();

      _inds->bindBuffer();
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);

      _inds->unbindBuffer();
      _verts->unbindBuffer();
      _tex->unbind(SFM::TextureChannel::e::Channel0);
      _prog->unbind();
    }
  }
  std::shared_ptr<SFM::GpuBuffer> _inds;
  std::shared_ptr<SFM::GpuBuffer> _verts;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  std::shared_ptr<SFM::App> a = std::make_shared<SFM::App>();

  SFM::Log::info("Hello World.... running the app");

  std::shared_ptr<MyGame> g = std::make_shared<MyGame>(a);
  a->run(g);

  return 0;
}
