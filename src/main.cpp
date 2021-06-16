#include "./sf2d.h"

//Short cut
typedef sf2d::GL GL;


class MyGame : public sf2d::Game {
public:
  MyGame(std::shared_ptr<sf2d::App> a) : sf2d::Game(a) {
  }
  virtual void init() override {
    //Load Texture
    std::shared_ptr<sf2d::Image32> img = std::make_shared<sf2d::Image32>();
    img->load("./mario.png");
    _tex = std::make_shared<sf2d::Texture2D>(img, true, false, false);
    _tex->setFilter(sf2d::TexFilter::Nearest);

    _quads = std::make_shared<sf2d::QuadBlitter>();
    _quads->setTexture(_tex);
  }
  virtual void update(double delta) override {
    _quads->reset();
    _quads->setQuad(glm::vec2(10,10), app()->viewport(), glm::vec4(1,1,1,1), glm::vec2(64,64));
  }
  virtual void render() override {
    _quads->render(app()->viewport());
  }

private:
  std::shared_ptr<sf2d::Texture2D> _tex = nullptr;
  std::shared_ptr<sf2d::QuadBlitter> _quads = nullptr;
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
