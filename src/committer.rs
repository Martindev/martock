//! committer is anything that modifies the world.

use commit;
use world;

pub type CL = Iterator<Item = commit::Commit>;

pub trait Committer {
    fn cl(&self, &world::World) -> Option<Box<CL>>;
}
