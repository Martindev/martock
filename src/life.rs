//! life is anything that changes state in response to the world and bodies.

use world;

/// Life should be implemented by anything that wants to change its state in response to the world
/// and bodies.
pub trait Life {
    fn update(&mut self, w: &world::World);
}
