//! render renders the state of the world to screen.

use graphics;
use piston::input::RenderArgs;
use opengl_graphics::GlGraphics;

use body;
use world;

pub struct Renderer;

impl Renderer {
    pub fn new() -> Self {
        Renderer {}
    }

    pub fn render(&self,
                  _: &world::World,
                  _: &[&body::Body],
                  args: RenderArgs,
                  gl: &mut GlGraphics) {
        let viewport = args.viewport();
        gl.draw(viewport, |_, gl| graphics::clear([1.0, 1.0, 1.0, 1.0], gl));
    }
}
