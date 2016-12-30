//! render renders the state of the world to screen.

mod textures;

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
            args: RenderArgs,
            cam: &camera::Camera,
            ctx: graphics::Context,
            gl: &mut GlGraphics) {
        let pos = cam.position();
        let block_x = pos.x as i64;
        let block_y = pos.y as u8;
        let translate_x = pos.x % 1.0 * self.block_size as f64 * -1.0;
        let translate_y = pos.y % 1.0 * self.block_size as f64 * -1.0;

        let blocks_width = (args.draw_width as usize / self.block_size) + 1;
        let blocks_height = (args.draw_height as usize / self.block_size) + 1;

        graphics::clear([0.0, 0.0, 0.0, 1.0], gl);
        for i in 0..blocks_width {
            for j in 0..blocks_height {
                let block = world.block(block_x + i as i64, block_y + j as u8);
                let texture = textures::block(block);
                let x = (i * self.block_size) as f64;
                let y = (j * self.block_size) as f64;
                let border = 5.0;
                let bordered_size = self.block_size as f64 - border;
                let rect = [x + border, y + border, bordered_size, bordered_size];
                let border_transform = ctx.zoom(1.0);
                let edge_transform = border_transform.trans(translate_x, translate_y).transform;
                graphics::rectangle(texture, rect, edge_transform, gl);
            }
        }
    }
}
