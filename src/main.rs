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

struct Sentience<'a> {
    committers: Vec<&'a committer::Committer>,
}

struct State<'a> {
    bodies: Vec<&'a body::Body>,
    interactives: Vec<&'a mut interactive::Interactive>,
    living: Vec<&'a mut life::Life>,
    mutable_bodies: Vec<&'a mut body::Body>,
    world: world::World,
}

fn window() -> Result<sdl2_window::Sdl2Window, String> {
    piston::window::WindowSettings::new("martock", (1280, 720)).build()
}

fn engine(mut window: sdl2_window::Sdl2Window,
          moderators: Moderators,
          sentience: Sentience,
          renderer: render::Renderer,
          mut state: State) {
    let opengl = opengl_graphics::OpenGL::V4_5;
    let mut gl = opengl_graphics::GlGraphics::new(opengl);
    let mut events = piston::event_loop::WindowEvents::new();
    while let Some(e) = events.next(&mut window) {
        match e {
            piston::input::Event::Update(_) => {
                let mut cls = Vec::new();
                for c in sentience.committers.iter() {
                    if let Some(cl) = c.cl(&state.world, &state.bodies) {
                        cls.push(cl);
                    }
                }

                moderators.arbiter.arbitrate(&mut state.world, cls.as_slice());
                moderators.reality.apply(&state.world, state.mutable_bodies.as_slice());

                for mut life in state.living.iter_mut() {
                    life.update(&state.world, state.bodies.as_slice());
                }
            }
            piston::input::Event::Render(args) => {
                renderer.render(&state.world, state.bodies.as_slice(), args, &mut gl)
            }
            piston::input::Event::AfterRender(_) => (),
            piston::input::Event::Idle(_) => (),
            piston::input::Event::Input(input) => {
                for mut interactable in state.interactives.iter_mut() {
                    interactable.interact(&input);
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

    let state = State {
        bodies: Vec::new(),
        interactives: Vec::new(),
        living: Vec::new(),
        mutable_bodies: Vec::new(),
        world: world::World::new(),
    };

    let sentience = Sentience { committers: Vec::new() };

    let renderer = render::Renderer::new();

    engine(window, moderators, sentience, renderer, state);
}
