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

pub mod arbiter;
pub mod block;
pub mod body;
pub mod commit;
pub mod committer;
pub mod life;
pub mod reality;
pub mod tool;
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
    world: world::World,
    bodies: Vec<&'a body::Body>,
    mutable_bodies: Vec<&'a mut body::Body>,
    living: Vec<&'a mut life::Life>,
}

fn window() -> Result<sdl2_window::Sdl2Window, String> {
    piston::window::WindowSettings::new("martock", (1280, 720)).build()
}

fn engine(mut window: sdl2_window::Sdl2Window,
          moderators: Moderators,
          sentience: Sentience,
          mut state: State) {
    let mut events = piston::event_loop::WindowEvents::new();
    while let Some(e) = events.next(&mut window) {
        let mut cls = Vec::new();
        for c in sentience.committers.iter() {
            if let Some(cl) = c.cl(&state.world, &state.bodies) {
                cls.push(cl);
            }
        }

        moderators.arbiter.arbitrate(&mut state.world, cls.as_slice());
        moderators.reality.apply(&state.world, state.mutable_bodies.as_slice());

        for mut life in state.living.iter_mut() {
            life.update(&state.world, state.bodies.as_slice(), &e);
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
        world: world::World::new(),
        bodies: Vec::new(),
        mutable_bodies: Vec::new(),
        living: Vec::new(),
    };

    let sentience = Sentience { committers: Vec::new() };

    engine(window, moderators, sentience, state);
}
