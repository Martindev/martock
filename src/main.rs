//! martock is a game.
//!
//! ## Initialization
//!
//! In no particular order, the following must be initialized before the main loop. See the module
//! docs for more information on each.
//!
//! * World
//! * Arbiter
//! * Reality
//! * Sentience, which interact with the world and may implement Body, Committer, and/or Life
//!
//! ## Main Loop
//!
//! 1. Give committers the state of the world and bodies and ask for commits to change the
//!    world state.
//! 2. Pass all commits through the arbiter which decides whether the commit should be
//!    applied to the world state.
//! 3. Apply reality to all the bodies (physics and other laws of nature).
//! 4. Update all the mutable world observers (who implement the life trait), such as the
//!    camera, sound effects, etc.

extern crate piston;
extern crate sdl2_window;
extern crate graphics;
extern crate opengl_graphics;

pub mod arbiter;
pub mod block;
pub mod body;
pub mod camera;
pub mod commit;
pub mod committer;
pub mod interactive;
pub mod life;
pub mod reality;
pub mod tool;
pub mod render;
pub mod world;
mod world_test;

struct Moderators {
    arbiter: arbiter::Arbiter,
    reality: reality::Reality,
}

struct State {
    world: world::World,
}

fn window() -> Result<sdl2_window::Sdl2Window, String> {
    piston::window::WindowSettings::new("martock", (1280, 720)).build()
}

fn commits(world: &world::World, committers: &[&committer::Committer]) -> Vec<Box<committer::CL>> {
    let mut cls = Vec::new();
    for c in committers {
        if let Some(cl) = c.cl(&world) {
            cls.push(cl);
        }
    }
    cls
}

fn merge(moderators: &Moderators,
         change_list: Vec<Box<committer::CL>>,
         bodies: &[&mut body::Body],
         world: &mut world::World) {
    moderators.arbiter.arbitrate(change_list, world);
    moderators.reality.apply(world, bodies);
}

fn engine(mut window: sdl2_window::Sdl2Window,
          moderators: Moderators,
          renderer: render::Renderer,
          mut state: State) {
    let opengl = opengl_graphics::OpenGL::V4_5;
    let mut gl = opengl_graphics::GlGraphics::new(opengl);
    let mut events = piston::event_loop::WindowEvents::new();
    let mut camera = camera::Camera::new(camera::Position { x: 0.0, y: 0.0 });
    while let Some(e) = events.next(&mut window) {
        match e {
            piston::input::Event::Update(_) => {
                let change_list = commits(&state.world, &Vec::new());
                merge(&moderators, change_list, &Vec::new(), &mut state.world);

                let mut lives: Vec<&mut life::Life> = Vec::new();
                for mut life in lives.iter_mut() {
                    life.update(&state.world);
                }
            }
            piston::input::Event::Render(args) => {
                let bodies: Vec<&body::Body> = Vec::new();
                renderer.render(&state.world, &bodies, &camera, args, &mut gl)
            }
            piston::input::Event::AfterRender(_) => (),
            piston::input::Event::Idle(_) => (),
            piston::input::Event::Input(input) => {
                let mut interactives: Vec<&mut interactive::Interactive> = vec![&mut camera];
                for mut interactive in interactives.iter_mut() {
                    interactive.interact(&input);
                }
            }
        }
    }
}

fn main() {
    let window = window().expect("Failed to construct window.");

    let moderators = Moderators {
        arbiter: arbiter::Arbiter::new(),
        reality: reality::Reality::new(),
    };

    let state = State { world: world::World::new() };

    let renderer = render::Renderer::new();

    engine(window, moderators, renderer, state);
}
