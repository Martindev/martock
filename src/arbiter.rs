//! arbiter defends the world from invalid modifications.

use commit;
use committer;
use world;

pub struct Arbiter;

/// Arbiter decides whether to apply commits to the world.
impl Arbiter {
    pub fn new() -> Self {
        Arbiter {}
    }

    pub fn arbitrate(&self, w: &mut world::World, cls: &[committer::CL]) {
        for cl in cls.iter() {
            for commit in cl.commits().iter() {
                if self.approve(commit) {
                    w.set_block(commit.block, commit.next_state);
                }
            }
        }
    }

    fn approve(&self, _: &commit::Commit) -> bool {
        true
    }
}
