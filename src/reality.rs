//! reality is laws and mechanics of nature.

use body;
use world;

pub struct Reality;

/// Reality applies all the active laws of nature such as physics to the bodies in the world.
impl Reality {
    pub fn new() -> Self {
        Reality{}
    }

    pub fn apply(&self, _: &world::World, _: &mut [&body::Body]) {}
}
