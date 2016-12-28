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

struct Sentience<'a> {
    bodies: Vec<&'a body::Body>,
    committers: Vec<&'a committer::Committer>,
    living: Vec<&'a mut life::Life>,
}

fn engine(a: arbiter::Arbiter,
          r: reality::Reality,
          mut w: world::World,
          mut sentience: Sentience) {
    loop {
        let mut cls = Vec::new();
        for c in sentience.committers.iter() {
            if let Some(cl) = c.cl(&w, &sentience.bodies) {
                cls.push(cl);
            }
        }

        a.arbitrate(&mut w, cls.as_slice());
        r.apply(&w, sentience.bodies.as_mut_slice());

        for mut life in sentience.living.iter_mut() {
            life.update(&w, &sentience.bodies);
        }
    }
}

fn main() {
    let a = arbiter::Arbiter::new();
    let r = reality::Reality::new();
    let w = world::World::new();
    let s = Sentience {
        bodies: Vec::new(),
        committers: Vec::new(),
        living: Vec::new(),
    };
    engine(a, r, w, s);
}
