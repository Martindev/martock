//! render renders the state of the world to screen.

mod textures;

use std::f64;

use graphics;
use graphics::Transformed;
use piston::input::RenderArgs;
use opengl_graphics::GlGraphics;

use body;
use world;
use camera;

pub struct Renderer {
    block_size: usize,
}

impl Renderer {
    pub fn new(block_size: usize) -> Self {
        Renderer { block_size: block_size }
    }

    pub fn render(&self,
                  world: &world::World,
                  _: &[&body::Body],
                  cam: &camera::Camera,
                  args: RenderArgs,
                  gl: &mut GlGraphics) {
        let viewport = args.viewport();
        gl.draw(viewport, |ctx, gl| self.draw(world, args, cam, ctx, gl))
    }

    fn draw(&self,
            world: &world::World,
            _: RenderArgs,
            cam: &camera::Camera,
            ctx: graphics::Context,
            gl: &mut GlGraphics) {
        let view = cam.view();
        let origin = view.top_left;
        let (block_x, block_y) = origin.block_pos();
        let (offset_x, offset_y) = origin.block_offsets();
        let (translate_x, translate_y) = (offset_x * -1.0, offset_y * -1.0);

        graphics::clear([0.0, 0.0, 0.0, 1.0], gl);
        for (x, y, block) in world.iter(block_x, block_y, view.width, view.height) {
            let texture = textures::block(block);
            let xpixel = ((x - block_x) * self.block_size as i64) as f64;
            let ypixel = ((y - block_y) as usize * self.block_size) as f64;
            let border = 5.0;
            let size = self.block_size as f64 - border;
            let rect = [xpixel + border, ypixel + border, size, size];
            let x_transform = translate_x * self.block_size as f64;
            let y_transform = translate_y * self.block_size as f64;
            let transform = ctx.trans(x_transform, y_transform).transform;
            graphics::rectangle(texture, rect, transform, gl);
        }
    }
}
