//! render renders the state of the world to screen.

mod textures;
mod window;
mod window_test;

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
        let window = window::Window::new(view.x, view.y);

        graphics::clear([0.0, 0.0, 0.0, 1.0], gl);
        for i in 0..view.width {
            for j in 0..view.height {
                let block = world.block(window.x + i as i64, window.y + j as u8);
                let texture = textures::block(block);
                let x = (i * self.block_size) as f64;
                let y = (j * self.block_size) as f64;
                let border = 5.0;
                let bordered_size = self.block_size as f64 - border;
                let rect = [x + border, y + border, bordered_size, bordered_size];
                let edge_transform = ctx.trans(window.translate_x * self.block_size as f64,
                           window.translate_y * self.block_size as f64)
                    .transform;
                graphics::rectangle(texture, rect, edge_transform, gl);
            }
        }
    }
}
