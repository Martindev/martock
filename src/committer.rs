//! committer is anything that modifies the world.

use camera;
use commit;
use world;

pub type CL = Iterator<Item = commit::Commit>;

pub trait Committer {
    fn cl(&self, &world::World, &camera::Camera) -> Option<Box<CL>>;
}
