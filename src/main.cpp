#include "./sf2d.h"

//Short cut
typedef sf2d::GL GL;

class MyGame : public sf2d::Game {
public:
  std::shared_ptr<sf2d::ShaderProgram> _prog = nullptr;
  std::shared_ptr<sf2d::Texture2D> _tex = nullptr;

  MyGame(std::shared_ptr<sf2d::App> a) : sf2d::Game(a) {
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

    _prog = std::make_shared<sf2d::ShaderProgram>();
    _prog->compile(vert, frag);

    std::shared_ptr<sf2d::Image32> img = std::make_shared<sf2d::Image32>();
    img->load("./mario.png");
    _tex = std::make_shared<sf2d::Texture2D>(img, true, false, false);

    _inds = std::make_shared<sf2d::GpuBuffer>("indexes", GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int));
    _inds->allocate(6);
    std::vector<unsigned int> inds = { 0, 2, 3, 0, 3, 1 };
    _inds->copyDataClientServer(inds.size(), inds.data(), sizeof(unsigned int));

    _verts = std::make_shared<sf2d::GpuBuffer>("vetrts", GL_ARRAY_BUFFER, sizeof(sf2d::v2x2));
    _verts->allocate(4);
    std::vector<sf2d::v2x2> verts = { sf2d::v2x2(.10, .50, 0, 0), sf2d::v2x2(.30, .50, 1, 0), sf2d::v2x2(.10, .10, 0, 1), sf2d::v2x2(.30, .10, 1, 1) };
    _verts->copyDataClientServer(verts.size(), verts.data(), sizeof(sf2d::v2x2));
  }
  virtual void update(double delta) override {
  }
  virtual void render() override {
    glDisable(GL_CULL_FACE);

    _tex->bind(sf2d::TextureChannel::e::Channel0);
    _prog->bind();
    _prog->setTextureUf(_tex, "_ufTexture0");

    //Very basic vert + tex. The screen coordinates are -1,1 x and -1,1 y
    GLint vLoc = GL::glGetAttribLocation(_prog->glId(), "_v201");
    GLint xLoc = GL::glGetAttribLocation(_prog->glId(), "_x201");
    if (vLoc == -1 || xLoc == -1) {
    }
    else {
      sf2d::OglErr::chkErrDbg();
      _verts->bindBuffer();
      sf2d::OglErr::chkErrDbg();
      GL::glEnableVertexAttribArray(vLoc);
      GL::glVertexAttribPointer(
        vLoc,
        2,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized?
        sizeof(sf2d::v2x2),           // stride
        (GLvoid*)((intptr_t)0)  // array buffer offset
      );
      sf2d::OglErr::chkErrDbg();

      GL::glEnableVertexAttribArray(xLoc);
      GL::glVertexAttribPointer(
        xLoc,
        2,                                          // size
        GL_FLOAT,                                   // type
        GL_FALSE,                                   // normalized?
        sizeof(sf2d::v2x2),                               // stride
        (GLvoid*)((intptr_t)0 + sizeof(float) * 2)  // array buffer offset
      );
      sf2d::OglErr::chkErrDbg();

      _inds->bindBuffer();
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);

      _inds->unbindBuffer();
      _verts->unbindBuffer();
      _tex->unbind(sf2d::TextureChannel::e::Channel0);
      _prog->unbind();
    }
  }
  std::shared_ptr<sf2d::GpuBuffer> _inds;
  std::shared_ptr<sf2d::GpuBuffer> _verts;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  std::shared_ptr<sf2d::App> a = std::make_shared<sf2d::App>();

  sf2d::Log::info("Hello World.... running the app");

  std::shared_ptr<MyGame> g = std::make_shared<MyGame>(a);
  a->run(g);

  return 0;
}
